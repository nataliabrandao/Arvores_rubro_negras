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

    printTreeRB(ptrTree->ptrRoot);

    cout << "O elemento de valor 60 é removido (se houver)" << endl;
    remove(ptrTree, 60);

    cout << "O elemento de valor 20 é removido (se houver)" << endl;
    remove(ptrTree, 20);

    return 0;
}