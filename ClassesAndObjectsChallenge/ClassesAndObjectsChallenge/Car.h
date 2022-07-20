#pragma once

#include <iostream>

class Car
{
private:
	int m_year;

public:
	// Member variables
	//int m_year;
	int m_miles;
	std::string m_brand;

	// Default constructor
	Car();
	Car(int year, int miles, std::string brand);

	// Destructor
	~Car();

	// Member functions
	void Display();
	void Drive(int miles);
	void SetYear(int newYear);
	int GetYear();
};

