#include <iostream>
#include "libTreeRB/tree_rb.h"

int main() 
{
    Tree_RB* ptrTree = createTree();
    
    insert(ptrTree, 20);

    for (int i = 1; i < 30; i += 3)
    {
        insert(ptrTree, i);
    }

    cout << "Elementos da árvore : ";
    inorder(ptrTree->ptrRoot);
    cout << endl << endl;

    return 0;
}