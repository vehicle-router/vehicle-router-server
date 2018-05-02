#include "controller/device_query_controller.h"

using namespace controller;

Device_query_controller::~Device_query_controller() = default;

void Device_query_controller::handle_get(http_request& request) {


    request.reply(status_codes::OK);
}
