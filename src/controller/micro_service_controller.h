#pragma once
#include "controller.h"

class MicroServiceController : public Controller, Handler {

	json::value responseNotImplemented(const http::method& http_method);
public:
	MicroServiceController(): Controller() {}

	~MicroServiceController() {}

	void handleGet(http_request request) override;

	void handlePut(http_request request) override;

	void handlePost(http_request request) override;

	void handleDelete(http_request request) override;

	void initializeRestHandlers() override;
};
