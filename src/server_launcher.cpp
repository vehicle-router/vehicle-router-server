#include <vector>
#include <memory>
#include <spdlog/spdlog.h>
#include <cpprest/asyncrt_utils.h>

#include "interrupts.h"
#include "controller/router_controller.h"
#include "controller/device_query_controller.h"

using namespace controller;

inline std::vector<Standard_controller*> register_controllers();

int main(int argc, char* argv) {
    using namespace controller;

    InterruptHandler::hookSIGINT();

    auto logger = spdlog::stdout_color_st("vehicle-router-server");
    auto controllers = register_controllers();

    try {
        std::for_each(controllers.begin(), controllers.end(), [&](Standard_controller* controller) -> void {

            controller->open();
            logger->info("Endpoint opened at: {}", conversions::to_utf8string(controller->get_endpoint()));
        });

        InterruptHandler::waitForUserInterrupt();

        std::for_each(controllers.begin(), controllers.end(), [&](Standard_controller* controller) -> void {
            controller->close().wait();
        });
    }
    catch (std::exception& e) {
        logger->error("An error occurred: {}", e.what());
    }
    catch (...) {
        logger->error("An error occurred");
    }

    return 0;
}

inline std::vector<Standard_controller*> register_controllers() {

    Standard_controller* c1 = new Routing_endpoint_controller(uri(L"http://localhost:6060/routing"));
    Standard_controller* c2 = new Device_query_controller(uri(L"http://localhost:6060/devices"));

    return std::vector<Standard_controller*>{c1, c2};
}
