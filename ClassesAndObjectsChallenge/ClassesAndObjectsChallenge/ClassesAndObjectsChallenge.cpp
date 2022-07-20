// ClassesAndObjectsChallenge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Car.h"

int main()
{
    Car myCar;
    myCar.m_brand = "BMW";
    //myCar.m_year = 2019; removed at 5 out of 11
    myCar.SetYear(2019);
    myCar.m_miles = 20;
    myCar.Drive(10);
    myCar.Display();

    Car defaultCar;
    defaultCar.Display();
}

