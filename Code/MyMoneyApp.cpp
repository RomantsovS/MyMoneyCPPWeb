#include "MyMoneyApp.h"

#include <string>

#include "Widgets/MyMoneyWidget.h"

using namespace Wt;

MyMoneyApp::MyMoneyApp(const WEnvironment& env) : WApplication(env) {
    setTitle("My money");

    messageResourceBundle().use(appRoot() + "strings");

    useStyleSheet("css/mymoney.css");

    root()->addNew<MyMoneyWidget>();
}

std::unique_ptr<WApplication> createApplication(const WEnvironment& env) {
    return std::make_unique<MyMoneyApp>(env);
}