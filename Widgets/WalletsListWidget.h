#ifndef WALLETS_WIDGET_H_
#define WALLETS_WIDGET_H_

#include <Wt/WContainerWidget.h>

#include <string>

namespace Wt {
class WStackedWidget;
class WPushButton;
}  // namespace Wt

class Session;

class WalletsListWidget : public Wt::WContainerWidget {
   public:
    WalletsListWidget(Session *session);
    void update();

   private:
    Session *session_ = nullptr;
};

#endif
