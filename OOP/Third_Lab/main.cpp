#include<iostream>
#include <cassert>
#include "BoolVector.h"
int main()
{
    BoolVector a;
    a.print();
    BoolVector b (9, true);
    b.print();
    return 0;
}