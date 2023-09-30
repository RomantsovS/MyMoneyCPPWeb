#include "CurrenciesListWidget.h"

#include <Wt/WHBoxLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>

#include <vector>

#include "../Session.h"

using namespace Wt;

CurrenciesListWidget::CurrenciesListWidget(Session *session) : session_(session) {
    setContentAlignment(AlignmentFlag::Center);
    setStyleClass("green-box");

    auto vbox = setLayout(std::make_unique<WVBoxLayout>());
    auto top_hbox = vbox->addLayout(std::make_unique<WHBoxLayout>());

    auto item_text = std::make_unique<WText>(tr("mymoney.currenciesList"));
    item_text->setStyleClass("green-box");
    top_hbox->addWidget(std::move(item_text));

    auto item_add = std::make_unique<WText>("Add");
    item_add->setStyleClass("blue-box");
    top_hbox->addWidget(std::move(item_add));

    auto table = std::make_unique<WTable>();
    auto table_ = table.get();
    table_->setStyleClass("green-box");
    vbox->addWidget(std::move(table));

    table_->elementAt(0, 0)->addNew<WText>("Name");
    table_->setHeaderCount(1);
}

void CurrenciesListWidget::update() {
    auto currencies = session_->currencies(10);

    for (auto &currency : currencies) {
        int row = table_->rowCount();
        table_->elementAt(row, 0)->addNew<WText>(currency.name());
    }
}