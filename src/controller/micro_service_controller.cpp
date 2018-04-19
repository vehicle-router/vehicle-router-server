#include "micro_service_controller.h"

void MicroServiceController::initializeRestHandlers() {
	http_listener.support(methods::GET, std::bind(&MicroServiceController::handleGet, this, std::placeholders::_1));
	http_listener.support(methods::PUT, std::bind(&MicroServiceController::handlePut, this, std::placeholders::_1));
	http_listener.support(methods::POST, std::bind(&MicroServiceController::handlePost, this, std::placeholders::_1));
	http_listener.support(methods::DEL, std::bind(&MicroServiceController::handleDelete, this, std::placeholders::_1));
}


json::value MicroServiceController::responseNotImplemented(const http::method& http_method) {
	auto response = json::value::object();

	response[L"serviceName"] = json::value::string(L"C++ Rest SDK microservice");
	response[L"httpMethod"] = json::value::string(http_method);

	return response;
}

void MicroServiceController::handleGet(http_request request) {
	auto path = requestPath(request);

	std::cout << "Handling GET \n";
	if (!path.empty()) {
		request.reply(status_codes::OK);
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
