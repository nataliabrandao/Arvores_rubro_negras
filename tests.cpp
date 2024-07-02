#include <iostream>
#include "libTreeRB/tree_rb.h"

int main() 
{
    Tree_RB* ptrTree = createTree();
    
    //Testando a insert: 
    insert(ptrTree, 20);

    for (int i = 1; i < 30; i += 3)
    {
        insert(ptrTree, i);
    }

    //Testando a inorder: 
    cout << "Elementos da árvore : ";
    inorder(ptrTree->ptrRoot);
    cout << endl << endl;

    printTreeRB(ptrTree->ptrRoot);

    //Testando a remove
    cout << "O elemento de valor 60 é removido (se houver)" << endl;
    remove(ptrTree, 60);

    cout << "O elemento de valor 20 é removido (se houver)" << endl;
    remove(ptrTree, 20);

    printTreeRB(ptrTree->ptrRoot);

    //Testando a search
    Node_RB* result1;
    result1 = search(ptrTree, 10);
    if (result1 != nullptr && result1->iValue == 10) {
        cout << "Teste 1 passou: 10 encontrado." << endl;
    } else {
        cout << "Teste 1 falhou: 10 não encontrado." << endl;
    }

    Node_RB* result2;
    result2 = search(ptrTree, 80);
    if (result2 != nullptr && result2->iValue == 80) {
        cout << "Teste 2 passou: 80 encontrado." << endl;
    } else {
        cout << "Teste 2 falhou: 80 não encontrado." << endl;
    }




    return 0;
}