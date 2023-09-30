#include "CurrencyWidget.h"

#include <Wt/WApplication.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>

#include <vector>

#include "../Session.h"

using namespace Wt;

CurrencyWidget::CurrencyWidget(Session *session) : session_(session) {
    setContentAlignment(AlignmentFlag::Center);
    setStyleClass("green-box");

    auto vbox = setLayout(std::make_unique<WVBoxLayout>());
    auto top_hbox = vbox->addLayout(std::make_unique<WHBoxLayout>());

    auto item_text = std::make_unique<WText>(tr("mymoney.currency"));
    item_text->setStyleClass("green-box");
    top_hbox->addWidget(std::move(item_text));

    auto save_button = std::make_unique<WPushButton>(tr("mymoney.save"));
    save_button_ = save_button.get();
    save_button_->clicked().connect(this, &CurrencyWidget::save);
    save_button_->setStyleClass("blue-box");
    top_hbox->addWidget(std::move(save_button));

    auto name_edit = std::make_unique<WLineEdit>();
    name_edit_ = name_edit.get();
    name_edit_->setStyleClass("white-box");
    vbox->addWidget(std::move(name_edit));
}

void CurrencyWidget::save() {
    auto currency = std::make_unique<Currency>(name_edit_->text().toUTF8());

    session_->add(std::move(currency));

    WApplication::instance()->setInternalPath("/currenciesList", true);
}