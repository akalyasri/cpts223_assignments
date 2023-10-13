#include "avlNode.h"

template<class T>

class avlTree{

public:
    avlTree(){
        root = nullptr;
    }

    bool contains(const T& value){

        return containsHelper(root, value);
    }

    void printTree(void){

        printTreeHelper(root);
        cout << endl;
    }

    void remove(const T& value){
        
        removeHelper(root, value);
    }

    void insert(const T& value){

        insertHelper(root, value);
    }



private:

    avlNode<T>* root;

    void printTreeHelper(avlNode<T>* node){

        if(node == nullptr){
            return;
        }

        queue<avlNode<T>*> curLevel, nexLevel;

        curLevel.push(root);

        while(!curLevel.empty()){

            avlNode<T>* cur = curLevel.front();
            curLevel.pop();

            if(cur != nullptr){

                cout << cur->key << " ";

                nexLevel.push(cur->left);
                nexLevel.push(cur->right);

            }

            if(curLevel.empty()){
                cout << endl;
                swap(curLevel,nexLevel);
            }
        }
    }

    void height(avlNode<T>* &node){

        if(node->left == nullptr && node->right == nullptr){

            node->height = 0;

        } else if(node->left == nullptr){

            node->height = (node->right)->height + 1;

        } else if(node->right == nullptr){

            node->height = (node->left)->height + 1;

        } else{

            node->height = max((node->left)->height, (node->right)->height) +1;
        }

    }

    bool containsHelper(avlNode<T>* root, const T& value){

        if(root == nullptr){

            return false;

        } else if(root->key == value){

            return true;
        } 

        if(value < root->key){

            containsHelper(root->left, value);

        } else if(value > root->key){

            containsHelper(root->right, value);
        }


    }

    void Rrotation(avlNode<T>* &node){

        avlNode<T>* Lnode = node->left;
        avlNode<T>* tempNode = node;

        node->left = Lnode->right;
        Lnode->right = node;
        node = Lnode;

        height(tempNode);
        height(Lnode);
        height(node);
    }

    void Lrotation(avlNode<T>* &node){

        avlNode<T>* Rnode = node->right;
        avlNode<T>* tempNode = node;

        node->right = Rnode->left;
        Rnode->left = node;
        node = Rnode;

        height(tempNode);
        height(Rnode);
        height(node);
    }


    int balanceFactor(avlNode<T>* node){

        if(node == nullptr){

            return 0;

        } else{

            if(node->left == nullptr && node->right == nullptr){

                return 0;

            } else if(node->left == nullptr){

                return (-1) - (node->right)->height;

            } else if (node->right == nullptr){
                 
                return (node->left)->height + 1;

            } else {

                return (node->left)->height - (node->right)->height;
            }

        }

    }

    void determineRotation(avlNode<T>* &node, int& bFactor){

        if(bFactor > 1 && balanceFactor(node->left) >= 0){

            Rrotation(node);   
        }

        if(bFactor < -1 && balanceFactor(node->right) <= 0){

            Lrotation(node);
        }

        if(bFactor > 1 && balanceFactor(node->left) < 0) {

            Lrotation(node->left);
            Rrotation(node);
        }

        if(bFactor < -1 && balanceFactor(node->right) > 0){

            Rrotation(node->right);
            Lrotation(node);
        }
    }



    void removeHelper(avlNode<T>* &root, const T& value){

        if(root == nullptr){
            return;
        }

        if(value < root->key){
            removeHelper(root->left, value);
        
        } else if(value > root->key){

            removeHelper(root->right, value);
        } else {

            if((root->left == nullptr) && (root->right == nullptr)){
                root = nullptr;
            
            } else if(root->left == nullptr){

                avlNode<T>* temp = root;
                root = root->right;
                delete temp;
            
            } else if(root->right == nullptr){

                avlNode<T>* temp = root;
                root = root->left;
                delete temp;
            
            } else {

                avlNode<T>* temp = root->right;

                while(temp->left != nullptr){

                    temp = temp->left;
                }

                root->key = temp->key;

                removeHelper(root->right, temp->key);
            }


        }

        if(root == nullptr){
            return;
        }

        height(root);

        int bFactor = balanceFactor(root);

        determineRotation(root, bFactor);

    }



    void insertHelper(avlNode<T>* &node, const T& value){

        if(node == nullptr){

            node = new avlNode<T>(value);
        
        } else if(value > node->key){

            insertHelper(node->right, value);

        } else {

            insertHelper(node->left, value);

        }

        height(node);

        int bFactor = balanceFactor(node);

        determineRotation(node, bFactor);


    }










};