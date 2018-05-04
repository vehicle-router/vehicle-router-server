#include <utilities/device/device_query.h>
#include <cpprest/json.h>

#include "controller/device_query_controller.h"

using namespace device_query;
using namespace controller;
using namespace std;

Device_query_controller::~Device_query_controller() = default;

void Device_query_controller::handle_get(http_request& request) {
    using namespace conversions;

    vector<unique_ptr<Device_properties>> properties = get_cuda_device_properties();
    vector<json::value> device_elements;

    device_elements.reserve(properties.size());
    for (auto& property : properties) {
        json::value stats = json::value::object();

        stats[L"deviceName"] = json::value::string(to_string_t(property->device_name));
        stats[L"globalMemoryMegabytes"] = json::value::number(property->global_memory_in_mb);
        stats[L"maxThreadsPerBlock"] = json::value::number(property->maximum_threads_per_block);
        stats[L"computeCapability"] = json::value::string(to_string_t(property->compute_capability));
        stats[L"driverVersion"] = json::value::number(property->driver_version);

        device_elements.push_back(stats);
    }

    request.reply(status_codes::OK, json::value::array(device_elements));
}
