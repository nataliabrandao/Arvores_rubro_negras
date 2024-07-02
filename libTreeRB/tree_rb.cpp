#include "tree_rb.h"

// ==================================================
// ===== Implementação das funções requisitadas =====
// ==================================================

void insert(Tree_RB* ptrTree, int iValue)
{
    // Inserção do primeiro nó da árvore
    if (ptrTree->ptrRoot == nullptr) 
    {
        ptrTree->ptrRoot = createNode(iValue, BLACK);
        return;
    }    

    // Inserção de um nó na árvore
    Node_RB* ptrCurrent = ptrTree->ptrRoot;
    Node_RB* ptrParent = nullptr;

    while (ptrCurrent != nullptr)
    {
        ptrParent = ptrCurrent;

        if (iValue < ptrCurrent->iValue)
        {
            ptrCurrent = ptrCurrent->ptrLeft;
        }
        else 
        {
            ptrCurrent = ptrCurrent->ptrRight;
        }
    }

    Node_RB* ptrNew = createNode(iValue, RED);
    ptrNew->ptrParent = ptrParent;

    if (iValue < ptrParent->iValue)
    {
        ptrParent->ptrLeft = ptrNew;
    }
    else
    {
        ptrParent->ptrRight = ptrNew;
    }
    
    // Ajusta a árvore para manter as propriedades da árvore rubro-negra
    insertFixup(ptrTree, ptrNew);
}

void inorder(Node_RB* ptrNode)
{
    if (ptrNode == nullptr) { return; }

    inorder(ptrNode->ptrLeft);
    
    if (ptrNode->bColor == RED) {
        cout << red << ptrNode->iValue << reset << " ";
    } else {
        cout << ptrNode->iValue << " ";
    }

    inorder(ptrNode->ptrRight);
}

void remove(Tree_RB* ptrTree, int iValue)
{
    Node_RB* ptrRemove = search(ptrTree, iValue);
    if (ptrTree->ptrRoot == nullptr || ptrRemove == nullptr) { return; }

    bool bOriginalColor = ptrRemove->bColor;
    Node_RB* ptrChild = nullptr;
    
    // Caso 1: Filho à esquerda é nulo
    if (ptrRemove->ptrLeft == nullptr) 
    {
        ptrChild = ptrRemove->ptrRight;
        transplant(ptrTree, ptrRemove, ptrChild);
    }
    // Caso 2: Filho à direita é nulo
    else if (ptrRemove->ptrRight == nullptr) 
    {
        ptrChild = ptrRemove->ptrLeft;
        transplant(ptrTree, ptrRemove, ptrChild);
    }
    else // Caso 3: Nenhum filho é nulo 
    {
        Node_RB* ptrSubMin = findMin(ptrRemove->ptrRight);
        bOriginalColor = ptrSubMin->bColor; 
        ptrChild = ptrSubMin->ptrRight;

        if (ptrSubMin->ptrParent == ptrRemove) 
        {
            ptrChild->ptrParent = ptrSubMin;
        } 
        else 
        {
            transplant(ptrTree, ptrSubMin, ptrChild);
            ptrSubMin->ptrRight = ptrRemove->ptrRight;
            ptrRemove->ptrRight->ptrParent = ptrSubMin;
        }

        transplant(ptrTree, ptrRemove, ptrSubMin);
        ptrSubMin->ptrLeft = ptrRemove->ptrLeft;
        ptrRemove->ptrLeft->ptrParent = ptrSubMin;
        // Transfere a cor do nó removido para o sucessor
        ptrSubMin->bColor = ptrRemove->bColor;  
    }

    delete ptrRemove; // Deleta efetivamente o nó

    // Garante que a árvore é válida após a remoção
    if (bOriginalColor == BLACK) {
        removeFixup(ptrTree, ptrChild);
    }
}

