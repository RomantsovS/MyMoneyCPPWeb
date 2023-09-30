#include <Wt/WServer.h>

#include "MyMoneyApp.h"
#include "Session.h"

int main(int argc, char **argv) {
    try {
        Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

        server.addEntryPoint(Wt::EntryPointType::Application, createApplication);

        Session::configureAuth();

        server.run();
    } catch (Wt::WServer::Exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }
}
