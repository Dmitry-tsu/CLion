#include "List.h"

int main()
{
    // Создание пустого списка и печать его содержимого
    List<int> list_1;
    list_1.Print();

    // Создание списка из 5 элементов со значением 10 и печать его содержимого
    List<int> list_2(5, 10);
    list_2.Print();

    // Создание копии списка list_2 и печать ее содержимого
    List<int> list_3(list_2);
    list_3.Print();

    return 0;
}

