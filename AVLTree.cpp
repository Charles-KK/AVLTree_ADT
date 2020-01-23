#include"DSO.h"
#include <stdlib.h>
void print(AVLTree t, int depth, array last);
/// 1
Status InitAVLTree(AVLTree &T){
	T = NULL;
	return OK;
}

/// 2
void R_Rotate(AVLTree &p) {

	AVLTree lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;

}
/// 3
void L_Rotate(AVLTree &p) {

	AVLTree rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
}
/// 4
void LBalance(AVLTree& T) {
	AVLTree lc, lrc;
	lc = T->lchild;
	switch (lc->bf)
	{
	//LL Type --->  R_Rotate root
	case LH:
		T->bf = lc->bf = EH;
		R_Rotate(T); break;

	//LR Type ---> double rotate, lc will be new root
	case RH:
		lrc = lc->rchild;
		switch (lrc->bf) {
		case LH:
			//lc get lrc's lchild
			T->bf = RH; lc->bf = EH; break;   //lc is new root now
		case RH:
			//lc not get rlc's lchild so LC->BF will be LH
			T->bf = EH; lc->bf = LH; break;
		case EH:
			T->bf = EH; lc->bf = EH; break;
		}
	//lrc become lc->lchild
		lrc->bf = EH;
	L_Rotate(T->lchild);
	R_Rotate(T);
	break;
	//default:break;
	}
	
}
/// 5
void RBalance(AVLTree& T) {
	AVLTree rc = T->rchild, rlc;
	switch (rc->bf) {
	//RR Type   -->L_Rotate  root
	case RH:
		T->bf = rc->bf = EH; L_Rotate(T); break;
	//RL 
	case LH:
		rlc = rc->lchild;
		switch (rlc->bf) {
		case LH:
			T->bf = EH; rc->bf = RH; break;
		case RH:
			T->bf = LH; rc->bf = EH; break;
		case EH:
			T->bf = EH; rc->bf = EH; break;
		}
		rlc->bf = EH;
		R_Rotate(T->rchild); L_Rotate(T); break;
		//default: break;
	}

}
/// 6
Status InsertAVL(AVLTree& T, ElemType e, Status &taller) {
	if (T==NULL) {
		T = (AVLTree)malloc(sizeof(AVLTNode));
		if (T) {
			T->bf = EH; T->lchild = NULL; T->rchild = NULL;
			T->data = e;
			taller = TRUE;
		}
		else return OVERFLOW;
	}
	//因结点已存在，插入失败
	else if (e.key == T->data.key) {
		taller = FALSE; return FALSE;
	}
	//small ,insert into left branch
	else if (e.key < T->data.key) {
		if (FALSE == InsertAVL(T->lchild, e, taller)) return FALSE;
		if (TRUE == taller) {
			switch (T->bf) {
			case LH://需做左平衡处理
				LBalance(T); taller = FALSE; break;
			case EH:
				T->bf = LH; taller = TRUE; break;
			case RH:
				T->bf = EH; taller = FALSE; break;
			}
		}
	}
	//big ,insert into right branch
	else {
		if (FALSE == InsertAVL(T->rchild, e, taller)) return FALSE;
		if (taller == TRUE) {
			switch (T->bf) {
			case LH:
				T->bf = EH; taller = FALSE; break;
			case EH:
				T->bf = RH; taller = TRUE; break;
			case RH:
				RBalance(T); taller = FALSE; break;
			}
		}
	}
	return TRUE;
}
/// 7
AVLTree SearchBST(AVLTree T, KeyType key) {
	while (T) {
		if (T->data.key == key)
		{
			printf("查找成功！结点信息(node[bf])为：%d[%d]\n",T->data.key,T->bf);
			return T;
		}
		else if (T->data.key > key)
			T = T->lchild;
		else T = T->rchild;
	}
	return T;
	//if (!T) return NULL;
	//if (T->data.key == key) return T;
	//if (T->data.key > key)
	//	return SearchBST(T->lchild, key);
	//return SearchBST(T->rchild, key);
}
/// 8
Status Delete(AVLTree &T,KeyType key){
	if (!T) return FALSE;
	if (key == T->data.key) {
		DeleteNode(T);
		printf("删除成功!\n");
		return TRUE;
	}
	else if (key < T->data.key) 
		return Delete(T->lchild,key);
	return Delete(T->rchild, key);
}
/// 9
void DeleteNode(AVLTree &p) {
	AVLTNode* q, * s;
	q = p;
	if (!p->lchild) {
		p = p->rchild;
		free(q);
	}
	else if (!p->rchild) {
		p = p->lchild;
		free(q);
	}
	else if (!p->lchild)
	{
		p = p->rchild;
	}//左右子树均为空已包含在上述两种条件内
	//左右子树均不为空
	else
	{
		s = p->lchild;
		while (s->rchild) { //向右走到尽头，最右的结点是p的直接前驱,用s指向它
			q = s;
			s = s->rchild; // move pointer s
		}
		p->data = s->data;
		if (p == q) { //s是被删结点左孩子
			q->lchild = s->lchild;
		}
		else q->rchild = s->lchild;
		free(s);
	}
}
/// 10
//void printTree(AVLTree t) {
//	if (t == NULL)
//		return;
//	array last = getArray();
//	print(t, 1, last);
//}

