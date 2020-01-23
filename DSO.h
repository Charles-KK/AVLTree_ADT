#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1

#define EH 0
#define LH 1
#define RH -1
typedef int Status;

typedef int KeyType;
typedef int Infor;

typedef struct {
	KeyType key;
	Infor  other;
}ElemType;

typedef struct AVLTNode {
	ElemType data;
	int bf;
	struct AVLTNode* lchild, * rchild;
}*AVLTree; //AVL Tree Type

typedef struct arr {
	int* thelast;
	int max;
	int n;
}*array;
/*LQueue define*/
typedef struct LQNode{
	AVLTNode* data;
	struct LQNode* next;
}LQNode;
typedef struct {
	LQNode *front;
	LQNode *rear;
}LQ;
Status InitQueue(LQ &q);
Status EnQueue(LQ &q, AVLTree e);
Status DeQueue(LQ & q, AVLTree &e);
Status QueueEmpty(LQ q);
/************************************/
array append(array a, int last);
array getArray();
array pop(array a);
Status InitAVLTree(AVLTree& T);
void R_Rotate(AVLTree& p);
void L_Rotate(AVLTree& p);
void LBalance(AVLTree& T);
void RBalance(AVLTree& T);
Status InsertAVL(AVLTree& T, ElemType e, Status& taller);
AVLTree SearchBST(AVLTree T, KeyType key);
Status Delete(AVLTree& T, KeyType key);
int Depth(AVLTree T);
void DeleteNode(AVLTree& p);
void MidOrder(AVLTree T);
void Leveltraversal(AVLTree T);
void DestroyAVL(AVLTree &T);
void printTree(AVLTree T);
void printAtree(AVLTree t, int n);
void flush();