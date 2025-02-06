#include <iostream>
#include <cassert>
using namespace std;

template <typename Type>
struct node {
	Type data;
	node<Type>* left;
	node<Type>* right;
};

template<typename Type>
class BinTree {
private:
	node<Type>* root;

	//helper function
	void insert(node<Type>* key, node<Type>* current) {
		if (key == nullptr) {
			return;
		}
		else if (key->data < current->data) {
			if (current->left != nullptr) {		//have left child continue loop until no left child
				insert(key, current->left);
			}
			else {
				current->left = key;
			}
			return;
		}
		else if (key->data > current->data) {
			if (current->right != nullptr) {	//have right child continue loop until no right child
				insert(key, current->right);
			}
			else {
				current->right = key;
			}
			return;
		}
		else {
			cout << "repeated key, key ignored\n";
			return;
		}
	}
	void del(Type key, node<Type>* current) {
		if (current == nullptr) {
			cout << "invalid key\n";
			return;
		}
		if (key < current->data) {
			del(key, current->left);
		}
		else if (key > current->data) {
			del(key, current->right);
		}
		else if (key == current->data) {
			node<Type>* temp;
			temp = current;
			if (current->left == nullptr && current->right == nullptr) {	//no children(leaf)
				current = nullptr;
				delete temp;
			}
			else if (current->left == nullptr) {							//right child only
				current = current->right;
				delete temp;
			}
			else if (current->right == nullptr) {							//left child only
				current = current->left;
				delete temp;
			}
			else {															//have both children
				current->data = minval(current->right);
				del(current->data, current->right);
			}
		}
	}
	void destroy(node<Type>*& current) {
		if (current != nullptr) {
			destroy(current->left);
			destroy(current->right);
			delete current;
			current = nullptr;
		}
	}
	Type minval(node<Type>* current) {			//use to find left most value
		if (current->left != nullptr) {
			return minval(current->left);
		}
		else {
			return current->data;
		}
	}

public:
	//constructor & destructor
	BinTree() {
		root = nullptr;
	}
	~BinTree() {
		Destroy();
	}

	//method
	void Insert(Type key) {
		node<Type>* newnode;
		newnode = new node<Type>;
		assert(newnode != nullptr);
		newnode->data = key;
		newnode->left = newnode->right = nullptr;

		if (root == nullptr) {
			root = newnode;
		}
		else {
			insert(newnode, root);
		}
		cout << "key updated\n";
	}
	void Delete(Type key) {
		if (root == nullptr) {
			cout << "no binary tree detected\n";
		}
		else {
			del(key, root);
		}
	}
	void Destroy() {
		destroy(root);
	}
	node<Type>* Search(Type key, node<Type>* current = nullptr) const {
		if (current == nullptr) { 
			current = root;
		}
		if (current->data == key) {
			cout << "key found\n";
			return current;
		}
		else {
			node<Type>* temp = nullptr;
			if (current->left != nullptr) {
				temp = Search(key, current->left);
			}
			if (temp == nullptr && current->right != nullptr) {
				temp = Search(key, current->right);
			}
			return temp;
		}
	}


	//order display
	//1. left->node->right
	void Inorder(node<Type>* key = nullptr) const {
		if (key == nullptr) {
			if (root != nullptr) {
				key = root;
			}
			else {
				cout << "no binary tree detected!\n";
				return;
			}
		}
		if (key->left != nullptr) {
			Inorder(key->left);
		}
		cout << key->data << "\n";
		if (key->right != nullptr) {
			Inorder(key->right);
		}
	}
	//2. node->left->right
	void Preorder(node<Type>* key = nullptr) const {
		if (key == nullptr) {
			if (root != nullptr) {
				key = root;
			}
			else {
				cout << "no binary tree detected!\n";
				return;
			}
		}
		cout << key->data << "\n";
		if (key->left != nullptr) {
			Preorder(key->left);
		}
		if (key->right != nullptr) {
			Preorder(key->right);
		}
	}
	//3. left->right->node
	void Postorder(node<Type>* key = nullptr) const {
		if (key == nullptr) {
			if (root != nullptr) {
				key = root;
			}
			else {
				cout << "no binary tree detected!\n";
				return;
			}
		}
		if (key->left != nullptr) {
			Postorder(key->left);
		}
		if (key->right != nullptr) {
			Postorder(key->right);
		}
		cout << key->data << "\n";
	}
};

int main() {
	int choice, item;
	node<int> *leaf;
	BinTree<int> tree;
	do {
		system("cls");
		cout << "========================================\n";
		cout << "	Welcome to my item tree	\n";
		cout << "========================================\n";
		cout << endl;
		cout << "Available action:\n";
		cout << "1.insert key\n";				//insert item
		cout << "2.delete key\n";				//delete item
		cout << "3.destroy the tree \n";		//destroy list
		cout << "4.print tree (inorder) \n";	//print list
		cout << "5.print tree (preorder) \n";	//print list
		cout << "6.print tree (postorder) \n";	//print list
		cout << "7.find 'someone'\n";			//find item
		cout << "\n\n\nSo what will you do?\n";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "enter item to store in this world:\n";
			cin >> item;
			tree.Insert(item);
			break;
		case 2:
			cout << "enter item to be used:\n";
			cin >> item;
			tree.Delete(item);
			break;
		case 3:
			tree.Destroy();
			break;
		case 4:
			tree.Inorder();
			break;
		case 5:
			tree.Preorder();
			break;
		case 6:
			tree.Postorder();
			break;
		case 7:
			cout << "enter leaf to be expected in this tree:\n";
			cin >> item;
			leaf = tree.Search(item);
			break;
		defalut:
			cout << "invalid choice. Please try again:\n";
			break;
		}
		system("pause");
	} while (choice != 0);
}