#include "Currency.h"

#include <Wt/Dbo/Impl.h>

DBO_INSTANTIATE_TEMPLATES(Currency)

Wt::Dbo::dbo_traits<Currency>::IdType Currency::stringToId(const std::string &s) {
    std::size_t pos = std::string::npos;
    auto result = std::stoll(s, &pos);
    if (pos != s.size())
        return Wt::Dbo::dbo_traits<Currency>::invalidId();
    else
        return result;
}