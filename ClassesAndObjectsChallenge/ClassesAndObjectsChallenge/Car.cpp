#include "Car.h"
#include <iostream>

// Constructors

Car::Car()
{
	m_year = 2019;
	m_miles = 0;
	m_brand = "unspecified";
}

Car::Car(int year, int miles, std::string brand)
{
	m_year = year;
	m_miles = miles;
	m_brand = brand;
}

// Destructor
Car::~Car()
{

}

// Member functions
void Car::Display()
{
	std::cout << "Brand: " << m_brand << std::endl;
	std::cout << "Year: " << m_year << std::endl;
	std::cout << "Miles: " << m_miles << std::endl;
}

void Car::Drive(int miles)
{
	m_miles = m_miles + miles;
}

void Car::SetYear(int newYear)
{
	m_year = newYear;
}

int Car::GetYear()
{
	return m_year;
}