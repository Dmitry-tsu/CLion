#include<iostream>
#include "BoolMatrix.h"
#include <random>
#include <ctime>

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
    std::mt19937 rng(std::time(nullptr));
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
            std::cout << charMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void DeleteMatrix(int rows, int cols, char**charMatrix)
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
    std::cout << std::endl;

    BoolMatrix bm1(5,15,true);
    bm1.print();
    std::cout << std::endl;

    BoolMatrix bm2(bm1);
    bm2.print();
    std::cout << std::endl;

    char** charMatrix = CreateRandomCharMatrix(10, 10);
    print(10, 10, charMatrix);
    std::cout << std::endl;
    BoolMatrix bm3(charMatrix, 10, 10);
    bm3.print();
    DeleteMatrix(10, 10, charMatrix);
    std::cout << std::endl;

    std::cin >> bm1[1];
    bm1.print();

    return 0;
}

