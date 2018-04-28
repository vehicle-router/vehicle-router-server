#include "controller.h"

using namespace controller;

Standard_controller::Standard_controller() {
    http_listener = new ::http_listener;
}

Standard_controller::Standard_controller(uri& endpoint_uri) {
    http_listener = new ::http_listener(endpoint_uri);
}
Standard_controller::Standard_controller(string_t& endpoint) {
    http_listener = new ::http_listener(uri(endpoint));
}

void Standard_controller::handle_get(http_request request) {}
void Standard_controller::handle_put(http_request request) {}
void Standard_controller::handle_post(http_request request) {}
void Standard_controller::handle_delete(http_request request) {}

Standard_controller::~Standard_controller() {
    delete http_listener;
}

void Standard_controller::initialize_http_handlers() {}


json::value Standard_controller::responseNotImplemented(const http::method& http_method) {
    auto response = json::value::object();

    response[L"serviceName"] = json::value::string(L"C++ Rest SDK microservice");
    response[L"httpMethod"] = json::value::string(http_method);

    return response;
}

void Standard_controller::setEndpoint(const utility::string_t& value) {
    uri endpoint_uri(value);
    uri_builder endpoint_builder;

    endpoint_builder.set_scheme(endpoint_uri.scheme());

    if (endpoint_uri.host() == L"host_auto_ip4") {
        endpoint_builder.set_host(L"localhost");
    }

    endpoint_builder.set_port(endpoint_uri.port());
    endpoint_builder.set_path(endpoint_uri.path());

    http_listener = experimental::listener::http_listener(endpoint_builder.to_uri());
}

utility::string_t Standard_controller::getEndpoint() const {
    return http_listener.uri().to_string();
}

pplx::task<void> Standard_controller::accept() {
    initialize_http_handlers();

    return http_listener.open();
}

pplx::task<void> Standard_controller::shutdown() {
    return http_listener.close();
}

std::vector<utility::string_t> Standard_controller::requestPath(const http_request& request) {
    const auto decoded = uri::decode(request.relative_uri().path());

    return uri::split_path(decoded);
}