Node_RB* search(Tree_RB* ptrTree, int value)
{
    Node_RB* ptrCurrent = ptrTree->ptrRoot;

    while (ptrCurrent != nullptr) 
    {
        if (value == ptrCurrent->iValue) 
        {
            return ptrCurrent; // Nó encontrado
        } 
        else if (value < ptrCurrent->iValue) {
            // Procura na subárvore esquerda
            ptrCurrent = ptrCurrent->ptrLeft; 
        } else {
            // Procura na subárvore direita
            ptrCurrent = ptrCurrent->ptrRight; 
        }
    }

    return nullptr; // Nó não encontrado
}

Node_RB* findMin(Node_RB* ptrRoot)
{
    if (ptrRoot == nullptr) { return nullptr; }

    Node_RB* ptrCurrent = ptrRoot;

    while(ptrCurrent->ptrLeft != nullptr)
    {
        ptrCurrent = ptrCurrent->ptrLeft;
    }

    return ptrCurrent;
}

bool isValid_Tree_RB(Tree_RB* ptrTree) 
{
    if(ptrTree == nullptr) return true;

    Node_RB* ptrNode = ptrTree->ptrRoot;

    // Verifica raiz
    if(ptrNode->bColor != BLACK) {
        cerr << "Violação: a raíz não é preta." << endl;
        return false;
    }

    // Verifica os nós vermelhos
    if(!verifyRedNodes(ptrNode)) {
        cerr << "Violação: os nós vermelhos tem filhos pretos." << endl;
        return false;
    }

    // Verifica a altura pretas de um caminho
    int iCountBlack = 0;
    Node_RB* temp = ptrNode;
    while(temp != nullptr) {
        if (temp->bColor == BLACK) iCountBlack++;
        temp = temp->ptrLeft;
    }

    if(!verifyBlackNodes(ptrNode, iCountBlack, 0)) {
        cerr << "Violação: Os caminho até as folhas (NIL) não tem o mesmo número de nós pretos." << endl;
        return false;
    }

    return true;
}



// ============================================
// ===== Declaração de funções auxiliares =====
// ============================================


Tree_RB* createTree()
{
    Tree_RB* ptrTree = new Tree_RB;
    return ptrTree;
}

Node_RB* createNode(int iValue)
{
    Node_RB* ptrNode = new Node_RB;
    ptrNode->iValue = iValue;
    ptrNode->bColor = RED;
    return ptrNode;
}


Node_RB* createNode(int iValue, Color color)
{
    Node_RB* ptrNode = new Node_RB;
    ptrNode->iValue = iValue;
    ptrNode->bColor = color;
    return ptrNode;
}


void insertFixup(Tree_RB* ptrTree, Node_RB* ptrNew) 
{
    while (ptrNew != ptrTree->ptrRoot && ptrNew->ptrParent->bColor == RED) 
    {
        if (ptrNew->ptrParent == ptrNew->ptrParent->ptrParent->ptrLeft) 
        {
            Node_RB* ptrUncle = ptrNew->ptrParent->ptrParent->ptrRight;

            // Case A1: Tio é vermelho
            if (ptrUncle != nullptr && ptrUncle->bColor == RED) 
            {
                ptrNew->ptrParent->bColor = BLACK;
                ptrUncle->bColor = BLACK;
                ptrNew->ptrParent->ptrParent->bColor = RED;
                ptrNew = ptrNew->ptrParent->ptrParent;
            }
            else 
            {
                // Case A2: Tio é preto e se alinha formando um triângulo
                if (ptrNew == ptrNew->ptrParent->ptrRight) 
                {
                    ptrNew = ptrNew->ptrParent;
                    rotateLeft(ptrTree, ptrNew);
                }

                // Case A3: Tio é preto e se alinha formando uma linha
                ptrNew->ptrParent->bColor = BLACK;
                ptrNew->ptrParent->ptrParent->bColor = RED;
                rotateRight(ptrTree, ptrNew->ptrParent->ptrParent);
            }
        } 
        else 
        {
            // Caso simétrico ao anterior, trocando direita por esquerda e vice-versa
            Node_RB* ptrUncle = ptrNew->ptrParent->ptrParent->ptrLeft;

            if (ptrUncle != nullptr && ptrUncle->bColor == RED) 
            {
                ptrNew->ptrParent->bColor = BLACK;
                ptrUncle->bColor = BLACK;
                ptrNew->ptrParent->ptrParent->bColor = RED;
                ptrNew = ptrNew->ptrParent->ptrParent;
            } 
            else 
            {
                if (ptrNew == ptrNew->ptrParent->ptrLeft) 
                {
                    ptrNew = ptrNew->ptrParent;
                    rotateRight(ptrTree, ptrNew);
                }
                
                ptrNew->ptrParent->bColor = BLACK;
                ptrNew->ptrParent->ptrParent->bColor = RED;
                rotateLeft(ptrTree, ptrNew->ptrParent->ptrParent);
            }
        }
    }

    // Garante um critério para válidade da árvore, sua raiz sempre será preta
    ptrTree->ptrRoot->bColor = BLACK;
}


