#pragma once

#include <cpprest/http_msg.h>

using namespace web;
using namespace http;

class Handler {
public:
	virtual ~Handler() {};

	virtual void handleGet(http_request request) = 0;

	virtual void handlePut(http_request request) = 0;

	virtual void handlePost(http_request request) = 0;

	virtual void handleDelete(http_request request) = 0;
};
