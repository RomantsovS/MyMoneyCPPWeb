#include "MenuWidget.h"

#include <Wt/WApplication.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

using namespace Wt;

MenuWidget::MenuWidget() {
    setContentAlignment(AlignmentFlag::Center);

    title_ = addNew<WText>(tr("mymoney.menu"));

    wallets_button_ = addNew<WPushButton>(tr("mymoney.openWalletsList"));
    wallets_button_->clicked().connect(this, &MenuWidget::openWalletsList);

    currencies_button_ = addNew<WPushButton>(tr("mymoney.openCurrenciesList"));
    currencies_button_->clicked().connect(this, &MenuWidget::openCurrenciesList);
}

void MenuWidget::openWalletsList() {
    WApplication::instance()->setInternalPath("/walletsList", true);
}

void MenuWidget::openCurrenciesList() {
    WApplication::instance()->setInternalPath("/currenciesList", true);
}