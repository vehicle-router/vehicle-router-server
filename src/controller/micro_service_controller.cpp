#include <router_library.h>
#include "micro_service_controller.h"

void MicroServiceController::initializeRestHandlers() {
    http_listener.support(methods::GET, [&](auto request) -> void { handleGet(request); });
    http_listener.support(methods::PUT, [&](auto request) -> void { handlePut(request); });
    http_listener.support(methods::POST, [&](auto request) -> void { handlePost(request); });
    http_listener.support(methods::DEL, [&](auto request) -> void { handleDelete(request); });
}


json::value MicroServiceController::responseNotImplemented(const http::method& http_method) const {
    auto response = json::value::object();

    response[L"serviceName"] = json::value::string(L"C++ Rest SDK microservice");
    response[L"httpMethod"] = json::value::string(http_method);

    return response;
}

void MicroServiceController::handleGet(http_request request) {
    auto path = requestPath(request);

    if (!path.empty() && path[0] == L"test") {
        auto response = json::value::object();

        response[L"status"] = json::value::string(L"Online");
        response[L"version"] = json::value::string(L"0.1");

        vr::executeInParallel();
        request.reply(status_codes::OK, response);
    }
    else {
        request.reply(status_codes::NotFound);
    }
}

void MicroServiceController::handlePut(http_request request) {
    request.reply(status_codes::NotImplemented, responseNotImplemented(methods::PUT));
}

void MicroServiceController::handlePost(http_request request) {
    request.reply(status_codes::NotImplemented, responseNotImplemented(methods::POST));
}

void MicroServiceController::handleDelete(http_request request) {
    request.reply(status_codes::NotImplemented, responseNotImplemented(methods::DEL));
}
