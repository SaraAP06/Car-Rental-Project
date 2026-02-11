#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Reservation
{
	string username;
	int startDate;
	int endDate;
	bool operator>(const Reservation& other) const
	{
		return startDate > other.startDate;
	}
};
class ReservationQueue
{
private: 
	vector<Reservation> heapArray;
	void heapifyUp(int index);
	void heapifyDown(int index);

public:
	
	void push(Reservation res);
	Reservation pop();
	Reservation peek();
	bool isEmpty();
	bool hasConflict(int newStart, int newEnd);
	void printQueue();
};