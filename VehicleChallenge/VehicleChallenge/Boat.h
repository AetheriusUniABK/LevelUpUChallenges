#pragma once

#include <iostream>
#include "Vehicle.h"

class Boat : public Vehicle
{
public:
	void Drive() override
	{
		std::cout << "Woosh woosh" << std::endl;
	}
};

