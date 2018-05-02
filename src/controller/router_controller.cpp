#include "router_controller.h"

using namespace routing;

Routing_endpoint_controller::~Routing_endpoint_controller() = default;

void Routing_endpoint_controller::handle_get(http_request& request) {
    auto path = split_request_uri(request);

    if (!path.empty() && path[0] == L"test") {
        auto response = json::value::object();

        response[L"status"] = json::value::string(L"Online");
        response[L"version"] = json::value::string(L"0.1");

        request.reply(status_codes::OK, response);
    }
    else {
        request.reply(status_codes::NotFound);
    }
}
