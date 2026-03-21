#include <stdarg.h>

#include "ip_filter.h"

ip_t split(const std::string &str, char d)
{
    ip_t r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

uint32_t transform_ip_to_number(const ip_t& ip)
{
    static const uint32_t ip_octets_size = 4;

    uint32_t ip_as_number = 0;
    for (uint32_t i = 0; i < ip_octets_size; ++i)
    {
        uint32_t num = static_cast<uint32_t>(std::stoul(ip.at(i)));
        if (num > 255)
        {
            throw std::runtime_error("Invalid ip part value");
        }
        ip_as_number += num << (8 * (3-i));
    }

    return ip_as_number;
}

void reverse_sort(ip_pool_t& ip_pool)
{  
    std::stable_sort(ip_pool.begin(), ip_pool.end(), [](const ip_t& a, const ip_t& b)
                                                     {
                                                         return transform_ip_to_number(a) > transform_ip_to_number(b);
                                                     });
}

void print_ip_by_iter(ip_pool_t::const_iterator ip_iter)
{
    for(auto ip_part = ip_iter->cbegin(); ip_part != ip_iter->cend(); ++ip_part)
    {
        if (ip_part != ip_iter->cbegin())
        {
            std::cout << ".";
        }
        std::cout << *ip_part;
    }
    std::cout << std::endl;
}

ip_pool_t filter_any(const ip_pool_t& ip_pool, const std::string& octet_value)
{
    ip_pool_t filtered;
    for (auto ip_iter = ip_pool.cbegin(); ip_iter != ip_pool.cend(); ++ip_iter)
    {
        if (std::any_of(ip_iter->cbegin(), ip_iter->cend(), 
                [&octet_value](const std::string& str){ return str == octet_value; })
            )
        {
            filtered.push_back(*ip_iter);
        }
    }
    return filtered;
}
