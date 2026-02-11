#pragma once
#include "Car.h"
class staffManager
{
private:
	Car* head;
	Car* tail;
	double pentalyRate;
	Car* findCar(string carId);
public:
	staffManager(double pentalyRate=20);
	void addCar(string id, string brand, string model, double price);
	void printDailyReservations(int date);
	void convertReservationToRental(string carId, string username, int currentDate);
	void returnCar(string carId, int returnDate,int expectedDate,bool isDsmaged);
	void sendCarForMaintenance(string carId);
	void finishMaintenance(string carId, int currentdate, string description, double cost);
	void displayAllcars();
	void addResevationForTesting(string carId, string username, int startDate, int endDate);
};