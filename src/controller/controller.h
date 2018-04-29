#pragma once

#include <string>
#include <pplx/pplxtasks.h>
#include <cpprest/http_listener.h>
#include "handler.h"

namespace controller {

    using namespace handler;
    using namespace utility;
    using namespace experimental::listener;

    class Standard_controller : Http_request_handler {
    protected:
        http_listener* http_listener;

        json::value create_unsupported_response_json(const method& http_method) const;

        void initialize_http_handlers();
    public:
        Standard_controller();

        Standard_controller(uri& endpoint_uri);

        Standard_controller(string_t& endpoint);

        virtual ~Standard_controller();

        void handle_get(http_request& request) override;

        void handle_put(http_request& request) override;

        void handle_post(http_request& request) override;

        void handle_delete(http_request& request) override;

        void setEndpoint(const string_t& value);

        string_t getEndpoint() const;

        pplx::task<void> open();

        pplx::task<void> close() const;

        static std::vector<string_t> split_request_uri(const http_request& request);
    };
}
