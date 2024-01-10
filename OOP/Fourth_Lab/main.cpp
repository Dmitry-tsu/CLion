#include<iostream>
#include "BoolMatrix.h"
#include <random>
#include <ctime>

using  std::cout;
using  std::cin;
using  std::endl;

char** CreateCharMatrix(int rows, int cols)
{
    char **charMatrix = new char *[rows];
    for (int i = 0; i < rows; i++)
    {
        charMatrix[i] = new char[cols + 1];
        int j = 0;
        for (j = 0; j < cols; j++) {
            std::cin >> charMatrix[i][j];
        }
        charMatrix[i][j] = '0';
    }
    return charMatrix;
}



char** CreateRandomCharMatrix(int rows,int cols)
{
    std::mt19937 rng(time(nullptr));
    std::uniform_int_distribution<int> dist(0, 1);
    char** charMatrix = new char* [rows];
    for (int i = 0; i < rows; i++) {
        charMatrix[i] = new char[cols+1];
        int j=0;
        for (j = 0; j < cols; j++) {
            charMatrix[i][j]= dist(rng) == 0 ? '0' : '1';
        }
        charMatrix[i][j] = '0';
    }
    return charMatrix;
}


void print(int rows, int cols, char **charMatrix)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << charMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void deleteMatrix(int rows, int cols, char**charMatrix)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] charMatrix[i];
    }
    delete[] charMatrix;
}

int main()
{
    BoolMatrix bm0;
    bm0.print();
    cout << endl;

    BoolMatrix bm1(5,15,true);
    bm1.print();
    cout << endl;

    BoolMatrix bm2(bm1);
    bm2.print();
    cout << endl;

    char** charMatrix = CreateRandomCharMatrix(10, 10);
    print(10, 10, charMatrix);
    cout << endl;
    BoolMatrix bm3(charMatrix, 10, 10);
    bm3.print();
    deleteMatrix(10, 10, charMatrix);
    cout << endl;

    cout << bm1.returnWeight() << endl;
    cout << bm1[0].returnWeight() << endl;
    cout << bm1.returnWeight(0) << endl;

    bm3.print();
    cout << endl;
    cout << bm3.logicalAnd() << endl;
    cout << bm3.logicalOr() << endl;

    charMatrix = CreateRandomCharMatrix(5, 5);
    print(5, 5, charMatrix);
    cout << endl;
    BoolMatrix bm4(charMatrix, 5, 5);
    delete(5, 5, charMatrix);

    bm3.print();
    cout << endl;
    bm4.print();
    cout << endl;
    cout << endl << (bm3 & bm4);
    cout << endl << (bm3 | bm4);
    cout << endl << (bm3 ^ bm4);
    cout << endl<< ~bm4;
    cout << endl;

    cout << bm4;
    bm4.inverse(0, 0);
    cout<< endl << bm4;
    bm4.inverse(2, 0);
    cout<<endl << bm4;
    bm4.inverse(0,0,8);
    cout << endl << bm4;
    bm4.set1(0, 0);
    cout << endl << bm4;
    bm4.set0(0, 0,8);
    cout << endl << bm4;

    return 0;
}

