#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>

using ip_t      = std::vector<std::string>;
using ip_pool_t = std::vector<ip_t>;

ip_t split(const std::string &str, char d);
void reverse_sort(ip_pool_t& ip_pool);
void print_ip_by_iter(ip_pool_t::const_iterator ip_iter);

template<typename... Args>
ip_pool_t filter(const ip_pool_t& ip_pool, const Args... octet_values)
{
    std::vector<std::string> ip_octets = { octet_values... };
    ip_pool_t filtered;
    
    for (const auto& ip : ip_pool)
    {
        auto temp_ip = std::vector<std::string>(ip.begin(), ip.begin() + ip_octets.size());
        if (ip_octets == temp_ip)
        {
            filtered.push_back(ip);
        }
    }

    return filtered;
}

ip_pool_t filter_any(const ip_pool_t& ip_pool, const std::string& octet_value);
void sort_filter_and_print();