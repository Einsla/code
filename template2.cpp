#include <iostream>
#include <cassert>
using namespace std;

template<typename Type>
struct node {
	Type data;
	node<Type>* link;
};

template<typename Type>
class queue {
private:
	node<Type>* first, * last, * current;
	int max, count;

public:
	queue() {
		first = last = current = nullptr;
		max = 50;
		count = 0;
	}
	~queue() {
		destroy();
	}

	Type front() {
		assert(first != nullptr);
		return first->data;
	}
	Type rear() {
		assert(last != nullptr);
		return last->data;
	}
	void addqueue(Type item) {
		node<Type>* newNode;
		newNode = new node<Type>;
		assert(newNode != nullptr);
		newNode->data = item;
		newNode->link = nullptr;

		if (last == nullptr) {
			first = last = newNode;
		}
		else {
			last->link = newNode;
			last=newNode;
		}
		count++;
	}
	void deletequeue() {
		current = first;
		if (current != nullptr) {
			first = current->link;
			delete current;
			count--;
		}
	}
	bool Full() {
		return (count == max);
	}
	void destroy() {
		current = first;
		while (current != nullptr) {
			first = current->link;
			delete current;
			current = first;
		}
		count = 0;
	}
};