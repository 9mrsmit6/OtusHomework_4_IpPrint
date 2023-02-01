#ifndef PRINTIP_HPP
#define PRINTIP_HPP

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
void print_ip(const T& value, typename std::enable_if<std::is_integral<T>::value, bool>::type = true)
{
    uint8_t* array=(uint8_t*)(&value);
    for(auto i=0;i!=sizeof(T);i++)
    {
        if(i!=0){std::cout<<'.';}
        std::cout<<(unsigned int)array[sizeof(T)-i-1];
    }
    std::cout<<std::endl;

}

template <typename T>
void print_ip(const T& value, typename std::enable_if<std::is_same<T, std::string>::value, bool>::type = true)
{
    std::cout<<value<<std::endl;
}

template <typename T>
void print_ip(const T& value, typename std::enable_if<isContainer<T>::value, bool>::type = true)
{
    bool isFirst=true;
    for(const auto& v:value)
    {
        if(isFirst) {   isFirst=false;  }
        else        {   std::cout<<'.'; }

        std::cout<<v;
    }
    std::cout<<std::endl;
}


#endif // PRINTIP_HPP
