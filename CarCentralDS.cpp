#include "StaffManager.h"
void printMenu()
{
	cout << "1. Add Car" << endl;
	cout << "2. Print Daily Reservations" << endl;
	cout << "3. Convert Reservation to Rental" << endl;
	cout << "4. Return Car" << endl;
	cout << "5. Send Car for Maintenance" << endl;
	cout << "6. Finish Maintenance" << endl;
	cout << "7. Display All Cars" << endl;
	cout << "8. Exit" << endl;
}

int main()
{
	staffManager manager(10);
	cout << "add cars" << endl << endl;
	manager.addCar("C001", "Toyota", "Camry", 50);
	manager.addCar("C002", "Honda", "Civic", 45);
	manager.addCar("C003", "Ford", "Mustang", 80);
	cout << endl << "add reservations" << endl << endl;
	manager.addResevationForTesting("C001", "user1", 1, 5);
	manager.addResevationForTesting("C001", "user2", 6, 10);
	cout << "test reservation conflict" << endl;
	manager.addResevationForTesting("C001", "user3", 2, 7);
	/*cout << endl << "print daily reservations for date 3" << endl << endl;
	manager.printDailyReservations(3);
	cout << endl << "convert reservation to rental and return car" << endl << endl;
	manager.convertReservationToRental("C001", "user1", 3);
	manager.returnCar("C001", 8, 5, false);
	cout << endl << "send car for maintenance and finish maintenance" << endl << endl;
	manager.sendCarForMaintenance("C002");
	manager.finishMaintenance("C002", 10, "Engine repair", 200);
	cout << endl << "display all cars" << endl << endl;
	manager.displayAllcars();*/
	int choice;
	do
	{
		printMenu();
		cout << "Enter your choice: ";
		cin >> choice;
		string id, brand, model;
		double price;
		int date;
		string carId, username;
		int currentDate;
		string returnCarId;
		int returnDate, expectedDate;
		bool isDamaged;
		string maintenanceCarId;
		string finishMaintenanceCarId, description;
		int maintenanceDate;
		double cost;
		switch (choice)
		{
		case 1:
			
			cout << "Enter Car ID: ";
			cin >> id;
			cout << "Enter Brand: ";
			cin >> brand;
			cout << "Enter Model: ";
			cin >> model;
			cout << "Enter Price: ";
			cin >> price;
			manager.addCar(id, brand, model, price);
			break;
		case 2:
			cout << "Enter date to view reservations: ";
			cin >> date;
			manager.printDailyReservations(date);
			break;
		case 3:
			cout << "Enter Car ID: ";
			cin >> carId;
			cout << "Enter Username: ";
			cin >> username;
			cout << "Enter Current Date: ";
			cin >> currentDate;
			manager.convertReservationToRental(carId, username, currentDate);
			break;
		case 4:
			
			cout << "Enter Car ID: ";
			cin >> returnCarId;
			cout << "Enter Return Date: ";
			cin >> returnDate;
			cout << "Enter Expected Date: ";
			cin >> expectedDate;
			cout << "Is the car damaged? (1 for Yes, 0 for No): ";
			cin >> isDamaged;
			manager.returnCar(returnCarId, returnDate, expectedDate, isDamaged);
			break;
		case 5:
			
			cout << "Enter Car ID to send for maintenance: ";
			cin >> maintenanceCarId;
			manager.sendCarForMaintenance(maintenanceCarId);
			break;
		case 6:
			
			cout << "Enter Car ID to finish maintenance: ";
			cin >> finishMaintenanceCarId;
			cout << "Enter Current Date: ";
			cin >> maintenanceDate;
			cout << "Enter Description of Maintenance: ";
			cin.ignore();
			getline(cin, description);
			cout << "Enter Cost of Maintenance: ";
			cin >> cost;
			manager.finishMaintenance(finishMaintenanceCarId, maintenanceDate, description, cost);
			break;
		case 7:
			manager.displayAllcars();
			break;
		case 8:
			cout << "Exiting..." << endl;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 8);

	return 0;
}