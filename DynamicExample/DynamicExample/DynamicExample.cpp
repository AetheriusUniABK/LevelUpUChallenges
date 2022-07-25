// DynamicExample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int* CreateGrades(int size);
void PopulateGrades(int* pMyGrades, int size);
void DisplayGrades(int* pMyGrades, int size);

int main()
{
    /*
    // good practice of deleting allocated memory
    bool* pBool = new bool{ true };
    delete pBool;
    pBool = nullptr;

    // bad practice since you have to delete at the DELETE comment
    // store address in pointer
    float* pFloat = new float{ 20.5f };
    // DELETE and then assign new value to pFloat
    pFloat = new float{ 30.5f };
    delete pFloat;
    pFloat = nullptr;

    // will only delete one time, but need to delete 5 times to properly clear memory
    int* pInt = nullptr;
    for (int i = 0; i < 5; i++)
    {
        pInt = new int{ rand() };
        std::cout << *pInt << std::endl;
    }

    delete pInt;
    pInt = nullptr;
    */

    int size;
    std::cout << "How many classes do you have: " << std::endl;
    std::cin >> size;
    
    int* pMyGrades = CreateGrades(size);

    PopulateGrades(pMyGrades, size);
    DisplayGrades(pMyGrades, size);

    delete[] pMyGrades;
    pMyGrades = nullptr;
}

int* CreateGrades(int size)
{
    int* point = new int[size];
    return point;
}

void PopulateGrades(int* pMyGrades, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cin >> pMyGrades[i];
    }
}

void DisplayGrades(int* pMyGrades, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << pMyGrades[i] << " ";
    }
}

