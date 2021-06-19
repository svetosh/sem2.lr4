#include <exception>
#include <iostream>
#include <vector>
#include <string>

//using namespace std;

template<typename T>
class Vector
{
    T* _data;
    int _size;
    int _alloc_size;
    float magnifier = 1.5;

public:
    Vector() 
    {
        _data = nullptr;
        _size = 0;
        _alloc_size = 0;
    }

    explicit Vector(const int& size, float custom_magnifier = 1.5)
    {
        magnifier = custom_magnifier;
        _alloc_size = size;
        _data = new T[size];
    }

    ~Vector()
    {
        delete[] _data;
    }
};


class some_exception : public std::exception
{
public:
    char _what[27];

    some_exception(const char a[])
    {
        for (int i = 0; i < 27; ++i) 
        {
            _what[i] = a[i];
        }
    }
    ~some_exception() override
    {
        std::cout << "404" << std::endl;
    }
};

struct some_data 
{
    char data;
    some_data(char ch)
    {
        data = ch;
    }
};

void
some_function(some_data c)
{
    if (c.data == 'i') {
        throw some_exception(" cool ");
    }
}

class test1
{
public:
    virtual ~test1()
    {
    }
};

class test2
{
public:
    virtual ~test2()
    {
    }
};

int
main() 
{
    setlocale(LC_ALL, "ru");
    int what;
    std::cout << "0 - 1й режим работы    1 - 2й режим работы" << std::endl;
    std::cin >> what;

    if (what == 0)
    {
        std::cout << " Стандартные исключения и настраиваемые." << std::endl;
        std::vector<unsigned char> v = { 'a', 'b', 'c', 'd', 'e' };
        std::cout << std::endl;

        try 
        {
            std::cout << "Попытка получить vec[vec.size()]" << std::endl;
            v.at(v.size());
        }
        catch (const std::out_of_range& error) 
        {
            std::cout << "ОШИБКА: " << error.what() << std::endl;
        }
        std::cout << std::endl << std::endl;

        try 
        {
            std::cout << "Попытка изменить размер вектора до size = -5" << std::endl;
            v.resize(-5);
        }
        catch (const std::length_error& error) 
        {
            std::cout << "ОШИБКА: " << error.what() << std::endl;
        }
        std::cout << std::endl << std::endl;

        try 
        {
            std::cout << "Попытка получить int из world " << std::endl;
            std::stoi("world");
        }
        catch (const std::invalid_argument& error) 
        {
            std::cout << "ОШИБКА: " << error.what()
                << std::endl;
        }
        std::cout << std::endl << std::endl;

        try 
        {
            test1 test_1;
            std::cout << "Пытаюсь сделать test1 из test2 " << std::endl;
            dynamic_cast<test2&>(test_1);
        }
        catch (const std::bad_cast& error) 
        {
            std::cout << "ОШИБКА: " << error.what() << std::endl;
        }
        std::cout << std::endl << std::endl;

        try 
        {
            std::cout << "Попытка выделить слишком много памяти" << std::endl;
            int sz = -1;
            new int[sz];
        }
        catch (const std::bad_alloc& error) 
        {
            std::cout << "ОШИБКА: " << error.what() << std::endl;
        }
        std::cout << std::endl << std::endl;

        try 
        {
            some_data smth('i');
            std::cout << "Попытка  " << std::endl;
            some_function(smth);
        }
        catch (const some_exception& error) 
        {
            std::cout << "ОШИБКА: " << error._what << std::endl;
        }
        std::cout << std::endl << std::endl;

    }
    else 
    {
        std::cout << "Методы программирования без RAII и RAII" << std::endl;
        std::cout << std::endl << std::endl;

        try 
        {
            std::cout << "У нас есть int* some_pointer" << std::endl;
            int* some_pointer = nullptr;
            std::cout << "Выделим для него память" << std::endl;
            some_pointer = new int[100];
            std::cout << "Но затем что-то вызывает исключение." << std::endl;
            throw " exception ";
            delete[] some_pointer;
        }
        catch (const char* error) 
        {
            std::cout << "ошибка: " << error << std::endl << std::endl;
            std::cout << "И мы собираемся поймать блок, поэтому мы избегаем удаления. Итак, теперь у нас есть утечка памяти." << std::endl;
        }
        std::cout << std::endl << std::endl;

        try 
        {
            std::cout << "В RAII мы используем std::vector вместо массива в стиле C" << std::endl;
            std::vector<int> vec(100);
            std::cout << "И если что-то вызывает исключение." << std::endl;
            throw " exception ";
        }
        catch (const char* error) 
        {
            std::cout << "Ошибка: " << error << std::endl;
            std::cout  << "Мы собираемся поймать остановку, но std::vector обрабатывает память, поэтому утечки нет." << std::endl;
        }
        std::cout << std::endl << std::endl; 

        try 
        {
            std::cout << "В RAII мы используем vector вместо массива в стиле C" << std::endl;
            Vector<int> vec(100);
            std::cout << "И если что-то вызывает исключение" << std::endl;
            throw " exception ";
        }
        catch (const char* error) 
        {
            std::cout << "Ошибка: " << error << std::endl;
            std::cout << "Мы собираемся поймать остановку, но vector обрабатывает память, поэтому утечки нет" << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}
