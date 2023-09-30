#include "MyMoneyWidget.h"

#include <Wt/Auth/AuthWidget.h>
#include <Wt/WApplication.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WText.h>

#include "MenuWidget.h"

using namespace Wt;

MyMoneyWidget::MyMoneyWidget() : main_stack_(addNew<Wt::WStackedWidget>()) {
    session_.login().changed().connect(this, &MyMoneyWidget::onAuthEvent);

    addNew<WText>("<h1>My money</h1>");

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