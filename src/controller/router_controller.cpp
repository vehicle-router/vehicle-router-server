#include "controller/router_controller.h"

#include <routing/routing.h>
#include <spdlog/spdlog.h>

using namespace controller;
using namespace routing;

Routing_endpoint_controller::~Routing_endpoint_controller() = default;

inline std::vector<Node> parse_nodes(json::array& nodes_json) {
    const auto size = nodes_json.size();
    std::vector<Node> nodes;

    nodes.reserve(size);
    for (http_headers::size_type i = 0; i < size; ++i) {
        auto node = nodes_json.at(i).as_object();

        nodes.push_back({
            node.at(L"indice").as_integer(),
            node.at(L"x").as_integer(),
            node.at(L"y").as_integer(),
            static_cast<unsigned>(node.at(L"demand").as_integer())
        });
    }

    return nodes;
}

inline json::value create_visited_nodes_array(std::list<long>& visited_nodes) {
    size_t i = 0;
    json::value visited_nodes_json = json::value::array(visited_nodes.size());

    for (auto& node : visited_nodes) {
        visited_nodes_json[i++] = json::value::number(node);
    }

    return visited_nodes_json;
}

inline json::value map_routes_to_json(std::forward_list<Route>& routes) {
    size_t i = 0;
    json::value routes_json = json::value::array();

    for (auto& route : routes) {
        routes_json[i] = json::value::object(true);

        routes_json.at(i)[L"metDemand"] = json::value::number(route.met_demand);
        routes_json.at(i++)[L"nodes"] = create_visited_nodes_array(route.nodes);
    }

    return routes_json;
}

void Routing_endpoint_controller::handle_post(http_request& request) {
    auto path = split_request_uri(request);
    const bool single_argument = path.size() == 1;

    if (single_argument && path[0] == L"sequential") {
        request.extract_json().then([=](json::value& body) -> void {
            try {
                json::array nodes_json = body.at(L"nodes").as_array();
                auto routes = route(parse_nodes(nodes_json), body.at(L"vehicle_capacity").as_integer());

                request.reply(status_codes::OK, map_routes_to_json(routes));
            }
            catch (json::json_exception& e) {
                spdlog::get("vehicle-router-server")->error("Bad JSON format: {}", e.what());
                request.reply(status_codes::BadRequest);
            }
        });
    }
    else if (single_argument && path[0] == L"parallel") {
        request.extract_json().then([=](json::value& body) -> void {
            try {
                json::array nodes_json = body.at(L"nodes").as_array();
                auto routes = route_parallel(&parse_nodes(nodes_json)[0], nodes_json.size(),
                                             body.at(L"vehicle_capacity").as_integer());

                request.reply(status_codes::OK, map_routes_to_json(routes));
            }
            catch (json::json_exception& e) {
                spdlog::get("vehicle-router-server")->error("Bad JSON format: {}", e.what());
                request.reply(status_codes::BadRequest);
            }
        });
    }
    else {
        request.reply(status_codes::NotFound);
    }
}
