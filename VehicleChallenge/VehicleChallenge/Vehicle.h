#pragma once

#include <iostream>

class Vehicle
{
public:
	virtual void Drive()
	{
		std::cout << "Default Drive!" << std::endl;
	}
};

