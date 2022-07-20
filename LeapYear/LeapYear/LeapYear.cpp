// LeapYear.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <ctime>

int main()
{
    std::string rString = "That year is ";
    int year = 0;
    bool isLeap = false;

    std::cout << "Enter year to confirm leap year status: ";
    std::cin >> year;

    // Leap years must be divisible by 4
    if (year % 4 == 0)
    {
        // Years divisible by 100 aren't leap years
        if (year % 100 == 0)
        {
            // unless it's divisible by 400 then it's still a leap year
            if (year % 400 == 0)
            {
                isLeap = true;
            }
            else
            {
                isLeap = false;
            }
        }
        else
        {
            isLeap = true;
        }
    }
    else
    {
        isLeap = false;
    }

    // append appropriate ending to rString based on if we're dealing with a leap year or not
    if (isLeap)
    {
        // That year is a leap year!
        rString += "a leap year!";
    }
    else
    {
        // That year is not a leap year!
        rString += "not a leap year!";
    }

    // output the rString
    std::cout << rString << std::endl;
}
