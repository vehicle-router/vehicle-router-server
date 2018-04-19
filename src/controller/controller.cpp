#include "controller.h"

Controller::Controller() {}

Controller::~Controller() {}

void Controller::initializeRestHandlers() {}

void Controller::setEndpoint(const utility::string_t& value) {
	uri endpoint_uri(value);
	uri_builder endpoint_builder;

	endpoint_builder.set_scheme(endpoint_uri.scheme());

	if (endpoint_uri.host() == L"host_auto_ip4") {
		endpoint_builder.set_host(endpoint_uri.host());
	}

	endpoint_builder.set_port(endpoint_uri.port());
	endpoint_builder.set_path(endpoint_uri.path());

	http_listener = experimental::listener::http_listener(endpoint_builder.to_uri());
}

utility::string_t Controller::getEndpoint() const {
	return http_listener.uri().to_string();
}

pplx::task<void> Controller::accept() {
	initializeRestHandlers();

	return http_listener.open();
}

pplx::task<void> Controller::shutdown() {
	return http_listener.close();
}

std::vector<utility::string_t> Controller::requestPath(const http_request& request) {
	const auto decoded = uri::decode(request.relative_uri().path());

	return uri::split_path(decoded);
}
