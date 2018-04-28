#pragma once

#include <cpprest/http_msg.h>

namespace handler {

    using namespace web::http;

    class Http_request_handler {
    public:
        virtual ~Http_request_handler() {};

        virtual void handle_get(http_request request) = 0;

        virtual void handle_put(http_request request) = 0;

        virtual void handle_post(http_request request) = 0;

        virtual void handle_delete(http_request request) = 0;
    };
}
