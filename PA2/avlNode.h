#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using std::cout;
using std::endl;
using std::queue;
using std::shuffle;
using std::vector;
using std::random_shuffle;
using std::max;


template <class T>

class avlNode{

    public:

    avlNode(){
        left = nullptr;
        right = nullptr;
        height = 0;

    }

    avlNode(const T& value, avlNode* Lptr = nullptr, avlNode* Rptr = nullptr){
        key = value;
        left = Lptr;
        right = Rptr;
        height = 0;
    }


    T key;
    avlNode<T>* left;
    avlNode<T>* right;
    int height;


};