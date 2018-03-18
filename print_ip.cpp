#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<tuple>
#include<type_traits>

template<typename Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const Tuple& t)
    {
        TuplePrinter<Tuple, N-1>::print(t);
        std::cout << "." << std::get<N-1>(t);
    }
};

template<typename Tuple>
struct TuplePrinter<Tuple, 1> {
    static void print(const Tuple& t)
    {
        std::cout << std::get<0>(t);
    }
};

//! Функция печати адреса для контейнеров
template <
        typename T,
        typename std::enable_if<
                !(std::is_integral<T>::value
                || std::is_same<T, std::string>::value),
                T*
        >::type = nullptr
>
void print(const T& val)
{
    for(auto i=val.begin();i!=val.end();++i)std::cout<<*i<<(i==--val.end()  ?'\n':'.');
}

//! Функция печати адреса для строки
template <
        typename T,
        typename std::enable_if<
                std::is_same<T,std::string>::value,
                T*
        >::type = nullptr
>
void print(const T& val)
{
    std::cout<<val<<std::endl;
}

//! Функция печати адреса для целочисленных типов
template <
        typename T,
        typename std::enable_if<
                std::is_integral<T>::value,
                T*
        >::type = nullptr
>
void print(T val)
{
    size_t bytes = sizeof(val);
	for (size_t i = 1; i <= bytes; i++)
	{
		std::cout << ((i > 1) ? "." : "") << (unsigned int)(reinterpret_cast<unsigned char*>(&val))[bytes - i];
	}

	std::cout << std::endl;
}

//! Функция печати адреса для кортежей
template<class... Args>
void print(std::tuple<Args...> t)
{
	TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
    std::cout<<std::endl;
};

int main()
{
	print( char(-1));
	print( short(0));
	print( int(2130706433));
	print( long(8875824491850138409));
	print( std::string("255.255.255.255"));
	print( std::vector<int>{1,2,3,4});
	print( std::list<short>{12,34,56,78});
	print( std::make_tuple(100,200,300,400));

	return 0;
}