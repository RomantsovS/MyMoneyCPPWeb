#ifndef CURRENCY_WIDGET_H_
#define CURRENCY_WIDGET_H_

#include <Wt/Dbo/ptr.h>
#include <Wt/WContainerWidget.h>

#include <string>

namespace Wt {
class WStackedWidget;
class WPushButton;
class WLineEdit;
}  // namespace Wt

class Session;
class Currency;

class CurrencyWidget : public Wt::WContainerWidget {
   public:
    CurrencyWidget(Session *session, const std::string &id);
    void save();

   private:
    Session *session_ = nullptr;
    Wt::WContainerWidget *top_panel = nullptr;
    Wt::WPushButton *save_button_ = nullptr;
    Wt::WLineEdit *name_edit_ = nullptr;
    std::string id_;
};

#endif
