#include "ReservationQueue.h"
#include <algorithm>
using namespace std;
void ReservationQueue::heapifyUp(int index)
{
	if (index == 0)
		return;
	int parentindex = (index - 1) / 2;
	if (heapArray[parentindex].startDate > heapArray[index].startDate)
	{
		swap(heapArray[parentindex], heapArray[index]);
		heapifyUp(parentindex);
	}
}
void ReservationQueue::heapifyDown(int index)
{
	int leftchild = 2 * index + 1;
	int rightchild = 2 * index + 2;
	int smallest = index;
	if (leftchild < heapArray.size() && heapArray[leftchild].startDate < heapArray[smallest].startDate)
	{
		smallest = leftchild;
	}
	if (rightchild < heapArray.size() && heapArray[rightchild].startDate < heapArray[smallest].startDate)
	{
		smallest = rightchild;
	}
	if (smallest != index)
	{
		swap(heapArray[index], heapArray[smallest]);
		heapifyDown(smallest);
	}
}
void ReservationQueue::push(Reservation res)
{
	heapArray.push_back(res);
	heapifyUp(heapArray.size() - 1);
}
Reservation ReservationQueue::pop()
{
	if (isEmpty())
		return { "", 0, 0 };
	Reservation top = heapArray[0];
	heapArray[0] = heapArray.back();
	heapArray.pop_back();
	if (isEmpty())
	{
		heapifyDown(0);
	}
	return top;
}
Reservation ReservationQueue::peek()
{
	if (isEmpty())
		return { "", 0, 0 };
	return heapArray[0];
}
bool ReservationQueue::isEmpty()
{
	return heapArray.empty();
}
bool ReservationQueue::hasConflict(int newStart, int newEnd)
{
	for (const auto& res : heapArray)
	{
		if (newStart<res.endDate&& newEnd>res.startDate)
		{
			return true;
		}
	}
	return false;
}
void ReservationQueue::printQueue()
{
	if (isEmpty())
	{
		cout << "No reservations." << endl;
		return;
	}
	for (const auto& res : heapArray)
	{
		cout << "Username: " << res.username << ", Start: " << res.startDate << ", End: " << res.endDate << endl;
	}
}