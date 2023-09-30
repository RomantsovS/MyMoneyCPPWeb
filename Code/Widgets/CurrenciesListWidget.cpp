#include "CurrenciesListWidget.h"

#include <Wt/WApplication.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WTableView.h>
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

    auto add_button = std::make_unique<WPushButton>(tr("mymoney.add"));
    add_button_ = add_button.get();
    add_button_->clicked().connect(this, &CurrenciesListWidget::add);
    add_button_->setStyleClass("blue-box");
    top_hbox->addWidget(std::move(add_button));

    auto tableView = std::make_unique<WTableView>();
    tableView->setModel(session_->getQueryModel<Currency>());
    // tableView->setRowHeaderCount(1);  // treat first column as 'fixed' row headers
    tableView->setSortingEnabled(false);
    tableView->setAlternatingRowColors(true);
    tableView->setRowHeight(28);
    tableView->setHeaderHeight(28);
    tableView->setSelectionMode(SelectionMode::Single);
    tableView->setEditTriggers(EditTrigger::None);
    vbox->addWidget(std::move(tableView));
}

void CurrenciesListWidget::add() {
    WApplication::instance()->setInternalPath("/currenciesList/add", true);
}

void CurrenciesListWidget::edit() {
    WApplication::instance()->setInternalPath("/currenciesList/edit", true);
}