#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

template <typename T>
class MyAllocator {
public:
    template <typename U>
    struct rebind {
        typedef MyAllocator<U> other;
    };

    MyAllocator() noexcept {}
    template <typename U>
    MyAllocator(const MyAllocator<U>& other) noexcept {}

    T* allocate(std::size_t n) {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
            throw std::bad_alloc();
        }
        if (auto p = static_cast<T*>(std::malloc(n * sizeof(T)))) {
            return p;
        }
        throw std::bad_alloc();
    }

    void deallocate(T* p, std::size_t) noexcept {
        std::free(p);
    }
};


std::array<u_int8_t, 4> split(const std::string &str, char d)
{
    std::array<u_int8_t, 4> r;
    int i = 0;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r[i] = std::stoi(str.substr(start, stop - start));
        start = stop + 1;
        i++;
        stop = str.find_first_of(d, start);
    }

    r[i] = std::stoi(str.substr(start));

    return r;
}

void separattor()
{
    std::cout << std::endl;
    std::cout << "********************************************" << std::endl;
    std::cout << std::endl;
}

void print(const std::vector<std::array<uint8_t, 4>, MyAllocator<std::array<uint8_t, 4>>> &ip_pool)
{
    for (int i = 0; i < ip_pool.size(); i++)
    {
        printArray(ip_pool[i]);
    }
}

void printArray(const std::array<uint8_t, 4> &ip)
{
    std::cout << unsigned(ip[0]) << "." << unsigned(ip[1]) << "." << unsigned(ip[2]) << "." << unsigned(ip[3]) << std::endl;
}

int main(int argc, char const *argv[])
{
    try
    {

        std::vector<std::array<uint8_t, 4>, MyAllocator<std::array<uint8_t, 4>>> ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            size_t pos = line.find_first_of('\t');
            std::string ip_str = line.substr(0, pos);
            ip_pool.push_back(split(ip_str, '.'));
        }

        // TODO reverse lexicographically sort
        sort(ip_pool.rbegin(), ip_pool.rend());
        print(ip_pool);

        separattor();

        for (const auto &addr : ip_pool)
        {
            if (addr[0] == 1)
            {
                printArray(addr);
            }
        }

        separattor();

        for (const auto &addr : ip_pool)
        {
            if (addr[0] == 46 && addr[1] == 70)
            {
                printArray(addr);
            }
        }

        separattor();

        for (const auto &addr : ip_pool)
        {
            if (std::find(addr.begin(), addr.end(), 46) != addr.end())
            {
                printArray(addr);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}