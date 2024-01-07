#include<iostream>
#include "BoolVector.h"
int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    BoolVector bvec_1;
    cout << "bvec_1: ";
    bvec_1.print();
    BoolVector bvec_2(24, true);
    cout << "bvec_2: ";
    bvec_2.print();
    cout << endl;

    BoolVector bvec_3 = "10101";
    cout << "bvec_3: ";
    bvec_3.print();
    cout << endl;

    bvec_1.swap(bvec_2);
    cout << "bvec_1: ";
    bvec_1.print();
    cout << "bvec_2: ";
    bvec_2.print();
    cout << endl;

    BoolVector bvec_4(bvec_3);
    cout << "bvec_4: ";
    bvec_4.print();
    bvec_4.inverse();
    cout << "bvec_4: "<<bvec_4;
    cout << endl;

    cout << "bvec_1: ";
    for(int i=0;i<24;i++)
        cout << bvec_1[i];
    cout <<endl<< bvec_1;
    bvec_1.inverse();
    cout << bvec_1;
    cout << endl;

    bvec_1 = "100111010101000101";
    cout << bvec_1 << "^\n";
    cout << bvec_2 << "=\n";
    bvec_3 = bvec_1 ^ bvec_2;
    cout << bvec_3 << endl;
    bvec_1 ^= bvec_2;
    cout << bvec_1;
    cout << endl;

    cout << ~bvec_1;

    bvec_1 = "100111010101000101";
    cout << bvec_1<<"&\n";
    bvec_2 = "1100101001";
    cout << bvec_2<<"=\n";
    bvec_3 = bvec_1 & bvec_2;
    cout << bvec_3<<endl;
    bvec_1 &= bvec_2;
    cout << bvec_1;
    cout << endl;

    bvec_1 = "100111010101000101";
    cout << bvec_1 << "|\n";
    cout << bvec_2 << "=\n";
    bvec_3 = bvec_1 | bvec_2;
    cout << bvec_3 << endl;
    bvec_1 |= bvec_2;
    cout << bvec_1;
    cout << endl;

    cout << endl;

    BoolVector bvec_5 = "010111100011010111001100101000100101010010101110011110000101";
    cout << bvec_5;
    cout << (bvec_5<<35);
    bvec_5 <<= 35;
    cout << bvec_5;
    cout << endl;

    bvec_5 = "010111100011010111001100101000100101010010101110011110000101";
    cout << bvec_5;
    cout << (bvec_5 >> 35);
    bvec_5 >>= 35;
    cout << bvec_5;
    cout << endl;

    bvec_5 = "1011101";
    cout << bvec_5;
    cout << (bvec_5 << 35);
    cout << (bvec_5 << 5);
    cout << (bvec_5 >> 5);
    cout << endl;

    return 0;
}