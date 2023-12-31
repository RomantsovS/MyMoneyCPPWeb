#ifndef CURRENCIES_WIDGET_H_
#define CURRENCIES_WIDGET_H_

#include <Wt/WContainerWidget.h>

#include <string>

namespace Wt {
class WStackedWidget;
class WPushButton;
class WTableView;
}  // namespace Wt

class Session;

class CurrenciesListWidget : public Wt::WContainerWidget {
   public:
    CurrenciesListWidget(Session *session);
    
    void update();

    void add();
    void edit();

   private:
    Session *session_ = nullptr;
    Wt::WContainerWidget *top_panel = nullptr;
    Wt::WPushButton *add_button_ = nullptr;
    Wt::WTableView *table_view_ = nullptr;
};

#endif
