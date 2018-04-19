#pragma once

#include <string>
#include <pplx/pplxtasks.h>
#include <cpprest/http_listener.h>
#include "handler.h"

class Controller {

	experimental::listener::http_listener http_listener;
public:
	Controller();

	~Controller();

	virtual void initializeRestHandlers();

	void setEndpoint(const utility::string_t& value);

	utility::string_t getEndpoint() const;

	pplx::task<void> accept();

	pplx::task<void> shutdown();

	std::vector<utility::string_t> requestPath(const http_request& request);
};
