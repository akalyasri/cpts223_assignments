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

    //cout << "testing" <<endl;

    cout << "Height of ascending tree : " << ascendTree.heightOfTree() << endl;
    cout << "Height of decending tree : " << decendTree.heightOfTree() << endl;
    cout << "Height of random-order tree : " << randomTree.heightOfTree() << endl;

    cout << "validate ascending tree : " << ascendTree.validate() << endl;
    cout << "validate decending tree : " << decendTree.validate() << endl;
    cout << "validate random-order tree : " << randomTree.validate() << endl;


    bool aResult, dResult, rResult;

    for(int i = 0; i <= 100 ; i++){

        aResult = ascendTree.contains(i);

        if((i%2 == 0) && (aResult == 1)){
            cout << "My AVL ascending tree implementation is incorrect" << endl;
        }


        dResult = decendTree.contains(i);

        if((i%2 == 0) && (dResult == 1)){
            cout << "My AVL decending tree implementation is incorrect" << endl;
        }



        rResult = randomTree.contains(i);

        if((i%2 == 0) && (rResult == 1)){
            cout << "My AVL random-order tree implementation is incorrect" << endl;
        }

    }
    
    return 0;
}