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
