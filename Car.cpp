#include "Car.h"
Car::Car(string id, string b, string m, double p)
{
	carId = id;
	brand = b;
	model = m;
	price = p;
	status = "Available";
	prev = nullptr;
	next = nullptr;
}