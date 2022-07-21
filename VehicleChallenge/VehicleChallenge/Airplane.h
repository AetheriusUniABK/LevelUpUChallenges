#pragma once

#include <iostream>
#include "Vehicle.h"

class Airplane : public Vehicle
{
public:
	void Drive() override
	{
		std::cout << "Wheeeee" << std::endl;
	}
};

