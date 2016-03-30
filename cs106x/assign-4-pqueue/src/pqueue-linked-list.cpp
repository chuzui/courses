#include "pqueue-linked-list.h"
using namespace std;

LinkedListPQueue::LinkedListPQueue() { head = nullptr;}
LinkedListPQueue::~LinkedListPQueue() 
{
	Node* node = head;
	while(node)
	{
		Node* temp = node;
		node = node->next;
		delete temp;
	}

}

string LinkedListPQueue::peek() const {
	return head->item;
}

string LinkedListPQueue::extractMin() {
	string item = head->item;
	Node* temp  = head;
	head = head->next;

	delete temp;
	--logSize;

	return item;
}

void LinkedListPQueue::enqueue(const string&  elem ) {
	Node* node = new Node;
	node->item = elem;
	node->prev = nullptr;
	node->next = nullptr;

	insert(node);

	++logSize;
}

LinkedListPQueue *LinkedListPQueue::merge(LinkedListPQueue *  one , LinkedListPQueue *  two ) {
	LinkedListPQueue* lpq = new LinkedListPQueue();
	lpq->logSize = one->logSize + two->logSize;

	if (one->logSize == 0)
	{
		lpq->head = two->head;
		two->head = nullptr;
		return lpq;
	}

	lpq->head = one->head;
	while (two->head)
	{
		Node* curr = two->head;
		two->head = two->head->next;
		lpq->insert(curr);
	}

	return lpq;
}

void LinkedListPQueue::insert(Node* node)
{
	Node* curr;
	Node* prev = nullptr;

	for (curr = head; curr != nullptr; curr = curr->next)
	{
		if (node->item < curr->item) break;
		prev = curr;
	}

	node->next = curr;
	if (prev != nullptr)
	{
		node->prev = prev;
		prev->next = node;
	}
	else
	{
		head = node;
	}

	if (curr != nullptr)
	{
		curr->prev = node;
	}
}

