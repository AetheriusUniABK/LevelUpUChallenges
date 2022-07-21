#pragma once

#include <iostream>
#include "Vehicle.h"

class Car : public Vehicle
{
public:
	void Drive() override
	{
		std::cout << "Zoom zoom" << std::endl;
	}
};

