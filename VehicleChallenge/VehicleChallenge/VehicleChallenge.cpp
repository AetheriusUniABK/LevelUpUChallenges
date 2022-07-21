// VehicleChallenge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Vehicle.h"
#include "Airplane.h"
#include "Boat.h"
#include "Car.h"

int main()
{
    Vehicle vehicle;
    Airplane plane;
    Boat boat;
    Car car;

    vehicle.Drive();
    plane.Drive();
    boat.Drive();
    car.Drive();
}

