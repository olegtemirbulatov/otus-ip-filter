#include "ip_filter.h"

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

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

void reverse_sort(ip_pool_t& ip_pool)
{
    static const uint32_t ip_size = 4;
    
    // Преобразуем ip в число
    std::vector<uint32_t> ip_as_numbers;
    for (const auto& ip : ip_pool)
    {
        uint32_t ip_as_number = 0;
        for (uint32_t i = 0; i < ip_size; ++i)
        {
            uint32_t num = static_cast<uint32_t>(std::stoul(ip.at(i)));
            if (num > 255)
            {
                throw std::runtime_error("Invalid ip part value");
            }
            ip_as_number += num << (8 * (3-i));
        }
        ip_as_numbers.push_back(ip_as_number);
    }
    
    // Сортируем
    std::stable_sort(ip_as_numbers.begin(), ip_as_numbers.end(), std::greater<uint32_t>());
    
    // Преобразуем обратно число в ip
    for (size_t i = 0; i < ip_pool.size(); ++i)
    {
        for (size_t ip_part_index = 0; ip_part_index < ip_size; ++ip_part_index)
        {
            ip_pool.at(i).at(ip_part_index) = std::to_string((ip_as_numbers.at(i) >> (8 * (3-ip_part_index))) & 0xFF);
        }
    }
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

ip_pool_t filter(const std::string& first, const ip_pool_t& ip_pool)
{
    ip_pool_t filtered;
    for (auto ip_iter = ip_pool.cbegin(); ip_iter != ip_pool.cend(); ++ip_iter)
    {
        if (ip_iter->at(0) == first)
        {
            filtered.push_back(*ip_iter);
        }
    }
    return filtered;
}

ip_pool_t filter(const std::string& first, const std::string& second, const ip_pool_t& ip_pool)
{
    ip_pool_t filtered;
    for (auto ip_iter = ip_pool.cbegin(); ip_iter != ip_pool.cend(); ++ip_iter)
    {
        if (ip_iter->at(0) == first && ip_iter->at(1) == second)
        {
            filtered.push_back(*ip_iter);
        }
    }
    return filtered;
}

ip_pool_t filter_any(const std::string& value, const ip_pool_t& ip_pool)
{
    ip_pool_t filtered;
    for (auto ip_iter = ip_pool.cbegin(); ip_iter != ip_pool.cend(); ++ip_iter)
    {
        if (std::any_of(ip_iter->cbegin(), ip_iter->cend(), 
                [&value](const std::string& str){ return str == value; })
            )
        {
            filtered.push_back(*ip_iter);
        }
    }
    return filtered;
}
