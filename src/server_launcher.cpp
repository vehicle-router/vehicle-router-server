#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <spdlog/spdlog.h>

#include "network/network_utils.h"
#include "interrupts.h"
#include "controller/router_controller.h"
#include "controller/device_query_controller.h"

using namespace controller;
using namespace utils;

inline std::vector<Standard_controller*> register_controllers(const string_t& scheme, const int& port);

int main(int argc, char* argv) {
    auto logger = spdlog::stdout_color_st("vehicle-router-server");

    try {
        auto controllers = register_controllers(L"http", 6060);
        std::for_each(controllers.begin(), controllers.end(), [&](Standard_controller* controller) -> void {
            controller->open().wait();
            logger->info("Endpoint opened at: {}", conversions::to_utf8string(controller->get_endpoint()));
        });

        Interrupt_handler::hook_sigint();
        Interrupt_handler::wait_for_sigint();

        std::for_each(controllers.begin(), controllers.end(), [&](Standard_controller* controller) -> void {
            controller->close().wait();

            delete controller;
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

inline std::vector<Standard_controller*> register_controllers(const string_t& scheme, const int& port) {
    uri_builder base_uri_builder{};

    base_uri_builder.set_scheme(scheme);
    base_uri_builder.set_host(conversions::to_string_t(get_host_ipv4()));
    base_uri_builder.set_port(port);

    Standard_controller* c1 = new Routing_endpoint_controller(uri_builder(base_uri_builder).set_path(L"routing/").to_uri());
    Standard_controller* c2 = new Device_query_controller(uri_builder(base_uri_builder).set_path(L"devices/").to_uri());

    return std::vector<Standard_controller*>{c1, c2};
}
