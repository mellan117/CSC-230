#include "tree.h"

int main(){
    
    tree<int> myTree;
    myTree.insert(5);
    myTree.insert(3);
    myTree.insert(2);
    myTree.insert(4);
    myTree.insert(8);
    myTree.insert(6);
    myTree.insert(7);
    myTree.insert(9);
    
    cout << myTree.treeBSearch(9) << endl;
    cout << myTree.treeBSearch(11) << endl;
    cout << myTree.nNodes() << endl;
    
    cout << "The Tree Looks Like: " << endl;
    myTree.print();
    
    tree<int> myTree2;
    myTree2.insert(4);
    myTree2.insert(2);
    myTree2.insert(1);
    myTree2.insert(3);
    
    myTree2.insert(7);
    myTree2.insert(5);
    
    
   // myTree2.print();
}