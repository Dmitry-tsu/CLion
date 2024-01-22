#include<iostream>
#include "List.h"
int main()
{
    List<int> list_1;
    list_1.Print();
    List<int> list_2(2, 10);
    list_2.Print();
    List<int> list_3(5,10);
    list_2 = list_3;
    list_2.Print();
    std::cout << std::endl;

    List<char> list_4;
    list_4.PushBack('a');
    list_4.PushBack('b');
    list_4.PushBack('c');
    list_4.PushBack('A');
    list_4.PushBack('z');
    std::cout << std::endl << list_4.Max() << std::endl;

    list_3 = list_1 + list_2;
    list_3.Print();
    list_3 += list_1;
    list_3.Print();
    list_1.Print();
    list_2.Print();

    return 0;
}