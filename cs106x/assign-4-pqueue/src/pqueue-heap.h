#ifndef _binary_heap_pqueue_
#define _binary_heap_pqueue_

#include "pqueue.h"
#include <string>
#include <vector>

class HeapPQueue : public PQueue {
public:
	HeapPQueue();
	~HeapPQueue();
	
	static HeapPQueue *merge(HeapPQueue *one, HeapPQueue *two);
	
	void enqueue(const std::string& elem);
    std::string extractMin();
    std::string peek() const;
    
private:
    std::vector<std::string> data;

    void heapUp(int index);
    void heapDown(int index);
};

#endif