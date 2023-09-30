#ifndef SESSION_H_
#define SESSION_H_

#include <Wt/Auth/Dbo/UserDatabase.h>
#include <Wt/Auth/Login.h>
#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <Wt/Dbo/ptr.h>

#include <vector>

#include "Currency.h"
#include "User.h"
#include "Wallet.h"

using UserDatabase = Wt::Auth::Dbo::UserDatabase<AuthInfo>;

class Session {
   public:
    static void configureAuth();

    Session();

    Wt::Auth::AbstractUserDatabase& users();
    Wt::Auth::Login& login() { return login_; }

    std::vector<Wallet> wallets(size_t limit) const;
    std::vector<Currency> currencies(size_t limit) const;

    /*
     * These methods deal with the currently logged in user
     */
    std::string userName() const;

    static const Wt::Auth::AuthService& auth();
    static const Wt::Auth::AbstractPasswordService& passwordAuth();

   private:
    mutable Wt::Dbo::Session session_;
    std::unique_ptr<UserDatabase> users_;
    Wt::Auth::Login login_;

    Wt::Dbo::ptr<User> user() const;
};

#endif
