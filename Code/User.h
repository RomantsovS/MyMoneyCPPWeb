#ifndef USER_H_
#define USER_H_

#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/Dbo/Types.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <Wt/WDateTime.h>

#include <string>

class User;
using AuthInfo = Wt::Auth::Dbo::AuthInfo<User>;
using Users = Wt::Dbo::collection<Wt::Dbo::ptr<User>>;

class User {
   public:
    std::string name; /* a copy of auth info's user name */
    Wt::Dbo::weak_ptr<AuthInfo> authInfo;

    template <class Action>
    void persist(Action& a) {
        Wt::Dbo::hasOne(a, authInfo, "user");
    }
};

DBO_EXTERN_TEMPLATES(User)

#endif
