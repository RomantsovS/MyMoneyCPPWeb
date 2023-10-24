#ifndef SESSION_H_
#define SESSION_H_

#include <Wt/Auth/Dbo/UserDatabase.h>
#include <Wt/Auth/Login.h>
#include <Wt/Dbo/QueryModel.h>
#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/backend/Sqlite3.h>

#include <memory>
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

    template <typename T>
    std::shared_ptr<Wt::Dbo::QueryModel<Wt::Dbo::ptr<T>>> getQueryModel() {
        Wt::Dbo::Transaction t(session_);

        auto model = std::make_shared<Wt::Dbo::QueryModel<Wt::Dbo::ptr<T>>>();
        model->setQuery(session_.find<T>());
        model->addColumn("id", "ID");
        model->addColumn("name", "Name");

        return model;
    }

    std::unique_ptr<Wt::Dbo::Transaction> make_transaction() {
        return std::make_unique<Wt::Dbo::Transaction>(session_);
    }

    template <typename T>
    void add(std::unique_ptr<T>&& obj) const {
        session_.add(std::move(obj));
    }

    template <typename T>
    Wt::Dbo::ptr<T> load(typename Wt::Dbo::dbo_traits<T>::IdType id) const {
        return session_.load<T>(id);
    }

    void update(Wt::Dbo::ptr<Currency>::mutator&&) const { Wt::Dbo::Transaction t(session_); }

    /*
     * These methods deal with the currently logged in user
     */
    std::string userName() const;

    static const Wt::Auth::AuthService& auth();
    static const Wt::Auth::AbstractPasswordService& passwordAuth();

   private:
    Wt::Dbo::ptr<User> user() const;

    mutable Wt::Dbo::Session session_;
    std::unique_ptr<UserDatabase> users_;
    Wt::Auth::Login login_;
};

#endif
