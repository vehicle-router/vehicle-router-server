#include <boost/asio.hpp>

#include "network/network_utils.h"

using namespace boost::asio;
using namespace ip;

using host_inet_info = tcp::resolver::iterator;

host_inet_info get_endpoint_entries() {
    io_service ios;
    const tcp::resolver::query query(host_name(), "");

    return tcp::resolver(ios).resolve(query);
}

std::string utils::get_host_ipv4() {
    auto entries = get_endpoint_entries();
    const tcp::resolver::iterator end;

    while (entries != end) {
        tcp::endpoint endpoint = *entries++;

        if (endpoint.data()->sa_family == AF_INET) {
            return endpoint.address().to_string();
        }
    }
    return nullptr;
}
