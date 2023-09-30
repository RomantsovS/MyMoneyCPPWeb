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
    void persist(Action& a) {}

   private:
    std::string name;
};

DBO_EXTERN_TEMPLATES(Wallet)

#endif
