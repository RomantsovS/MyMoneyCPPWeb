#ifndef MENU_WIDGET_H_
#define MENU_WIDGET_H_

#include <Wt/WContainerWidget.h>

#include <string>

namespace Wt {
class WStackedWidget;
class WPushButton;
}  // namespace Wt

class MenuWidget : public Wt::WContainerWidget {
   public:
    MenuWidget();

   private:
    void openWalletsList();
    void openCurrenciesList();

    Wt::WText *title_ = nullptr;
    Wt::WPushButton *wallets_button_ = nullptr;
    Wt::WPushButton *currencies_button_ = nullptr;
};

#endif
