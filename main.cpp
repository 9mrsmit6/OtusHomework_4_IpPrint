#include "printIp.hpp"

#include <tuple>


//template< std::size_t I, class T >
//struct tuple_element;

//// recursive case
//template< std::size_t I, class Head, class... Tail >
//struct tuple_element   <  I, std::tuple<Head, Tail...>   >: std::tuple_element<  I-1, std::tuple<Tail...>> { };

//// base case
//template< class Head, class... Tail >
//struct tuple_element<0, std::tuple<Head, Tail...>> {
//   using type = Head;
//};


//template <class T>
//struct testTuple
//{

//    static bool detector(T tuple){}
//    static constexpr bool value=true;
//};

template <class H, class ...T>
void vax(T... a)
{
    std::cout<<"H"<<std::endl;
    vax(a...);
}

template <class ...T>
void vax(T... a)
{
    std::cout<<"END"<<std::endl;
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

    vax(10,12,12,12,12);

    return 0;
}
