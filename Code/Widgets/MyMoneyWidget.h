#ifndef MAIN_WIDGET_H_
#define MAIN_WIDGET_H_

#include <Wt/WContainerWidget.h>

#include <string>

#include "../Session.h"

namespace Wt {
class WStackedWidget;
class WAnchor;
}  // namespace Wt

class MenuWidget;
class WalletsListWidget;
class CurrenciesListWidget;

class MyMoneyWidget : public Wt::WContainerWidget {
   public:
    MyMoneyWidget();

    void handleInternalPath(const std::string& internalPath);

   private:
    void onAuthEvent();
    void showMenu();
    void showWalletList();
    void showCurrenciesList();

    Wt::WStackedWidget* main_stack_ = nullptr;
    MenuWidget* menu_widget_ = nullptr;
    WalletsListWidget* wallets_list_widget_ = nullptr;
    CurrenciesListWidget* currencies_list_widget_ = nullptr;

    Session session_;
};

#endif
