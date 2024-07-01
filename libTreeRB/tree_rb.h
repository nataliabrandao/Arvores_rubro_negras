#ifndef _TREE_RB_H
#define _TREE_RB_H

// Inclusão de bibliotecas e namespaces
#include <iostream>
using std::cout;
using std::endl;
using std::max;
using std::string;
using std::cerr;

// Definição de cores para a impressão da árvore
const std::string red("\033[0;31m");
const std::string reset("\033[0m");

// Enumeração para as cores dos nós
typedef enum {BLACK, RED} Color;

// Estrutura de um nó da árvore
typedef struct Node_RB {
    Node_RB* ptrParent = nullptr;
    Node_RB* ptrLeft = nullptr; 
    Node_RB* ptrRight = nullptr;

    int iValue;
    bool bColor;
} Node_RB;

// Estrutura da árvore
typedef struct Tree_RB
{
    Node_RB* ptrRoot = nullptr;
} Tree_RB;

// Declaração de funções requisitadas
void insert(Tree_RB*, int);
void inorder(Node_RB*);

// Declaração de funções auxiliares
Tree_RB* createTree();
Node_RB* createNode(int);
Node_RB* createNode(int, Color);
void insertFixup(Tree_RB*, Node_RB*);
Node_RB* rotateLeft(Tree_RB* ptrTree, Node_RB* ptrNode);
Node_RB* rotateRight(Tree_RB* ptrTree, Node_RB* ptrNode);
void printTreeRB(string, Node_RB*, bool);
void printTreeRB(Node_RB*); // Sobrecarga de função 

#endif // _TREE_RB_H