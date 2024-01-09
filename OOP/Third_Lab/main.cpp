#include<iostream>
#include "BoolVector.h"
int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    BoolVector foo(41, true);
    for (int i = 0; i <= foo.returnLength(); ++i)
    {
        cout << (foo << i);
    }
    cout << "______________________________\n";
    for (int i = 0; i <= foo.returnLength(); ++i)
    {
        cout << (foo >> i);
    }
    cout << "______________________________\n";


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

    BoolVector bvec_6 = "1010011";

    cout << bvec_6;
    cout << bvec_6[0]<<endl;
    int n = 32; bvec_6[2] = n; cout << bvec_6;
    bool b = true; bvec_6[1] = b; cout << bvec_6;
    if (bvec_6[2] == bvec_6[1])
        cout << "Completed"<<endl;
    bvec_6[1] = 1;
    if (bvec_6[0] != bvec_6[1])
        cout << "Completed" << endl;
    bvec_6[0]=bvec_6[1]& bvec_6[2];
    cout << bvec_6;
    bvec_6[0] &= 0;
    cout << bvec_6;

    cout << endl;
    bvec_6[0] = 0; bvec_6[1] = 0;
    cout << bvec_6;
    bvec_6[0] = bvec_6[1] | bvec_6[2];
    cout << bvec_6;
    bvec_6[1] |= 1;
    cout << bvec_6;
    cout << ~bvec_6[0];
    cout << endl;
    cout << (bvec_6[0] ^ bvec_1[0])<<endl;
    if (bvec_6[0]>=bvec_6[0])
        cout << "Completed" << endl;

    cout << bvec_6.returnWeight();
    bvec_6.inverse(1);
    cout << bvec_6;
    bvec_6.set1(2, 55);
    cout << bvec_6;
    bvec_6.set0(0, 55);
    cout << bvec_6;

    bvec_6.set1();
    cout << bvec_6;
    bvec_6.set0();
    cout << bvec_6;

    return 0;


}