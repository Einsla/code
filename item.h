#pragma once
#include <iostream>
#include <string>
using namespace std;

struct effect {
	int round;
	string Eff;
	effect* link;

	effect() {
		round = 0;
		Eff = " ";
		link = nullptr;
	}
	~effect() {
		round = 0;
		Eff = " ";
		link = nullptr;
	}

	void apply() const {
		system("cls");
		if(Eff == "burn"){
			cout << "+------------------------------------------------+\n";
			cout << "| cause burn on target for " << round << " rounds              |\n";
			cout << "| target continuously loss hp...                 |\n";
			cout << "+------------------------------------------------+\n";
		}
		else if (Eff == "frozen") {
			cout << "+------------------------------------------------+\n";
			cout << "| cause frost on target for " << round << " rounds             |\n";
			cout << "| target can't move...                           |\n";
			cout << "+------------------------------------------------+\n";
		}
		else if (Eff == "electrocute") {
			cout << "+------------------------------------------------+\n";
			cout << "| cause electric on target for " << round << " rounds          |\n";
			cout << "| target loss 50 agility                         |\n";
			cout << "+------------------------------------------------+\n";
		}
		else if (Eff == "heal") {
			cout << "+------------------------------------------------+\n";
			cout << "| hp recover by 50 for " << round << " rounds                   |\n";
			cout << "| continuously recovering...                      |\n";
			cout << "+------------------------------------------------+\n";
		}
	}
};

class chain {
private:
	effect* first, * last;

public:
	chain() {
		first = last = nullptr;
	}
	~chain() {
		destroy();
	}

	void add_effect(string e, int r) {
		effect* add;
		add = new effect;
		add->Eff = e;
		add->round = r;
		add->link = nullptr;

		if (first == nullptr) {
			first = last = add;
		}
		else {
			last->link = add;
			last = add;
		}
	}
	void apply() {
		effect* temp;
		temp = first;
		while (temp != nullptr) {
			temp->apply();
			temp = temp->link;
		}
	}
	void destroy() {
		effect* temp;
		temp = first;
		while (temp != nullptr) {
			first = temp->link;
			delete temp;
			temp = first;
		}
		first = last = nullptr;
	}

	chain& operator=(const chain& other) {
		if (this != &other) {
			destroy();
			effect* temp = other.first;
			while (temp) {
				add_effect(temp->Eff, temp->round);
				temp = temp->link;
			}
		}
		return *this;
	}
};

class item {
private:
	int code,quantity;
	string name, description;
	chain status;

public:
	//c&d
	item() {
		code = quantity = 0;
		name = description = " ";
	}
	~item() {
		code = quantity = 0;
		name = description = " ";
	}

	void set(int c, int n, string na, string de, chain &s) {
		code = c;
		quantity = n;
		name = na;
		description = de;
		status = s;
	}
	string getname() {
		return name;
	}
	int getquantity() const {
		return quantity;
	}
	void use(int n) {
		quantity -= n;
		while (n > 0) {
			status.apply();
			n--;
		}
	}
	void display() {
		int n = 0;
		char c;
		do {
			system("cls");
			cout << name << endl;
			cout << description << endl;
			cout << quantity << endl;
			cout << "would you like to use this item?\n";
			cin >> c;
			if (c == 'Y') {
				cout << "How many item to be use?\n";
				cin >> n;
				if (n > quantity) {
					cout << "insufficient item\n";
				}
				else {
					use(n);
					return;
				}
			}
			else if (c == 'N') {
				return;
			}
			else {
				cout << "invalid command\n";
			}
			system("pause");
		} while ((c != 'N' and c != 'Y') or n > quantity);
		

	}
	void add(item &i) {
		quantity += i.quantity;
	}

	bool operator <(item& target) {
		return (code < target.code);
	}
	bool operator ==(item& target) {
		return code == target.code;
	}

	friend void create(item& a) {
		int c, q, r;
		string n, d, e;
		chain s;
		cout << "name        : ";
		getline(cin >> ws, n);
		cout << "description : ";
		getline(cin >> ws, d);
		cout << "code        : ";
		cin >> c;
		cout << "quantity    : ";
		cin >> q;
		while(true){
			cout << "effect      : ";
			getline(cin >> ws, e);
			if (e == "none") {
				break;
			}
			cout << "round       : ";
			cin >> r;
			s.add_effect(e,r);
		}
		a.set(c,q,n,d,s);
	}
};
