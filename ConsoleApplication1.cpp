#include <iostream>
#include <cassert>
using namespace std;

struct Node {
	int data;
	Node* link;
};

class list {
	Node* first, * last, * current, * previous;	//pointer to access list with *first point to first Node and *last point to last Node, *current is Node access at the moment
	int count;									//list length

public:
	list() {
		first = last = current = previous = nullptr;
		count = 0;
	}
	~list() {
		destroy();
	}
	void insert(int item) {
		Node* add;
		add = new Node;
		assert(add != nullptr);					//to ensure 'add' is successfully created(memory sufficient)
		add->data = item;						//to initialized the 'add' node
		add->link = nullptr;

		if (first == nullptr) {
			first = last = add;
			count++;
		}
		else {
			current = first;
			while (current != nullptr) {		//to prevent segmentation error during access
				if (first->data >= item) {
					add->link = first;
					first = add;
					count++;
					break;
				}
				else if(current->data >= item){
					previous->link = add;
					add->link = current;
					count++; 
					break;
				}
				else{
					if (current != last) {
						current = current->link;
						previous = previous->link;
					}
					else {
						current->link = add;
						last = add;
					}
					count++;
					break;
				}

			}
		}
	}
	void deleted(int item) {
		bool found = false;
		if (first == nullptr) {
			cout << "no list detected\n";
		}
		else {
			current = first;
			while (current != nullptr) {
				if (first->data == item) {
					first = current->link;
					delete current;
					found = true;
					count--;
					break;
				}
				else if (current->data == item) {
					previous->link = current->link;
					delete current;
					found = true;
					count--;
					break;
				}
				else {
					previous = current;
					current = current->link;
				}
			}
			if (found) {
				cout << "item deletion succeed...\n";
			}
			else {
				cout << "item mention is not in list\n";
			}
		}
	}
	void destroy() {
		current = first;
		if (first == nullptr) {
			cout << "no list to be destroyed!!!\n";
		}
		else {
			while (current != nullptr) {
				previous = current;
				current = current->link;
				delete previous;
				count--;
			}
			cout << "list destruction succeed\n";
		}
	}
	void print() {
		int i = 1;
		if (first == nullptr) {
			cout << "no list to be printed\n";
		}
		else {
			current = first;
			while (current != nullptr) {
				cout << "item in box " << i << " is " << current->data<<endl;
				i++;
				current = current->link;
			}
		}
	}
	void find(int item) {
		bool found = false;
		int i = 1;
		if (first == nullptr) {
			cout << "no list detected\n";
		}
		else {
			current = first;
			while (current != nullptr) {
				if (current->data==item) {
					found = true;
					cout << "expected item " << current->data << " is located at box " << i << endl;
					break;
				}
				else {
					current = current->link;
					i++;
				}
			}
			if (!found) {
				cout << "item expected is not in list\n";
			}
		}
	}
	int length() {
		return count;
	}
};

int main() {
	int choice,item;
	list world;
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
		defalut:
			cout << "invalid choice. Please try again:\n";
			break;
		}
		system("pause");
	} while (choice != 0);
}