#include<iostream>
#include "List.h"
int main()
{
    List<int> list_1;
    list_1.Print();

    for (int i = 0; i < 5; ++i)
    {
        list_1.PopFront();
        list_1.PopBack();
    }

    for (int i = 0; i < 10; i++)
    {
        list_1.Insert(i,i);
        list_1.Print();
    }

    for (int i = 9; i >=0; i--)
    {
        list_1.Remove(i);
        list_1.Print();
    }

    for (int i = 0; i < 10; i++)
        list_1.Insert(i, i);
    list_1.Print();

    if ( list_1.RemoveKey(5))
        list_1.Print();

    list_1.RemoveRange(list_1.begin(), list_1.end()-1);
    list_1.Print();

    for (int i = 0; i < 10; i++)
        list_1.Insert(i, i);
    list_1.InsertAfter(5, 400);
    list_1.Print();
    std::cout << list_1.Max()<<std::endl<< list_1.Min() << std::endl;

    return 0;
}