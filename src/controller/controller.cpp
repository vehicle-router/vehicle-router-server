#include "controller/controller.h"

using namespace controller;

Standard_controller::Standard_controller() {
    http_listener = new ::http_listener;
}

Standard_controller::Standard_controller(const uri& endpoint_uri) {
    http_listener = new ::http_listener(endpoint_uri);
}

Standard_controller::Standard_controller(const string_t& endpoint) {
    http_listener = new ::http_listener(uri(endpoint));
}

void Standard_controller::handle_get(http_request& request) {
    request.reply(status_codes::MethodNotAllowed, create_unsupported_response_json(methods::GET));
}

void Standard_controller::handle_put(http_request& request) {
    request.reply(status_codes::MethodNotAllowed, create_unsupported_response_json(methods::PUT));
}

void Standard_controller::handle_post(http_request& request) {
    request.reply(status_codes::MethodNotAllowed, create_unsupported_response_json(methods::POST));
}

void Standard_controller::handle_delete(http_request& request) {
    request.reply(status_codes::MethodNotAllowed, create_unsupported_response_json(methods::DEL));
}

Standard_controller::~Standard_controller() {
    delete http_listener;
}

void Standard_controller::initialize_http_handlers() {
    http_listener->support(methods::GET, [&](http_request& request) -> void { handle_get(request); });
    http_listener->support(methods::PUT, [&](http_request& request) -> void { handle_put(request); });
    http_listener->support(methods::POST, [&](http_request& request) -> void { handle_post(request); });
    http_listener->support(methods::DEL, [&](http_request& request) -> void { handle_delete(request); });
}


json::value Standard_controller::create_unsupported_response_json(const http::method& http_method) const {
    auto response = json::value::object();

    response[L"error"] = json::value::string(L"Method not allowed/implemented");
    response[L"httpMethod"] = json::value::string(http_method);

    return response;
}

void Standard_controller::set_endpoint(const utility::string_t& value) {
    delete http_listener;

    const uri new_endpoint(value);
    http_listener = new experimental::listener::http_listener(new_endpoint);
}

string_t Standard_controller::get_endpoint() const {
    return http_listener->uri().to_string();
}

pplx::task<void> Standard_controller::open() {
    initialize_http_handlers();

    return http_listener->open();
}

pplx::task<void> Standard_controller::close() const {
    return http_listener->close();
}

std::vector<string_t> Standard_controller::split_request_uri(const http_request& request) {
    const auto decoded = uri::decode(request.relative_uri().path());

    return uri::split_path(decoded);
}
