#include "StaffManager.h"
staffManager::staffManager(double pentalyRate): pentalyRate(pentalyRate)
{
	head = nullptr;
	tail = nullptr;
}
Car* staffManager::findCar(string carId)
{
	Car* current = head;
	while (current != nullptr)
	{
		if (current->carId == carId)
			return current;
		current = current->next;
	}
	return nullptr;
}
void staffManager::addCar(string id, string brand, string model, double price)
{
	Car* newCar = new Car(id, brand, model, price);
	if (head == nullptr)
	{
		head = newCar;
		tail = newCar;
	}
	else
	{
		tail->next = newCar;
		newCar->prev = tail;
		tail = newCar;
	}
	cout << "Car "<<brand<<" "<<model<<" added successfully!" << endl;

}
void staffManager::printDailyReservations(int date)
{
	cout << "Reservations for date " << date << ":" << endl;
	Car* current = head;
	bool found = false;
	while (current != nullptr)
	{
		if (!current->resQueue.isEmpty())
		{
			Reservation res = current->resQueue.peek();
			if (res.startDate <= date)
			{
				cout << "Car ID: " << current->carId << " (" << current->brand << "), Reserved by User : " << res.username << ", Start : " << res.startDate << ", End : " << res.endDate << endl;
				cout << "-----------------------------" << endl;
				found = true;
			}
		}
		current = current->next;
	}
	if (!found)
	{
		cout << "No reservations until this date." << endl;
	}
}
void staffManager::convertReservationToRental(string carId, string username, int currentDate)
{
	Car* car = findCar(carId);
	if (car == nullptr)
	{
		cout << "Car not found." << endl;
		return;
	}
	if (car->status != "Available")
	{
		cout << "Car is not available for rental." << endl;
		return;
	}
	if (car->resQueue.isEmpty() || car->resQueue.peek().username != username || car->resQueue.peek().startDate > currentDate)
	{
		cout << "No valid reservation found for this user at the current date." << endl;
		return;
	}
	car->status = "Rented";
	car->resQueue.pop();
	cout << "Reservation converted to rental successfully! car " <<carId<<" is now Rented to "<<username<<"!" << endl;
}
void staffManager::returnCar(string carId, int returnDate, int expectedDate, bool isDamaged)
{
	Car* car = findCar(carId);
	if (car == nullptr)
	{
		cout << "Car not found." << endl;
		return;
	}
	if (car->status != "Rented")
	{
		cout << "Car is not currently rented." << endl;
		return;
	}
	car->status = "Available";
	double penalty = 0;
	if (returnDate > expectedDate)
	{
		penalty = (returnDate - expectedDate) * pentalyRate;
		cout << "Car returned late. Penalty: $" << penalty << endl;

	}
	if (isDamaged)
	{
		car->status = "Maintenance";
		cout << "car reported as damaged and sent to maintenance." << endl;
	}
}
void staffManager::sendCarForMaintenance(string carId)
{
	Car* car = findCar(carId);
	if (car == nullptr)
	{
		cout << "Car not found." << endl;
		return;
	}
	if (car->status == "Rented")
	{
		cout << "Car is currently rented and cannot be sent for maintenance." << endl;
		return;
	}
	car->status = "Maintenance";
	cout << "Car sent for maintenance successfully!" << endl;
}
void staffManager::finishMaintenance(string carId, int currentDate, string description, double cost)
{
	Car* car = findCar(carId);
	if (car == nullptr)
	{
		cout << "Car not found." << endl;
		return;
	}
	if (car->status != "Maintenance")
	{
		cout << "Car is not currently under maintenance." << endl;
		return;
	}
	car->status = "Available";
	car->repairHistory.push_back({ currentDate, description, cost });
	cout << "Maintenance finished and car is now available!" << endl;
}
void staffManager::displayAllcars()
{
	Car* current = head;
	if (current == nullptr)
	{
		cout << "No cars in the system." << endl;
		return;
	}
	while (current != nullptr)
	{
		cout << "Car ID: " << current->carId << ", Brand: " << current->brand << ", Model: " << current->model << ", Price: $" << current->price << ", Status: " << current->status << endl;
		current = current->next;
	}
}
void staffManager::addResevationForTesting(string carId, string username, int startDate, int endDate)
{
	Car* car = findCar(carId);
	if (car == nullptr)
	{
		cout << "Car not found." << endl;
		return;
	}
	if (car->resQueue.hasConflict(startDate, endDate))
	{
		cout << "Cannot add reservation because of a conflict." << endl;
		return;
	}
	else
	{
		car->resQueue.push({ username, startDate, endDate });
		cout << "Test reservation added successfully for car " << carId << " and username:" << username << "!" << endl;
	}
}