#include <iostream>
#include <map>

template <class T, size_t Count = 10>
class MyAllocator
{
public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    template <class U>
    struct rebind
    {
        using other = MyAllocator<U, Count>;
    };

    MyAllocator() noexcept {}

    template <class U>
    MyAllocator(const MyAllocator<U, Count> &) noexcept {}

    T *allocate(std::size_t n)
    {
        if (n > Count)
        {
            throw std::bad_alloc();
        }
        if (auto p = static_cast<T *>(std::malloc(n * sizeof(T))))
        {
            return p;
        }
        throw std::bad_alloc();
    }

    void deallocate(T *p, std::size_t) noexcept
    {
        std::free(p);
    }
};

template <typename T>
using MyMap = std::map<int, T, std::less<int>, MyAllocator<std::pair<const int, T>>>;

int factorial(int n)
{
    return (n == 0) ? 1 : n * factorial(n - 1);
}

int main()
{
    // Создание экземпляра std::map<int, int>
    std::map<int, int> map1;

    // Заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
    for (int i = 0; i < 10; ++i)
    {
        map1.emplace(i, factorial(i));
    }

    // Создание экземпляра std::map<int, int> с новым аллокатором, ограниченным 10 элементами
    MyMap<int> map2;

    // Заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
    for (int i = 0; i < 10; ++i)
    {
        map2.emplace(i, factorial(i));
    }

    // Вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
    std::cout << "\nВывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере:" << std::endl;
    for (const auto &[key, value] : map2)
    {
        std::cout << key << " " << value << std::endl;
    }

    // Создание экземпляра своего контейнера для хранения значений типа int
    MyMap<int> myMap1;

    // Заполнение 10 элементами от 0 до 9
    for (int i = 0; i < 10; ++i)
    {
        myMap1.emplace(i, i);
    }

    // Создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором, ограниченным 10 элементами
    MyMap<int> myMap2;

    // Заполнение 10 элементами от 0 до 9
    for (int i = 0; i < 10; ++i)
    {
        myMap2.emplace(i, i);
    }
    // Вывод на экран всех значений, хранящихся в контейнере
    std::cout << "\nВывод на экран всех значений, хранящихся в контейнере:" << std::endl;
    for (const auto &[key, value] : myMap2)
    {
        std::cout << key << " " << value << std::endl;
    }

    return 0;
} 
