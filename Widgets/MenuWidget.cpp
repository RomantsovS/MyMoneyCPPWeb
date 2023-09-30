#include "MenuWidget.h"

#include <Wt/WPushButton.h>
#include <Wt/WText.h>

MenuWidget::MenuWidget() {
    setContentAlignment(Wt::AlignmentFlag::Center);

    title_ = addNew<Wt::WText>(tr("mymoney.readyToPlay"));

    wallets_button_ = addNew<Wt::WPushButton>(tr("memoney.openWalletsList"));
    wallets_button_->clicked().connect(this, &MenuWidget::openWalletsList);
}

void MenuWidget::openWalletsList() {}