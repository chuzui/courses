#ifndef _binomial_heap_pqueue_
#define _binomial_heap_pqueue_

#include "pqueue.h"
#include <string>
#include <vector>

class BinomialHeapPQueue : public PQueue {
public:
	BinomialHeapPQueue();
	~BinomialHeapPQueue();
	
	static BinomialHeapPQueue *merge(BinomialHeapPQueue *one, BinomialHeapPQueue *two);
	
	void enqueue(const std::string& elem);
    std::string extractMin();
    std::string peek() const;
	
private:
    struct Node
    {
    	std::string elem;
    	int degree;
    	std::vector<Node*> children;
    };

    std::vector<Node*> data;

    void insert(Node* node);
    Node* addSubHeap(Node* p, Node* child);
    Node* creatNode(const std::string& elem);
};

#endif
