#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "ReservationQueue.h"
using namespace std;
struct maintenanceStatus
{
	int date;
	string description;
	double cost;
};

class Car {
public:
	string carId;
	string brand;
	string model;
	double price;
	string status;
	ReservationQueue resQueue;
	vector<maintenanceStatus> repairHistory;
	Car* prev;
	Car* next;
	Car(string id, string b, string m, double p);
};