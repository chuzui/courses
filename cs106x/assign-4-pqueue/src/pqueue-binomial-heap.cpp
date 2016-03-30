#include "pqueue-binomial-heap.h"
#include <iostream>
using namespace std;

BinomialHeapPQueue::BinomialHeapPQueue() {}
BinomialHeapPQueue::~BinomialHeapPQueue() {}

string BinomialHeapPQueue::peek() const {
    // placeholder so method compiles..
	// replace with your own implementation
	string minElem;
	for (auto& node: data)
	{
		if (node)
		{
			if (node->elem < minElem)
				minElem = node->elem;
		}
	}

	return minElem;
}

string BinomialHeapPQueue::extractMin() {
	Node* minNode = nullptr;
	int minIndex;
	for (int i = 0; i < data.size(); ++i)
	{
		Node* node = data[i];
		if (node)
		{
			if (!minNode || node->elem < minNode->elem)
			{
				minNode = node;
				minIndex = i;
			}
		}
	}

	string elem = minNode->elem;
	data[minIndex] = nullptr;

	for (auto n: minNode->children)
	{
		insert(n);
	}

	delete minNode;

	--logSize;
	
	return elem;
}

void BinomialHeapPQueue::enqueue(const string&  elem ) {
    Node* node = creatNode(elem);
    insert(node);
    ++logSize;
}

BinomialHeapPQueue *BinomialHeapPQueue::merge(BinomialHeapPQueue* one, BinomialHeapPQueue* two) {
	BinomialHeapPQueue* bhp = new BinomialHeapPQueue();

	bhp->logSize = one->logSize + two->logSize;

	BinomialHeapPQueue* other;

	if (one->logSize > two->logSize)
	{
		bhp->data = one->data;
		other = two;
	}
	else
	{
		bhp->data = two->data;
		other = one;
	}

	for (auto& n : other->data)
	{
		if (n)
			bhp->insert(n);
	}

	return bhp;

}

void BinomialHeapPQueue::insert(Node* node)
{
	if (!node) return;

	Node* insertNode = node;

	while (insertNode->degree < data.size())
	{
		int degree = insertNode->degree;

		if (!data[degree])
		{
			data[degree] = insertNode;
			return;
		}

		if (insertNode->elem < data[degree]->elem)
		{
			insertNode = addSubHeap(insertNode, data[degree]);
		}
		else
		{
			insertNode = addSubHeap(data[degree], insertNode);
		}
		data[degree] = nullptr;
	}

	data.push_back(insertNode);
}

typename BinomialHeapPQueue::Node* BinomialHeapPQueue::addSubHeap(Node* p, Node* child)
{
	p->children.push_back(child);
	++(p->degree);
	return p;
}

typename BinomialHeapPQueue::Node* BinomialHeapPQueue::creatNode(const std::string& elem)
{
	Node* node = new Node;

	node->elem = elem;
	node->degree = 0;

	return node;
}