Node_RB* rotateRight(Tree_RB* ptrTree, Node_RB* ptrNode) 
{
    Node_RB* ptrGrandparent = ptrNode->ptrParent; 
    Node_RB* ptrPivot = ptrNode->ptrLeft;
    Node_RB* ptrChild = nullptr;
    
    if (ptrPivot != nullptr) 
    {
        ptrChild = ptrPivot->ptrRight;
        
        // Realizar a rotação
        ptrNode->ptrLeft = ptrChild;
        ptrPivot->ptrRight = ptrNode;

        // Atualizar os ponteiros de parentesco
        ptrNode->ptrParent = ptrPivot;
        ptrPivot->ptrParent = ptrGrandparent;
        if (ptrChild != nullptr) {
            ptrChild->ptrParent = ptrNode;
        }

        // Atualizar o ponteiro do ancestral
        if (ptrGrandparent != nullptr) {
            if (ptrGrandparent->ptrLeft == ptrNode) {
                ptrGrandparent->ptrLeft = ptrPivot;
            } else {
                ptrGrandparent->ptrRight = ptrPivot;
            }
        } else {
            // Caso a subárvore seja a árvore inteira
            ptrTree->ptrRoot = ptrPivot;
        }
        
        return ptrPivot;
    }

    // Retorno de um ponteiro nulo, caso a rotação não seja possível
    return nullptr;
}

Node_RB* rotateLeft(Tree_RB* ptrTree, Node_RB* ptrNode) 
{
    Node_RB* ptrGrandparent = ptrNode->ptrParent; 
    Node_RB* ptrPivot = ptrNode->ptrRight;
    Node_RB* ptrChild = nullptr;
    
    if (ptrPivot != nullptr) 
    {
        ptrChild = ptrPivot->ptrLeft;
        
        // Realizar a rotação
        ptrNode->ptrRight = ptrChild;
        ptrPivot->ptrLeft = ptrNode;

        // Atualizar os ponteiros de parentesco
        ptrNode->ptrParent = ptrPivot;
        ptrPivot->ptrParent = ptrGrandparent;
        if (ptrChild != nullptr) {
            ptrChild->ptrParent = ptrNode;
        }

        // Atualizar o ponteiro do ancestral
        if (ptrGrandparent != nullptr) {
            if (ptrGrandparent->ptrLeft == ptrNode) {
                ptrGrandparent->ptrLeft = ptrPivot;
            } else {
                ptrGrandparent->ptrRight = ptrPivot;
            }
        } else {
            // Caso a subárvore seja a árvore inteira
            ptrTree->ptrRoot = ptrPivot;
        }
        
        return ptrPivot;
    }

    // Retorno de um ponteiro nulo, caso a rotação não seja possível
    return nullptr;
}

void printTreeRB(string sPrefix, Node_RB* ptrNode, bool isLeft)
{
    if (ptrNode != nullptr)
    {
        cout << sPrefix;

        cout << (isLeft ? "├──" : "└──");

        // print the value of the ptrNode
        if (ptrNode->bColor == RED)
        {
            cout << red << ptrNode->iValue << reset << " ";
        }
        else
        {
            cout << ptrNode->iValue << " ";
        }
        cout << endl;

        // enter the next tree level - left and right branch
        printTreeRB(sPrefix + (isLeft ? "│   " : "    "), ptrNode->ptrLeft, true);
        printTreeRB(sPrefix + (isLeft ? "│   " : "    "), ptrNode->ptrRight, false);
    }
}

