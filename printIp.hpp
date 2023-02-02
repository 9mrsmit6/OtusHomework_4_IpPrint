#ifndef PRINTIP_HPP
#define PRINTIP_HPP

#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <string>

//!Проверка кортеж ли это
template<typename T>
struct isTuple
{
    template<typename ...U>
    static bool detect(const std::tuple<U...>&);
    static std::nullptr_t detect(...);

    static constexpr bool value = !std::is_same_v<    std::nullptr_t, decltype(detect(  std::declval<T>() )) > ;
};


template <class T>
inline constexpr bool isTuple_v = isTuple<T>::value;

//!Проверка кортежа на однородность вторая версия
template <class T>
struct testTuple2
{

    template<class F, class S, class ...Tail>
    static constexpr bool test(const std::tuple<F,S,Tail...>&)
    {
        return std::is_same_v<F, S>&&  test<S,Tail...>  ( std::tuple<S,Tail...>() );
    }

    template<class F>
    static constexpr bool test(const std::tuple<F>&)
    {
        return true;
    }

    static constexpr bool isOk=test (  T()  );
};


//!Проверка кортежа на однородность первая версия
template <class T>
struct testTuple
{

    template<class U, std::size_t i>
    static constexpr bool test(typename std::enable_if_t< (std::tuple_size_v<U> >=2)&&(i>=(std::tuple_size_v<U>-2)), bool> = true)
    {
        using Type=std::tuple_element_t<i, U>;
        using Type2=std::tuple_element_t<i+1, U>;
        return std::is_same_v<Type, Type2>;

    }

    template<class U, std::size_t i>
    static constexpr bool test(typename std::enable_if_t< (std::tuple_size_v<U> >=2)&&(i<(std::tuple_size_v<U>-2)), bool> = true)
    {
        using Type=std::tuple_element_t<i, U>;
        using Type2=std::tuple_element_t<i+1, U>;
        return std::is_same_v<Type, Type2>&&test<U,i+1>();
    }

    template<class U, std::size_t i>
    static constexpr bool test(typename std::enable_if_t< (std::tuple_size_v<U> < 2)&&(std::tuple_size_v<U> != 0), bool> = true)
    {
        return true;
    }

    static constexpr bool isOk=test<T,0>();
};

template <class T>
inline constexpr bool testTuple_v = testTuple<T>::isOk;


//!Проверка кортежа на однородность вторая версия
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


//!Печать целочисленного аргументв
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

//!Печать строкиы
template <typename T>
void print_ip(const T& value, typename std::enable_if<std::is_same<T, std::string>::value, bool>::type = true)
{
    std::cout<<value<<std::endl;
}

//!Печать контейнера
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

//!вспомогательяная функция печать кортежа
template< typename T,  std::size_t n=0>
void printTuple(const T& tuple)
{
    if constexpr (n!=0) {   std::cout << '.';   }
    std::cout<< std::get<n>(tuple);

    if constexpr (n != std::tuple_size_v<T>- 1)
    {
        printTuple<T, n + 1>(tuple);
    }
}


//!Печать кортежа
template <typename T>
void print_ip(const T& value, typename std::enable_if<isTuple_v<T>, bool>::type = true)
{
    static_assert(testTuple_v<T>);
    printTuple(value);
    std::cout<<std::endl;
}


#endif // PRINTIP_HPP
