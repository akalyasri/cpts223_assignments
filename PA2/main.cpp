#include "avlTree.h"

int main(void){

    avlTree<int> ascendTree;
    avlTree<int> decendTree;
    avlTree<int> randomTree;

    vector<int> randOddNums;

    for(int i = 1; i<100 ; i+=2){
        ascendTree.insert(i);
        randOddNums.push_back(i);
    }

    for (int i = 99; i > 0; i -= 2){
        decendTree.insert(i);
    }

    //random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    random_shuffle(randOddNums.begin(),randOddNums.end());

    for (int i : randOddNums){
        randomTree.insert(i);
    }

    
    return 0;
}