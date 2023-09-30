#include "MyMoneyApp.h"

#include <string>

#include "MyMoneyWidget.h"

MyMoneyApp::MyMoneyApp(const Wt::WEnvironment& env) : WApplication(env) {
    setTitle("My money");

    messageResourceBundle().use(appRoot() + "strings");

    useStyleSheet("css/mymoney.css");

    root()->addNew<MyMoneyWidget>();
}

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env) {
    return std::make_unique<MyMoneyApp>(env);
}