void printTreeRB(Node_RB* ptrNode)
{
    printTreeRB("", ptrNode, false);
}

void transplant(Tree_RB* ptrTree, Node_RB* ptrNode, Node_RB* ptrSubRoot) {
    if (ptrNode->ptrParent == nullptr) 
    {
        ptrTree->ptrRoot = ptrSubRoot;
    } 
    else if (ptrNode == ptrNode->ptrParent->ptrLeft) 
    {    
        ptrNode->ptrParent->ptrLeft = ptrSubRoot;
    } 
    else {
        ptrNode->ptrParent->ptrRight = ptrSubRoot;
    }

    if (ptrSubRoot != nullptr) {
        ptrSubRoot->ptrParent = ptrNode->ptrParent;
    }
}

void removeFixup(Tree_RB* ptrTree, Node_RB* ptrChild) 
{
    if (ptrChild == nullptr) { return; }

    while (ptrChild != ptrTree->ptrRoot && ptrChild->bColor == BLACK) 
    {
        // Verifica se correções são necessárias
        if (ptrChild != ptrChild->ptrParent->ptrLeft) { break;}

        Node_RB* ptrSibling = ptrChild->ptrParent->ptrRight;

        // Caso 1:
        if (ptrSibling->bColor == RED) 
        {
            ptrSibling->bColor = BLACK;
            ptrChild->ptrParent->bColor = RED;
            rotateLeft(ptrTree, ptrChild->ptrParent);
            ptrSibling = ptrChild->ptrParent->ptrRight;
        }

        // Caso 2:
        if (ptrSibling->ptrLeft->bColor == BLACK && ptrSibling->ptrRight->bColor == BLACK) 
        {
            ptrSibling->bColor = RED;
            ptrChild = ptrChild->ptrParent;
        }
        else {
            // Caso 3:
            if (ptrSibling->ptrRight->bColor == BLACK) 
            {
                ptrSibling->ptrLeft->bColor = BLACK;
                ptrSibling->bColor = RED;
                rotateRight(ptrTree, ptrSibling);
                ptrSibling = ptrChild->ptrParent->ptrRight;
            }
            // Caso 4:
            ptrSibling->bColor = ptrChild->ptrParent->bColor;
            ptrChild->ptrParent->bColor = BLACK;
            ptrSibling->ptrRight->bColor = BLACK;
            rotateLeft(ptrTree, ptrChild->ptrParent);
            ptrChild = ptrTree->ptrRoot;
        }   
    }

    ptrChild->bColor = BLACK;
}

bool verifyRedNodes(Node_RB* ptrNode) 
{
    if(ptrNode == nullptr) return true;

    // Verifica se um nó vermelho tem, como esperado, filhos pretos
    if(ptrNode->bColor == RED) 
    {
        if ((ptrNode->ptrLeft != nullptr && ptrNode->ptrLeft->bColor == RED) ||
            (ptrNode->ptrRight != nullptr && ptrNode->ptrRight->bColor == RED)) {
            return false;
        }
    }

    // Recursivamente verifica todos os nós vermelhos da árvore
    return verifyRedNodes(ptrNode->ptrLeft) && verifyRedNodes(ptrNode->ptrRight);
}

bool verifyBlackNodes(Node_RB* ptrNode, int iCountBlack, int currentCount) 
{
    if(ptrNode == nullptr) 
    {
        return currentCount == iCountBlack;
    }

    if(ptrNode->bColor == BLACK) 
    {
        currentCount++;
    }

    // Recursivamente verifica todos os nós pretos da árvore
    return verifyBlackNodes(ptrNode->ptrLeft, iCountBlack, currentCount) &&
        verifyBlackNodes(ptrNode->ptrRight, iCountBlack, currentCount);
}

