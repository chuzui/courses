#include "pqueue-vector.h"
using namespace std;

VectorPQueue::VectorPQueue() {}
VectorPQueue::~VectorPQueue() {}

string VectorPQueue::peek() const {
    // placeholder so method compiles..
	// replace with your own implementation
	int pos = findMin();
	return data[pos];
}

string VectorPQueue::extractMin() {
	// placeholder so method compiles..
	// replace with your own implementation
	int pos = findMin();
	string minStr = data[pos];
	
	data.erase(data.begin() + pos);
	--logSize;

	return minStr;
}

void VectorPQueue::enqueue(const string& elem) {
	++logSize;
	data.push_back(elem);
}
	

VectorPQueue *VectorPQueue::merge(VectorPQueue * one, VectorPQueue * two) {
	VectorPQueue* newPq = new VectorPQueue();

	for (auto it = one->data.begin(); it != one->data.end(); ++it)
	{
		newPq->enqueue(*it);
	}

	for (auto it = two->data.begin(); it != two->data.end(); ++it)
	{
		newPq->enqueue(*it);
	}

	return newPq;
}

int VectorPQueue::findMin () const
{
	string minStr;
	int minIndex = 0;

	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i] < minStr || minStr.size() == 0)
		{
			minStr = data[i];
			minIndex = i;
		}
	}

	return minIndex;
}
