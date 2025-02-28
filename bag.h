//this is a note: rmb to comment out the main function in order to use this header


#pragma once
#include <iostream>
#include "item.h"
using namespace std;

struct space {
	item key;
	space* next;
	space* previous;
};

class bag {
private:
	space* first, * last;
	int count, max = 500;

public:
	bag() {
		first = last = nullptr;
		count = 0;
	}
	~bag() {
		destroy();
	}

	int getcount() const {
		return count;
	}
	void click(int n) {
		if (n > count) {
			return;
		}
		else if (n > 0) {
			space* temp;
			temp = first;
			n--;
			while (n > 0) {
				temp = temp->next;
				n--;
			}
			temp->key.display();
			if (temp->key.getquantity() == 0) {
				if (temp == first) {
					first = temp->next;
				}
				else {
					temp->previous->next = temp->next;
				}
				if (temp == last) {
					last = temp->previous;
				}
				else {
					temp->next->previous = temp->previous;
				}
				count--;
			}
		}
	}
	void destroy() {
		space* temp;
		while (first != nullptr) {
			temp = first;
			first = temp->next;
			delete temp;
			first->previous = nullptr;
			count--;
		}
	}
	void insert(item& Item) {
		space* temp, * add;
		add = new space;
		add->key = Item;
		add->next = add->previous = nullptr;

		if (count == max) {
			cout << "bag is full. Please clear up some space\n";
			delete add;
			return;
		}
		if (first == nullptr) {
			first = last = add;
		}
		else {
			temp = first;
			while (temp != nullptr) {
				if (Item < temp->key) {
					add->previous = temp->previous;
					add->next = temp;
					temp->previous = add;
					if (temp == first) {
						first = add;
					}
					else {
						add->previous->next = add;
					}
					break;
				}
				else if (Item == temp->key) {
					temp->key.add(Item);
					delete add;
					return;
				}
				else {
					if (temp->next != nullptr) {
						temp = temp->next;
					}
					else {
						temp->next = add;
						add->previous = temp;
						last = add;
						break;
					}
				}
			}
		}
		count++;
	}
	void display() {
		space* temp;
		int n = 0;
		temp = first;
		while (temp != nullptr) {
			n++;
			cout << n << ". " << temp->key.getname() << endl;
			temp = temp->next;
		}
		cout << endl << endl << endl;
		cout << n + 1 << ". back to main." << endl;

	}
};

int main() {
	char choice;
	int n;
	bag world;
	item ref;
	do {
		system("cls");
		cout << "========================================\n";
		cout << "	Welcome to my item world	\n";
		cout << "========================================\n";
		cout << endl;
		cout << "Available action:\n";
		cout << "1.pick up item\n";			//insert item
		cout << "2.open bag\n";				//print item list
		cout << "3.exit game\n";
		cout << "\n\n\nSo what will you do?\n";
		cin >> choice;
		switch (choice) {
		case'1':
			system("cls");
			create(ref);
			world.insert(ref);
			system("pause");
			break;
		case'2':
			while (true) {
				system("cls");
				world.display();
				cout << endl << endl;
				cin >> n;
				if (n == (world.getcount() + 1)) {
					cout << "Returning to menu..." << endl;
					system("pause");
					break;
				}
				world.click(n);
			};
			break;
		case'3':
			exit(0);
			break;
		default:
			cout << "invalid choice\n";
			cout << "Please choose again!!!\n";
			break;
		}
	} while (choice != '3');
}
