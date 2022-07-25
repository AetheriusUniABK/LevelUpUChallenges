// PointersChallenge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

/*
void Swap(int* pNumber1, int* pNumber2);
void Swap(int* number1, int* number2);
*/

int main()
{
    /*
    // HOW POINTERS WORK
    int var = 10;
    // store address of var
    int* ptr = &var;
    // dereference ptr AKA get the value the a pointer is pointing to
    int newVar = *ptr;
    // change value of what ptr is pointing to by pointing to it
    *ptr = 20;                                          // var = 20

    std::cout << "variable: " << var << std::endl;      // 20
    std::cout << "&variable: " << &var << std::endl;    // 004FFDD0
    std::cout << "pointer: " << ptr << std::endl;       // 004FFDD0
    std::cout << "&pointer: " << &ptr << std::endl;     // 004FFDC4

    std::cout << "*pointer: " << *ptr << std::endl;     // 20
    */

    /*

    // SWAPPING EXAMPLE WITH POINTERS
    int a = 10;
    int b = 20;

    // function 1 - pointer function
    // input argument is the address of a and b
    // since when a pointer is used on an address, you get the value at the address
    Swap(&a, &b);
    std::cout << a << std::endl;
    std::cout << b << std::endl;

    // function 2 - reference function
    Swap(a, b);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    */

    // Write a program that asks the user to enter integers to be stored in variables 'a' and 'b'
    int a, b;
    std::cout << "Enter value a: ";
    std::cin >> a;
    std::cout << "Enter value b: ";
    std::cin >> b;

    // Then create two integer pointers named ptrA and ptrB
    // Assign the values of 'a' and 'b' to ptrA and ptrB
    int* ptrA = &a;
    int* ptrB = &b;

    // Display them
    std::cout << *ptrA << std::endl;
    std::cout << *ptrB << std::endl;
}

/*
// function 1
void Swap(int* pNumber1, int* pNumber2)
{
    int temp = *pNumber1;
    *pNumber1 = *pNumber2;
    *pNumber2 = temp;
}

// function 2
void Swap(int& number1, int& number2)
{
    int temp = number1;
    number1 = number2;
    number2 = temp;
}
*/