#include "Session.h"

#include <Wt/Auth/AuthService.h>
#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/Auth/Dbo/UserDatabase.h>
#include <Wt/Auth/GoogleService.h>
#include <Wt/Auth/HashFunction.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Auth/PasswordStrengthValidator.h>
#include <Wt/Auth/PasswordVerifier.h>
#include <Wt/WApplication.h>
#include <Wt/WLogger.h>

#ifndef WT_WIN32
#include <unistd.h>
#endif

#if !defined(WT_WIN32) && !defined(__CYGWIN__) && !defined(ANDROID)
#define HAVE_CRYPT
#ifndef _XOPEN_CRYPT
#include <crypt.h>
#endif  // _XOPEN_CRYPT
#endif

using namespace Wt;

namespace {

#ifdef HAVE_CRYPT
class UnixCryptHashFunction : public Auth::HashFunction {
   public:
    std::string compute(const std::string& msg, const std::string& salt) const override {
        std::string md5Salt = "$1$" + salt;
        return crypt(msg.c_str(), md5Salt.c_str());
    }

    bool verify(const std::string& msg, [[maybe_unused]] const std::string& salt,
                const std::string& hash) const override {
        return crypt(msg.c_str(), hash.c_str()) == hash;
    }

    std::string name() const override { return "crypt"; }
};
#endif  // HAVE_CRYPT

Auth::AuthService myAuthService;
Auth::PasswordService myPasswordService(myAuthService);
}  // namespace

void Session::configureAuth() {
    myAuthService.setAuthTokensEnabled(true, "hangmancookie");
    myAuthService.setEmailVerificationEnabled(false);

    auto verifier = std::make_unique<Auth::PasswordVerifier>();
    verifier->addHashFunction(std::make_unique<Auth::BCryptHashFunction>(7));

#ifdef HAVE_CRYPT
    // We want to still support users registered in the pre - Wt::Auth
    // version of the hangman example
    verifier->addHashFunction(std::make_unique<UnixCryptHashFunction>());
#endif

    myPasswordService.setVerifier(std::move(verifier));
    myPasswordService.setStrengthValidator(std::make_unique<Auth::PasswordStrengthValidator>());
    myPasswordService.setAttemptThrottlingEnabled(true);
}

Session::Session() {
    auto sqlite3 =
        std::make_unique<Dbo::backend::Sqlite3>(WApplication::instance()->appRoot() + "mymoney.db");
    sqlite3->setProperty("show-queries", "true");
    session_.setConnection(std::move(sqlite3));

    session_.mapClass<User>("user");
    session_.mapClass<Wallet>("wallet");
    session_.mapClass<Currency>("currency");
    session_.mapClass<AuthInfo>("auth_info");
    session_.mapClass<AuthInfo::AuthIdentityType>("auth_identity");
    session_.mapClass<AuthInfo::AuthTokenType>("auth_token");

    users_ = std::make_unique<UserDatabase>(session_);

    {
        Dbo::Transaction transaction(session_);
        try {
            session_.createTables();

            /*
             * Add a default guest/guest account
             */
            Auth::User guestUser = users_->registerNew();
            guestUser.addIdentity(Auth::Identity::LoginName, "guest");
            myPasswordService.updatePassword(guestUser, "guest");

            transaction.commit();

            log("info") << "Database created";
        } catch (...) {
            log("info") << "Using existing database";
        }
    }

    Dbo::Transaction transaction(session_);

    using Users = Dbo::collection<Dbo::ptr<User>>;

    Users users = session_.find<User>();

    log("info") << "We have " << users.size() << " users:\n";

    for (const auto& user : users) {
        log("info") << " user " << user->name;
    }

    transaction.commit();
}

Dbo::ptr<User> Session::user() const {
    log("info") << "call" << __PRETTY_FUNCTION__;
    if (login_.loggedIn()) {
        Dbo::ptr<AuthInfo> authInfo = users_->find(login_.user());
        Dbo::ptr<User> user = authInfo->user();

        if (!user) {
            user = session_.add(std::make_unique<User>());
            authInfo.modify()->setUser(user);
        }

        return user;
    } else
        return Dbo::ptr<User>();
}

std::vector<Wallet> Session::wallets(size_t limit) const {
    Dbo::Transaction transaction(session_);

    Wallets wallets = session_.find<Wallet>().limit(limit);

    std::vector<Wallet> result;
    for (const auto& dbo_wallet : wallets) {
        result.push_back(*dbo_wallet);
    }

    transaction.commit();

    return result;
}

std::vector<Currency> Session::currencies(size_t limit) const {
    Dbo::Transaction transaction(session_);

    Currencies currencies = session_.find<Currency>().limit(limit);

    std::vector<Currency> result;
    for (const auto& dbo_currency : currencies) {
        result.push_back(*dbo_currency);
    }

    transaction.commit();

    return result;
}

std::string Session::userName() const {
    if (login_.loggedIn())
        return login_.user().identity(Auth::Identity::LoginName).toUTF8();
    else
        return std::string();
}

Auth::AbstractUserDatabase& Session::users() {
    log("info") << "call" << __PRETTY_FUNCTION__;
    return *users_;
}

const Auth::AuthService& Session::auth() { return myAuthService; }

const Auth::AbstractPasswordService& Session::passwordAuth() { return myPasswordService; }
