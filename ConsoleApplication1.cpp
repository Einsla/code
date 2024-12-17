#include <iostream>
#include <cassert>
#include <string>
using namespace std;

template <typename T>
struct Node {
	T info;
	Node<T>* link;
};

template <typename T>
class list {
	protected:
		Node<T> *first, *last, *current, *previous;
		int count;
	public:
		//constructor & destructor
		list() {
			first = last = current = previous = nullptr;
			count = 0;
		}
		~list() {
			destroy();
		}
		void insert(T &item) {
			Node<T>* newNode;
			newNode = new Node<T>;
			assert(newNode != nullptr);
			newNode->info = item;
			newNode->link = nullptr;
			if (first == nullptr) {
				first = last = newNode;
			}
			else {
				current = first;
				while (current != nullptr) {
					if (current->info >= item) {
						newNode->link = current;
						if (current == first) {
							first = newNode;
							break;
						}
						previous->link = newNode;
						break;
					}
					else {
						if (current != last) {
							previous = current;
							current = current->link;
						}
						else {
							current->link = newNode;
							last = newNode;
							break;
						}
					}
				}
			}
			count++;
			cout << "item appended succeed\n";
		}
		void deleted(T& item) {
			bool found = false;
			if (first == nullptr) {
				cout << "no list detected\n";
			}
			else {
				current = first;
				if (first->info == item) {
					first = current->link;
					delete current;
					count--;
					found = true;
				}
				else {
					while (current != nullptr) {
						if (current->info == item) {
							previous->link = current->link;
							if (current == last) {
								last = previous;
							}
							delete current;
							count--;
							found = true;
							break;
						}
						else {
							previous = current;
							current = current->link;
						}
					}
				}
				if (!found) {
					cout << "item requested is not in list\n";
				}
				else {
					cout << "deletion succeed\n";
				}
			}
		}
		void find(T& item) {
			bool found = false;
			int i = 1;
			if (first == nullptr) {
				cout << "no list detected\n";
			}
			else {
				current = first;
				while (current != nullptr) {
					if (current->info == item) {
						found = true;
						break;
					}
					else {
						previous = current;
						current = current->link;
						i++;
					}
				}
				if (!found) {
					cout << "item requested is not in list\n";
				}
				else {
					cout << "item requested "<<item<<" is in box "<<i<<"\n";
				}
			}
		}
		void print() {
			int i = 1;
			if (first == nullptr) {
				cout << "no list detected\n";
			}
			else {
				current = first;
				while (current != nullptr) {
					cout << "Box " << i << " item is " << current->info << endl;
					i++;
					current = current->link;
				}
			}
			
		}
		void destroy() {
			current = first;
			while (current != nullptr) {
				previous = current;
				current = current->link;
				delete previous;
			}
			count = 0;
			first = last = nullptr;
			cout << "destruction succeed\n";
		}
};

int main() {
	int choice;
	string item;
	list<string> world;
	do {
		system("cls");
		cout << "========================================\n";
		cout << "	Welcome to my item world	\n";
		cout << "========================================\n";
		cout << endl;
		cout << "Available action:\n";
		cout << "1.insert item\n";			//insert item
		cout << "2.used item\n";			//delete item
		cout << "3.destroy the world\n";	//destroy list
		cout << "4.print world listing\n";	//print list
		cout << "5.find 'someone'\n";		//find item
		cout << "\n\n\nSo what will you do?\n";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "enter item to store in this world:\n";
			cin >> item;
			world.insert(item);
			break;
		case 2:
			cout << "enter item to be used:\n";
			cin >> item;
			world.deleted(item);
			break;
		case 3:
			world.destroy();
			break;
		case 4:
			world.print();
			break;
		case 5:
			cout << "enter item to be expected in this world:\n";
			cin >> item;
			world.find(item);
			break;
		default:
			cout << "invalid choice. Please try again:\n";
			break;
		}
		system("pause");
	} while (choice != 0);
}