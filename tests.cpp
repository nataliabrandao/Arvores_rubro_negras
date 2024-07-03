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

    //Testando isValid_Tree_RB
    cout << "A árvore é válida: " << isValid_Tree_RB(ptrTree) << " - (1 = sim, 0 = não)" << endl;

    //Testando a findMin
        Node_RB* result3 = findMin(ptrTree->ptrRoot);
    if (result3 != nullptr && result3->iValue == 1) {
        cout << "Teste passou: valor mínimo é 1." << endl;
    } else {
        cout << "Teste falhou: valor mínimo não é 1." << endl;
    }

    //Testando a findMax 
      Node_RB* result4 = findMax(ptrTree->ptrRoot);
    if (result4 != nullptr && result4->iValue == 28) {
        cout << "Teste passou: valor máximo é 28." << endl;
    } else {
        cout << "Teste falhou: valor máximo não é 28." << endl;
    }

    //Testando a height 
    cout << "Altura da árvore: " << height(ptrTree->ptrRoot) << endl;

    return 0;
}