#include "MyMoneyWidget.h"

#include <Wt/Auth/AuthWidget.h>
#include <Wt/WApplication.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WText.h>

#include "CurrenciesListWidget.h"
#include "MenuWidget.h"
#include "WalletsListWidget.h"

using namespace Wt;

MyMoneyWidget::MyMoneyWidget() : main_stack_(addNew<WStackedWidget>()) {
    session_.login().changed().connect(this, &MyMoneyWidget::onAuthEvent);

    auto authModel = std::make_unique<Auth::AuthModel>(Session::auth(), session_.users());
    authModel->addPasswordAuth(&Session::passwordAuth());

    auto authWidget = std::make_unique<Auth::AuthWidget>(session_.login());
    auto authWidgetPtr = authWidget.get();
    authWidget->setModel(std::move(authModel));
    authWidget->setRegistrationEnabled(true);

    addWidget(std::move(authWidget));

    main_stack_->setStyleClass("gamestack");

    WApplication::instance()->internalPathChanged().connect(this,
                                                            &MyMoneyWidget::handleInternalPath);

    authWidgetPtr->processEnvironment();
}

void MyMoneyWidget::onAuthEvent() {
    if (session_.login().loggedIn()) {
        handleInternalPath(WApplication::instance()->internalPath());
    } else {
        main_stack_->clear();
        menu_widget_ = nullptr;
        WApplication::instance()->setInternalPath("/", true);
    }
}

void MyMoneyWidget::handleInternalPath(const std::string &internalPath) {
    if (session_.login().loggedIn()) {
        if (internalPath == "/menu")
            showMenu();
        else if (internalPath == "/walletsList")
            showWalletList();
        else if (internalPath == "/currenciesList")
            showCurrenciesList();
        else
            WApplication::instance()->setInternalPath("/menu", true);
    }
}

void MyMoneyWidget::showMenu() {
    if (!menu_widget_) {
        menu_widget_ = main_stack_->addNew<MenuWidget>();
    }

    main_stack_->setCurrentWidget(menu_widget_);
}

void MyMoneyWidget::showWalletList() {
    if (!wallets_list_widget_) {
        wallets_list_widget_ = main_stack_->addNew<WalletsListWidget>(&session_);
    }

    main_stack_->setCurrentWidget(wallets_list_widget_);
    wallets_list_widget_->update();
}

void MyMoneyWidget::showCurrenciesList() {
    if (!currencies_list_widget_) {
        currencies_list_widget_ = main_stack_->addNew<CurrenciesListWidget>(&session_);
    }

    main_stack_->setCurrentWidget(currencies_list_widget_);
    currencies_list_widget_->update();
}