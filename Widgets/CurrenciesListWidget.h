#ifndef CURRENCIES_WIDGET_H_
#define CURRENCIES_WIDGET_H_

#include <Wt/WContainerWidget.h>

#include <string>

namespace Wt {
class WStackedWidget;
class WPushButton;
class WTable;
}  // namespace Wt

class Session;

class CurrenciesListWidget : public Wt::WContainerWidget {
   public:
    CurrenciesListWidget(Session *session);
    void update();

   private:
    Session *session_ = nullptr;
    Wt::WContainerWidget *top_panel = nullptr;
    Wt::WTable *table_ = nullptr;
};

#endif
