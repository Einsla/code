#include <iostream>
#include <cassert>
using namespace std;

template<typename Type>
struct node {
	Type data;
	node<Type>* link;
};

template<typename Type>
class stack {
	private:
		node<Type>* top, * current;
		int max, count;

	public:
		stack() {
			top = current = nullptr;
			max = 50;
			count = 0;
		}
		~stack() {
			destroy();
		}

		Type Top() {
			assert(top != nullptr);
			return top->data;
		}
		void Push(Type item) {
			node<Type>* newNode;
			newNode = new node<Type>;
			assert(newNode != nullptr);
			newNode->data = item;
			newNode->link = nullptr;

			if (top == nullptr) {
				top = newNode;
			}
			else {
				newNode->link = top;
				top = newNode;
			}
			count++;
		}
		void Pop() {
			current = top;
			if (current != nullptr) {
				top = current->link;
				delete current;
				count--;
			}
		}
		bool Full() {
			return (count == max);
		}
		void destroy() {
			current = top;
			while (current != nullptr) {
				top = current->link;
				delete current;
				current = top;
			}
			count = 0;
		}
};
