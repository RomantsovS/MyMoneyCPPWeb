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

CurrenciesListWidget::CurrenciesListWidget(Session* session) : session_(session) {
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

    auto table_view = std::make_unique<WTableView>();
    table_view_ = table_view.get();
    table_view_->setModel(session_->getQueryModel<Currency>());
    // table_view->setRowHeaderCount(1);  // treat first column as 'fixed' row headers
    table_view_->setSortingEnabled(false);
    table_view_->setAlternatingRowColors(true);
    table_view_->setRowHeight(28);
    table_view_->setHeaderHeight(28);
    table_view_->setSelectionMode(SelectionMode::Single);
    table_view_->setEditTriggers(EditTrigger::None);
    table_view_->doubleClicked().connect(this, &CurrenciesListWidget::edit);
    vbox->addWidget(std::move(table_view));
}

void CurrenciesListWidget::add() {
    WApplication::instance()->setInternalPath("/currenciesList/add", true);
}

void CurrenciesListWidget::edit() {
    std::string id;
    for (const auto& index : table_view_->selectedIndexes()) {
        Dbo::QueryModel<Dbo::ptr<Currency>>* item =
            static_cast<Dbo::QueryModel<Dbo::ptr<Currency>>*>(table_view_->model().get());
        id = std::to_string(item->resultRow(index.row()).id());
    }
    WApplication::instance()->setInternalPath("/currenciesList/edit/" + id, true);
}