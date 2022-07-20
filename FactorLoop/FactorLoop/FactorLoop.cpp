// FactorLoop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    int inputNum = 0;

    std::cout << "Enter the number you want to get the factors for: ";
    std::cin >> inputNum;

    std::cout << "The factors are: ";

    for (int i = 1; i <= inputNum; i++)
    {
        if (inputNum % i == 0)
        {
            std::cout << i << " ";
        }
    }
}

