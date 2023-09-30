#ifndef MY_MONEY_APP_H
#define MY_MONEY_APP_H

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>

#include <memory>

class MyMoneyWidget;

class MyMoneyApp : public Wt::WApplication {
   public:
    MyMoneyApp(const Wt::WEnvironment& env);

   private:
    MyMoneyWidget* my_money_widget = nullptr;
};

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env);

#endif