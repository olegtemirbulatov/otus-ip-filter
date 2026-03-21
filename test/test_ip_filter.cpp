#include <sstream>

#include <gtest/gtest.h>
#include "ip_filter.h"

ip_pool_t make_input_ip_pool()
{
    static const ip_t ip_strings = {
        "46.70.113.73",
        "73.87.94.81",
        "5.62.159.140",
        "14.231.215.204",
        "73.87.94.81",
        "68.202.216.62",
        "1.87.203.225",
        "47.149.142.171",
        "5.189.203.79",
        "68.202.216.62",
        "47.149.142.171"
    };

    ip_pool_t ip_pool;
    for (auto& ip_string : ip_strings)
    {
        ip_pool.push_back(split(ip_string, '.'));
    }
    return ip_pool;
}

TEST(TestIpSort, TestReverseSort)
{
    const ip_pool_t ip_pool_expected = {
        {"73", "87", "94",  "81"},
        {"73", "87", "94",  "81"},
        {"68", "202", "216", "62"},
        {"68", "202", "216", "62"},
        {"47", "149", "142", "171"},
        {"47", "149", "142", "171"},
        {"46", "70",  "113", "73"},
        {"14", "231", "215", "204"},
        {"5",  "189", "203", "79"},
        {"5",  "62",  "159", "140"},
        {"1",  "87",  "203", "225"}
    };

    ip_pool_t ip_pool   = make_input_ip_pool();
    reverse_sort(ip_pool);

    ASSERT_EQ(ip_pool, ip_pool_expected);
}

TEST(TestIpSort, TestFilterByFirst)
{
    const ip_pool_t ip_pool_expected = {
        {"5",  "189", "203", "79"},
        {"5",  "62",  "159", "140"}
    };

    ip_pool_t ip_pool          = make_input_ip_pool();
    ip_pool_t filtered_ip_pool = filter(ip_pool, std::string("5"));
    reverse_sort(filtered_ip_pool);

    ASSERT_EQ(filtered_ip_pool, ip_pool_expected);
}

TEST(TestIpSort, TestFilterByFirstAndSecond)
{
    const ip_pool_t ip_pool_expected = {
        {"5",  "189", "203", "79"}
    };

    ip_pool_t ip_pool          = make_input_ip_pool();
    ip_pool_t filtered_ip_pool = filter(ip_pool, std::string("5"), std::string("189"));
    reverse_sort(filtered_ip_pool);

    ASSERT_EQ(filtered_ip_pool, ip_pool_expected);
}

TEST(TestIpSort, TestFilterByAny)
{
    const ip_pool_t ip_pool_expected = {
        {"14", "231", "215", "204"}
    };

    ip_pool_t ip_pool          = make_input_ip_pool();
    ip_pool_t filtered_ip_pool = filter_any(ip_pool, std::string("215"));
    reverse_sort(filtered_ip_pool);

    ASSERT_EQ(filtered_ip_pool, ip_pool_expected);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}