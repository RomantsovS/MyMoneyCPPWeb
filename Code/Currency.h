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

    const std::string& getName() const { return name_; }
    void setName(const std::string& name) { name_ = name; }

    static Wt::Dbo::dbo_traits<Currency>::IdType stringToId(const std::string& s);

   private:
    std::string name_;
};

DBO_EXTERN_TEMPLATES(Currency)

#endif
