// TemplateChallenge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>]
#include "Point.h"
#include "Stack.h"

int main()
{
    Point<int> p1(10, 5);
    Point<float> p2(5.3f, 1.5f);
    Point<double> p3(15.2, 41.5);

    int largestP1 = p1.GetLargerCoordinate();
    float largestP2 = p2.GetLargerCoordinate();
    double largestP3 = p3.GetLargerCoordinate();

    std::cout << "Larger coordinate for p1 is " << largestP1 << std::endl;
    std::cout << "Larger coordinate for p2 is " << largestP2 << std::endl;
    std::cout << "Larger coordinate for p3 is " << largestP3 << std::endl;

    Stack<int> intStack;
    intStack.Push(10);
    intStack.Push(20);

    Stack<Point<int>*> pointStack;
    pointStack.Push(new Point<int>(10, 20));
    pointStack.Push(new Point<int>(30, 10));
}


