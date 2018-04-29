#include <iostream>
#include "interrupts.h"
#include "controller/router_controller.h"

int main(int argc, char* argv) {
    using namespace controller;
    using namespace routing;

    InterruptHandler::hookSIGINT();

    uri endpoint(L"http://localhost:6060/api");
    Standard_controller* controller{new Routing_endpoint_controller(endpoint)};

    try {
        controller->open();
        std::wcout << "Listening for requests at: " << controller->getEndpoint() << '\n';

        InterruptHandler::waitForUserInterrupt();

        controller->close().wait();
        delete controller;
    }
    catch (std::exception& e) {
        std::cerr << "Something went wrong " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Something went wrong " << std::endl;
    }

    return 0;
}
