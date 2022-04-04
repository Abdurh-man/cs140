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
		node(){ID = 0; parent = NULL;}
		int ID;
		void print();
		TKey key;
		node *parent;
		node *left;
		node *right;
	};


	public:
	class iterator {
		public:
			//default constructor (no argument)
			//overloaded operators (++, *, ==, !=)
			iterator();
			iterator & operator++();
			TKey & operator*();
			bool operator==(const iterator &) const;
			bool operator!=(const iterator &) const;
		private:
			friend class bst<TKey>;
			//constructor (with argument)
			iterator(node *);
			//iterator pointer
			node *p;
	};
	//points to the left most value
	iterator begin();
	//points to NULL 
	iterator end();



	public:
	bst() { ID = 0; Troot=NULL;}
	~bst() { clear(Troot); }
	bool empty() { return Troot==NULL; }
	void insert(TKey &);
	void print_bylevel();
	
	iterator lower_bound(const TKey &);
	iterator upper_bound(const TKey &);

	private:
	void clear(node *);
	node *insert(node *, TKey &);

	int ID;
	node *Troot;
};
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
// specialized string version of the above goes here
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
	} else {
		T->right = insert(T->right, key);
		T ->right-> parent = T;
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

	template <class TKey>
bst<TKey>::iterator::iterator(){
	p = NULL;	
}

	template <class TKey>
bst<TKey>::iterator::iterator(bst<TKey>::node *ptr){
	p = ptr;
}

	template <class TKey>
typename bst<TKey>::iterator & bst<TKey>::iterator::operator++(){
	// if you can go right go right once
	if(p->right != NULL){
		p = p->right;
		//then go as left as possible
		while(p->left != NULL)
			p = p->left;	
	}
	// othewise go up
	else{
		node *up = p->parent;
		//while up exist and p is the right child or up
		while(up != NULL && p == up->right){
			p = up; 
			up = up->parent;
		}
		// updating the iterator pointer p accordingly
		p = up;
	}
	// return p
	return *this;
}

	template <class TKey>
TKey & bst<TKey>::iterator::operator*(){
	return p->key;
}

	template <class TKey>
bool bst<TKey>::iterator::operator==(const bst<TKey>::iterator &rhs) const{
	//condition ? result_if_true : result_if_false
	return (p == rhs.p ? true : false);
}

	template <class TKey>
bool bst<TKey>::iterator::operator!=(const bst<TKey>::iterator &rhs) const{
	return (p != rhs.p ? true : false);
}

	template <class TKey>
typename bst<TKey>::iterator bst<TKey>::begin(){	
	if(Troot == NULL)
		return iterator(NULL);
	
	node *min = Troot;
	//goes as far left as possible
	while(min->left != NULL){
		min = min->left;
	}
	//returns left most which is also the min value
	return iterator(min);
}

	template <class TKey>
typename bst<TKey>::iterator bst<TKey>::end(){
	return iterator(NULL);
}


	template <class TKey>
typename bst<TKey>::iterator bst<TKey>::lower_bound(const TKey& key0){
	// start at the root goes as far left as possible
	// if that doesnt work goes to the parent
	// if that doesnt work goes to the child
	node *compare = Troot;
	node *mother = NULL;
	while(compare != NULL){
		if(key0 <= compare->key){
			mother = compare;
			compare = compare->left;
		}
		else{
			compare = compare->right;
		}
	}
	return iterator(mother);
}

	template <class TKey>
typename bst<TKey>::iterator bst<TKey>::upper_bound(const TKey& key1){
	node *compare = Troot;
	node *mother = NULL;
	while(compare != NULL){
		if(key1 < compare->key){
			mother = compare;
			compare = compare->left;
		}
		else{
			compare = compare->right;
		}
	}
	return iterator(mother);
}
#endif
