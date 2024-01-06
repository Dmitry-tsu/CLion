#include<iostream>
#include <cassert>
#include "BoolVector.h"
int main()
{
    using std::cout;
    using std::endl;

    BoolVector bvec_1;
    cout << "bvec_1: ";
    bvec_1.print();
    BoolVector bvec_2(10, true);
    cout << "bvec_2: ";
    bvec_2.print();
    cout << endl;

    BoolVector bvec_3 = (const BoolVector &) "10111";
    cout << "bvec_3: ";
    bvec_3.print();
    cout << endl;

    bvec_1.swap(bvec_2);
    cout << "bvec_1: ";
    bvec_1.print();
    cout << "bvec_2: ";
    bvec_2.print();
    cout << endl;

    const BoolVector& bvec_4(bvec_3);
    cout << "bvec_4: ";
    bvec_4.print();
    cout << endl;

}