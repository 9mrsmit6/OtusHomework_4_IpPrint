#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <string>



template<typename T>
struct isContainer
{
    template<typename U>
    static typename U::value_type detect(const U&, typename std::enable_if<std::is_same<U, std::vector<typename U::value_type>>::value, bool>::type = true);

    template<typename U>
    static typename U::value_type detect(const U&, typename std::enable_if<std::is_same<U, std::list  <typename U::value_type>>::value, bool>::type = true);
    static std::nullptr_t detect(...);

    static constexpr bool value = !std::is_same<std::nullptr_t, decltype(detect(std::declval<T>()))>::value;
};



template <typename T>
void print_ip(T value, typename std::enable_if<std::is_integral<T>::value, bool>::type = true)
{
    uint8_t* array=(uint8_t*)(&value);
    for(auto i=0;i!=sizeof(T);i++)
    {
         std::cout<<(unsigned int)array[sizeof(T)-i-1]<<'.';
    }
    std::cout<<std::endl;

}

template <typename T>
void print_ip(T value, typename std::enable_if<std::is_same<T, std::string>::value, bool>::type = true)
{
    std::cout<<value<<std::endl;
}

template <typename T>
void print_ip(T value, typename std::enable_if<isContainer<T>::value, bool>::type = true)
{
    for(const auto& v:value)
    {
        std::cout<<v<<'.';
    }
    std::cout<<std::endl;
}

int main()
{
    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World"} ); // Hello, World!
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
//    print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0



    return 0;
}
