#include "ip_filter.h"

int main()
{
    try
    {
        ip_pool_t ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        reverse_sort(ip_pool);
        ip_pool_t filtered_by_first            = filter("1", ip_pool);
        ip_pool_t filtered_by_first_and_second = filter("46", "70", ip_pool);
        ip_pool_t filtered_by_any              = filter_any("46", ip_pool);

        ip_pool.insert(ip_pool.end(), filtered_by_first.begin(), filtered_by_first.end());
        ip_pool.insert(ip_pool.end(), filtered_by_first_and_second.begin(), filtered_by_first_and_second.end());
        ip_pool.insert(ip_pool.end(), filtered_by_any.begin(), filtered_by_any.end());

        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            print_ip_by_iter(ip);
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}