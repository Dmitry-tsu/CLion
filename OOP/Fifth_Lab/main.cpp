#include "List.h"

int main()
{
    List<int> list_1;
    list_1.Print();
    List<int> list_2(5, 2);
    list_2.Print();
    List<int> list_3(5, 7);
    list_2 = list_3;
    list_2.Print();
    std::cin >> list_2;
    std::cout << list_2;
    list_3 = list_1 + list_2;
    list_3.Print();
    list_3 += list_1;
    list_3.Print();
    list_1.Print();
    list_2.Print();

    std::cout << std::endl;


    return 0;
}

