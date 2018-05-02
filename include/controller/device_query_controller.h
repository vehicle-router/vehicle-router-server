#pragma once

#include "controller.h"

namespace controller {

    class Device_query_controller : public Standard_controller {
        
    public:
        Device_query_controller() = default;

        Device_query_controller(const uri& endpoint_uri): Standard_controller(endpoint_uri) {}

        virtual ~Device_query_controller();

        void handle_get(http_request& request) override;
    };
}
