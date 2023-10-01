#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include <vector>
using namespace std;


/*
 *  Data structure for a single tree node
 */
template <typename T>
struct Node {
public:
	T value;
	Node* left;
	Node* right;

	Node(T val) {
		this->value = val;
		this->left = nullptr;
		this->right = nullptr;
	}

	~Node()
	{
		this->value = 0;
		this->left = nullptr;
		this->right = nullptr;
	}
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <typename T>
class BST {

protected:
	Node<T>* _root;         // Root of the tree nodes

	/* Add new T val to the tree */
	void addHelper(Node<T>* root, T val) {
		if (root->value > val) {
			if (!root->left) {
				root->left = new Node<T>(val);
			}
			else {
				addHelper(root->left, val);
			}
		}
		else {
			if (!root->right) {
				root->right = new Node<T>(val);
			}
			else {
				addHelper(root->right, val);
			}
		}
	}

	/* Print tree out in inorder (A + B) */
	void printInOrderHelper(Node<T>* root) {
		if (!root) return;
		printInOrderHelper(root->left);
		cout << root->value << ' ';
		printInOrderHelper(root->right);
	}

	/* Return number of nodes in tree */
	int nodesCountHelper(Node<T>* root) {
		if (!root) {
			return 0;
		}
		else {
			return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
		}
	}

	/* Return height of tree (root == nullptr -> 0) */
	int heightHelper(Node<T>* root) {
		if (!root) {
			return -1;
		}
		else {
			return 1 + max(heightHelper(root->left), heightHelper(root->right));
		}
	}

	/* Delete a given <T> value from tree */
	bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
		if (!current) return false;
		if (current->value == value) {
			if (current->left == nullptr || current->right == nullptr) {
				Node<T>* temp = current->left;
				if (current->right) temp = current->right;
				if (parent) {
					if (parent->left == current) {
						parent->left = temp;
					}
					else {
						parent->right = temp;
					}
				}
				else {
					this->_root = temp;
				}
			}
			else {
				Node<T>* validSubs = current->right;
				while (validSubs->left) {
					validSubs = validSubs->left;
				}
				T temp = current->value;
				current->value = validSubs->value;
				validSubs->value = temp;
				return deleteValueHelper(current, current->right, temp);
			}
			delete current;
			return true;
		}
		return deleteValueHelper(current, current->left, value) ||
			deleteValueHelper(current, current->right, value);
	}


	void destroyTreeHelper(Node <T>* node){
		if(node != nullptr){
			  destroyTreeHelper(node->left);
			  destroyTreeHelper(node->right);
			  delete node;
		}

	}

	void printLevelOrderHelper(Node<T>* pCur){
		//int height = 
	}

	bool containsHelper(Node<T>* pCur, T value){
		if(pCur == nullptr){
			return false;
		}

		if(value == pCur->value){
			return true;

		} else if(value < pCur->value){			
			return containsHelper(pCur->left, value);

		} else{
			return containsHelper(pCur->right, value);
		}
	}




	void findMaxPath(Node<T>* pCur, vector<T>& currentP, vector<T>& longestP){
		
		//void findMaxPath(Node<T>* pCur, vector<T>& path){
		//if(pCur == nullptr){
		//	return;
		//}

		//vector<T> Lpath, Rpath;

		//findMaxPath(pCur->left,Lpath);
		//findMaxPath(pCur->right,Rpath);

		//vector<T>& mPath = (Lpath.size() > Rpath.size()) ? Lpath : Rpath;

		/*	if(Lpath.size() > Rpath.size()){
				vector<T>& mPath = Lpath;
			} else{
				vector<T>& mPath = Rpath;
			}
		*/

		//if(!mPath.empty() || pCur == _root){
		//	mPath.push_back(pCur->value);
		//}

		//if(mPath.size() > path.size()){
			//path = mPath;
		//}

		if(!pCur){
			return;
		}
		
		currentP.push_back(pCur->value);

		if(!pCur->left && !pCur->right){
			if(currentP.size() > longestP.size()){
				longestP = currentP;
			}
		}

		findMaxPath(pCur->left,currentP,longestP);
		findMaxPath(pCur->right,currentP,longestP);

		currentP.pop_back();

		
	}





	/********************************* PUBLIC API *****************************/
public:

	BST() : _root(nullptr) { }               // Basic initialization constructor

	/**
	 * Destructor - Needs to free *all* nodes in the tree
	 * TODO: Implement Destructor
	 */
	~BST() {	
		
		cout << "Implementing Destructor..." << endl;
		destroyTreeHelper(_root);
		//debugged - works correctly

	}

	/* Public API */
	void add(T val) {
		if (this->_root) {
			this->addHelper(this->_root, val);
		}
		else {
			this->_root = new Node<T>(val);
		}
	}

	void print() {
		printInOrderHelper(this->_root);
	}

	/**
	 * Print the nodes level by level, starting from the root
	 * TODO: Implement printLevelOrder
	 */
	void printLevelOrder() {
		//currently working 

		cout << "TODO: Implement printLevelOrder" << endl;
	}

	int nodesCount() {
		return nodesCountHelper(this->_root);
	}

	int height() {
		return heightHelper(this->_root);
	}

	/**
	 * Print the maximum path in this tree
	 * TODO: Implement printMaxPath
	 */
	void printMaxPath() {

		//vector<T> maxPath;
		//Node<T>* pCur = _root;
		//findMaxPath(_root, maxPath);


////

		vector<T> Cpath, Lpath;
		findMaxPath(_root,Cpath, Lpath);

		for(const T& i : Lpath){ //maxPath
			cout << i << " ";
		}
		
	}

	bool deleteValue(T value) {
		return this->deleteValueHelper(nullptr, this->_root, value);
	}

	/**
	 * Find if the BST contains the value
	 * TODO: Implement contains
	 */
	bool contains(T value) {
	    //cout << "Implementing contains ..." << endl;
		//return numeric_limits<T>::min();

		return containsHelper(_root, value);
	}
};

#endif

