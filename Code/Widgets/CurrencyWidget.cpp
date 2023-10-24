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

CurrencyWidget::CurrencyWidget(Session* session, const std::string& id)
    : session_(session), id_(id) {
    setContentAlignment(AlignmentFlag::Center);
    setStyleClass("green-box");

    auto vbox = setLayout(std::make_unique<WVBoxLayout>());
    auto top_hbox = vbox->addLayout(std::make_unique<WHBoxLayout>());

    auto item_text = std::make_unique<WText>(tr("mymoney.currency"));
    item_text->setStyleClass("green-box");
    top_hbox->addWidget(std::move(item_text));

    auto save_button = std::make_unique<WPushButton>(tr("mymoney.save"));
    save_button_ = save_button.get();
    save_button->clicked().connect(this, &CurrencyWidget::save);
    save_button->setStyleClass("blue-box");
    top_hbox->addWidget(std::move(save_button));

    auto name_edit = std::make_unique<WLineEdit>();
    name_edit_ = name_edit.get();
    name_edit_->setStyleClass("white-box");

    if (!id_.empty()) {
        auto t = session_->make_transaction();
        auto id = Currency::stringToId(id_);
        auto dbo_ptr_ = session_->load<Currency>(id);
        name_edit_->setText(dbo_ptr_->getName());
    }

    vbox->addWidget(std::move(name_edit));
}

void CurrencyWidget::save() {
    auto t = session_->make_transaction();

    if (id_.empty()) {
        auto currency = std::make_unique<Currency>(name_edit_->text().toUTF8());
        session_->add(std::move(currency));
    } else {
        auto id = Currency::stringToId(id_);
        auto dbo_ptr_ = session_->load<Currency>(id);
        auto object = dbo_ptr_.modify();
        object->setName(name_edit_->text().toUTF8());
    }

    t->commit();

    WApplication::instance()->setInternalPath("/currenciesList", true);
}