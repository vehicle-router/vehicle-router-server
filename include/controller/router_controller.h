#pragma once
#include "controller.h"

namespace routing {

    using namespace controller;

    class Routing_endpoint_controller : public Standard_controller {

    public:
        Routing_endpoint_controller() = default;

        Routing_endpoint_controller(uri& endpoint_uri): Standard_controller(endpoint_uri) {}

        virtual ~Routing_endpoint_controller();

        void handle_get(http_request& request) override;
    };
}
