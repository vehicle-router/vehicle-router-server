#include <iostream>
#include "interrupts.h"
#include "controller/micro_service_controller.h"

int main(int argc, char* argv) {
    InterruptHandler::hookSIGINT();

    Controller* controller{new MicroServiceController};

    controller->setEndpoint(L"http://host_auto_ip4:6060/api");

    try {
        controller->accept().wait();
        std::wcout << "Listening for requests at: " << controller->getEndpoint() << '\n';

        InterruptHandler::waitForUserInterrupt();

        controller->shutdown().wait();
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
