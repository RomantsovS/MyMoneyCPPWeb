#include <Wt/WServer.h>

#include "MyMoneyApp.h"
#include "Session.h"

using namespace Wt;

int main(int argc, char **argv) {
    try {
        WServer server(argc, argv, WTHTTP_CONFIGURATION);

        server.addEntryPoint(EntryPointType::Application, createApplication);

        Session::configureAuth();

        server.run();
    } catch (WServer::Exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }
}
