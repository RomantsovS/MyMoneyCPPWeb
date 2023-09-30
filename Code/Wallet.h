#ifndef WALLET_H_
#define WALLET_H_

#include <Wt/Dbo/Types.h>
#include <Wt/Dbo/WtSqlTraits.h>

#include <string>

class Wallet;
using Wallets = Wt::Dbo::collection<Wt::Dbo::ptr<Wallet>>;

class Wallet {
   public:
    template <class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, name_, "name");
    }

    std::string name() const {
        return name_;
    } 

   private:
    std::string name_;
};

DBO_EXTERN_TEMPLATES(Wallet)
 
#endif
