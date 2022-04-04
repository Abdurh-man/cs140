#ifndef BST_H
#define BST_H

#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class TKey>
class bst {
	struct node {
		node(){ID = 0; parent = NULL;}//default value);
		int ID;
		void print();
		TKey key;
		node *parent;
		node *left;
		node *right;
	};

	public:
	bst() { ID = 0; Troot=NULL;}
	~bst() { clear(Troot); }
	bool empty() { return Troot==NULL; }
	void insert(TKey &);
	void print_bylevel();
	private:
	void clear(node *);
	node *insert(node *, TKey &);
	//node *ID;
	
	int ID;
	node *Troot;
};
//	
//template <class Tkey>
//bst<TKey>::node::node(){
//	parent = NULL;
//}

	template <>
void bst<int>::node::print()
{
	cout << setw(3) << ID << ' ';
	cout << setw(3) << key << " :";

	if(parent == NULL)
		cout << " ROOT ";
	else
		cout <<" P=" << setw(3) << parent->ID;
	// output node and parent ID information
	// change below to output subtree ID information
	if (left)  cout << " L=" << setw(3) << left->ID;
	else       cout << "      ";
	if (right) cout << " R=" << setw(3) << right->ID;
	else       cout << "      ";

	cout << "\n";
}
//// specialized string version of the above goes here
	template <>
void bst<string>::node::print(){
	cout << setw(3) << ID << ' ';
	cout << setw(20) << key << " :";

	//if(parent->ID == 0)
	if(parent == NULL)
		cout << " ROOT ";
	else
		cout <<" P=" << setw(3) << parent->ID;
	// output node and parent ID information
	// change below to output subtree ID information
	if (left)  cout << " L=" << setw(3) << left->ID;
	else       cout << "      ";
	if (right) cout << " R=" << setw(3) << right->ID;
	else       cout << "      ";

	cout << "\n";
}	

// bst<TKey>::iterator functions not defined above go here

	template <class TKey>
void bst<TKey>::clear(node *T)
{
	if (T) {
		clear(T->left);
		clear(T->right);
		delete T;
		T = NULL;
	}
}

	template <class TKey>
void bst<TKey>::insert(TKey &key)
{ 
	Troot = insert(Troot, key);
}

	template <class TKey>
class bst<TKey>::node *bst<TKey>::insert(node *T, TKey &key)
{
	//set parent link below
	node n;
	if (T == NULL) {
		//update and set node ID 
		ID+=1;  
		T = new node;
		T->ID=ID;
		T->key = key;
	} else if (T->key == key) {
		;
	} else if (key < T->key) {
		T->left = insert(T->left, key);
		T ->left-> parent = T;
	
		//n.parent->T->left = T;
//		left->parent = T;
	} else {
		T->right = insert(T->right, key);
		T ->right-> parent = T;
//		n.parent = T->right;
//		T = n.parent->right;
//		rigt->parent = T;
	}
	//	parent = T;

	return T;
}
	
	template <class TKey>
void bst<TKey>::print_bylevel()
{
	if (Troot == NULL)
		return;

	queue<node *> Q;
	node *T;

	Q.push(Troot);
	while (!Q.empty()) {
		T = Q.front();
		Q.pop();

		T->print();
		if (T->left)  Q.push(T->left);
		if (T->right) Q.push(T->right);
	}
}
#endif
