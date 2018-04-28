#pragma once

#include <string>
#include <pplx/pplxtasks.h>
#include <cpprest/http_listener.h>
#include "handler.h"

namespace controller {

    using namespace utility;
    using namespace web;
    using namespace http;
    using namespace experimental::listener;

    class Standard_controller : handler::Http_request_handler {
    protected:
        http_listener* http_listener;

        json::value responseNotImplemented(const http::method& http_method);
    public:
        Standard_controller();

        Standard_controller(uri& endpoint_uri);

        Standard_controller(string_t& endpoint);

        virtual ~Standard_controller();

        void handle_get(http_request request) override;

        void handle_put(http_request request) override;

        void handle_post(http_request request) override;

        void handle_delete(http_request request) override;

        virtual void initialize_http_handlers();

        void setEndpoint(const utility::string_t& value);

        utility::string_t getEndpoint() const;

        pplx::task<void> accept();

        pplx::task<void> shutdown();

        std::vector<utility::string_t> requestPath(const http_request& request);
    };
}
