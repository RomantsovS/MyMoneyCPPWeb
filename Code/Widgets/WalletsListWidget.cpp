#include "WalletsListWidget.h"

#include <Wt/WPushButton.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>

#include <vector>

#include "../Session.h"

using namespace Wt;

WalletsListWidget::WalletsListWidget(Session *session) : session_(session) {
    setContentAlignment(AlignmentFlag::Center);
}

void WalletsListWidget::update() {
    clear();

    addNew<WText>(tr("mymoney.walletsList"));

    auto wallets = session_->wallets(10);

    auto *table = addNew<WTable>();

    table->elementAt(0, 0)->addNew<WText>("Name");
    table->setHeaderCount(1);

    for (auto &wallet : wallets) {
        int row = table->rowCount();
        table->elementAt(row, 0)->addNew<WText>(wallet.name());
    }
}