/// 11
void DestroyAVL(AVLTree&T) {
	if (T) {
		if (T->lchild) {
			DestroyAVL(T->lchild);
		}
		if (T->rchild) {
			DestroyAVL(T->rchild);
		}
		free(T);
		T = NULL;
	}
}

/// 12
void MidOrder(AVLTree T) {
	if (T == NULL)
		return;
	MidOrder(T->lchild);
	printf("%d\n",T->data.key);
	MidOrder(T->rchild);
}
void Leveltraversal(AVLTree T) {
	if (T!=NULL) {
		LQ q; InitQueue(q); AVLTNode *p = T;
			printf("%d ", p->data.key); EnQueue(q, p);
			while (DeQueue(q, p)) {
				if (p->lchild) {
					printf("%d ", p->lchild->data.key);
					EnQueue(q, p->lchild);
				}
				if (p->rchild) {
					printf("%d ", p->rchild->data.key);
					EnQueue(q, p->rchild);
				}
			}
		
	}
}
int Depth(AVLTree T) {
	int d1 = 0, d2 = 0;
	if (!T) return 0;
	else {
		d1 = Depth(T->lchild);
		d2 = Depth(T->rchild);
		return 1 + (d1 > d2 ? d1 : d2);
	}
}
//array append(array a, int last) {
//	if (a->n == a->max)
//		a->thelast = (int*)realloc(a->thelast, sizeof(int) * ((a->max) + 10));
//	if (a->thelast)
//	{
//		a->max += 10;
//		a->thelast[(a->n)++] = last;
//	}
//	return a;
//}
//array pop(array a) {
//	if (a == NULL || a->n == 0)
//		return a;
//	a->n -= 1;
//	return a;
//}

//void print(AVLTree t, int depth, array last) {
//	int i, j;
//	if (t == NULL)
//		return;
//	
//	printf("|\n");
//	
//			for (j = 0; j < depth - 1; j++) {
//				
//				if (!(last->thelast[j]))
//					printf("|");
//				else
//					printf(" ");
//				printf("\t");
//				 }
//		
//			printf("|->");
//			printf("%d\n", t->data.key);
//		
//			if (t->lchild) {
//				for (j = 0; j < depth - 1; j++) {
//					//if(i!=1){
//					if (!(last->thelast[j]))
//						printf("|");
//					else
//						printf(" ");
//					printf("\t");
//					//}
//				}
//				printf("|------>");
//				
//				append(last, 0);
//				print(t->lchild, depth + 1, last);
//				pop(last);
//			}
//			if (t->rchild) {
//				for (j = 0; j < depth - 1; j++) {
//					
//					if (!(last->thelast[j]))
//						printf("|");
//					else
//						printf(" ");
//					printf("\t");
//					
//				}
//				printf("|------>");
//				
//				append(last, 1);
//				
//				print(t->rchild, depth + 1, last);
//				pop(last);
//			}
//}
//array getArray() {
//	array a = (array)malloc(sizeof(struct arr));
//	if (a)
//	{
//		a->max = 10;
//		a->n = 0;
//		a->thelast = (int*)malloc(sizeof(int) * (a->max));
//	}
//	return a;
//}

Status InitQueue(LQ& q) {
	q.front = (LQNode*)malloc(sizeof(LQNode));
	if (q.front == NULL) return OVERFLOW;
	q.front = q.rear = NULL;
	return OK;
}
Status EnQueue(LQ&q , AVLTree e) {
	LQNode* p;
	p = (LQNode*)malloc(sizeof(LQNode));
	if (p == NULL) return OVERFLOW;
	p->data = e; p->next = NULL;
	//若插入的是空队列
	if (q.rear == NULL) q.front = p;
	else  q.rear->next = p;
	
	q.rear = p;
	return OK;

}
Status DeQueue(LQ &q, AVLTree &e) {
	LQNode* p;
	if (q.front == NULL) return ERROR;
	p = q.front; e = p->data; q.front = p->next; 
	if (q.rear == p) q.rear = NULL;
	free(p);
	return OK;
}
Status QueueEmpty(LQ q) {
	if (q.rear == NULL) return TRUE;  //or q.front==q.rear
	return FALSE;
}
void printAtree(AVLTree T, int depth) //二叉树的显示输出
{
	//竖向输出二叉树
	int i, j; int w; LQ q;
	AVLTree p=T;
	/*ElemType node;*/
	InitQueue(q);
	if(T) EnQueue(q,p);
	for (j = 0; j < depth; j++)
	{
		int w = 1 << (depth - j + 1);//设置结点的位置
		for (i = 0; i < 1 << j; i++) //第j层有2^j个结点
	    {
			DeQueue(q, p);
			if (p) {
				printf("%*d%*c", w, p->data.key, w, ' ');
				EnQueue(q,p->lchild);
				EnQueue(q, p->rchild);
			}
			else {
				printf("%*c%*c", w, ' ', w, ' ');
				EnQueue(q, NULL);
				EnQueue(q, NULL);
			}
		}
		printf("\n");
	}
	
	//凹入表
	//if (T) {
	//	printBlank(i); printf("%d\n", T->data.key);
	//}
	//else {
	//	printBlank(i); printf("NULL\n"); return;
	//}
	//printAtree(T->lchild, i + 5);
	//printAtree(T->rchild, i + 5);
}

void flush() {//清除缓冲区
	
	/*int c; scanf("%[^0-9]",&c);*/ //捕获非数字的到c
	int c;
	while ((c = getchar()) != '\n' && c != EOF); //   '\n'->10
}

