#include "pqueue-heap.h"
#include <algorithm>
#include <iterator>
#include <iostream>
using namespace std;

HeapPQueue::HeapPQueue() {}
HeapPQueue::~HeapPQueue() {}

string HeapPQueue::peek() const {
    // placeholder so method compiles..
	// replace with your own implementation
	return data[0];
}

string HeapPQueue::extractMin() {
	string minStr = data[0];

	swap(data[0], data.back());
	data.pop_back();
	--logSize;

	heapDown(0);

	return minStr;
}

void HeapPQueue::enqueue(const string&  elem ) {
	data.push_back(elem);
	++logSize;

	// if (logSize <= 4)
	// {
	// 	copy(data.begin(), data.end(), ostream_iterator<string>(cout, " "));
	// 	cout << endl;
	// }
	heapUp(logSize - 1);    
}

HeapPQueue *HeapPQueue::merge(HeapPQueue *  one , HeapPQueue *  two ) {
	HeapPQueue *hpg = new HeapPQueue();

	hpg->logSize = one->logSize + two->logSize;

	hpg->data = one->data;

	hpg->data.insert(hpg->data.end(), two->data.begin(), two->data.end());

	for (int i = hpg->logSize - 1; i >=0; --i)
	{
		hpg->heapUp(i);
	}

	return hpg;
}

void HeapPQueue::heapUp(int index)
{
	int currIndex = index;
	while(currIndex != 0)
	{
		int pIndex = (currIndex - 1) / 2;

		if (data[pIndex] > data[currIndex])
			swap(data[pIndex], data[currIndex]);

		currIndex = pIndex;
	}
}

void HeapPQueue::heapDown(int index)
{
	int currIndex = index;
	while(true)
	{
		int leftChildIndex = 2 * currIndex + 1;
    	int rightChildIndex = 2 * currIndex + 2;

	    if(leftChildIndex >= logSize)
	        break; 

    	int minIndex = currIndex;

	    if(data[minIndex] > data[leftChildIndex])
	    {
	        minIndex = leftChildIndex;
	    }
    
	    if((rightChildIndex < logSize) && (data[minIndex] > data[rightChildIndex]))
	    {
	        minIndex = rightChildIndex;
	    }

	    if(minIndex != currIndex)
	    {
	        swap(data[currIndex], data[minIndex]);
	        currIndex = minIndex;
	    }
	    else
	    {
	    	break;
	    }
	}
}

