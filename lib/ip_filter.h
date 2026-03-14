#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>

using ip_pool_t = std::vector<std::vector<std::string>>;

std::vector<std::string> split(const std::string &str, char d);
void reverse_sort(ip_pool_t& ip_pool);
void print_ip_by_iter(ip_pool_t::const_iterator ip_iter);
ip_pool_t filter(const std::string& first, const ip_pool_t& ip_pool);
ip_pool_t filter(const std::string& first, const std::string& second, const ip_pool_t& ip_pool);
ip_pool_t filter_any(const std::string& value, const ip_pool_t& ip_pool);
void sort_filter_and_print();