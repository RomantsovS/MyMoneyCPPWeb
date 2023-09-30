#ifndef CUREENCY_H_
#define CUREENCY_H_

#include <Wt/Dbo/Types.h>
#include <Wt/Dbo/WtSqlTraits.h>

#include <string>

class Currency;
using Currencies = Wt::Dbo::collection<Wt::Dbo::ptr<Currency>>;

class Currency {
   public:
    Currency() = default;
    Currency(const std::string& name) : name_(name) {}

    template <class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, name_, "name");
    }

    std::string name() const { return name_; }

   private:
    std::string name_;
};

DBO_EXTERN_TEMPLATES(Currency)

#endif
