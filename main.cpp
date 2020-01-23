#include"DSO.h"

int main() {
	AVLTree t1;
	int temp = 0;
	int taller = 1;
	InitAVLTree(t1);
	int select = 0;
	int depth = Depth(t1);
	while (1) {
		//menue
		printf("**************************************************************************\n");
		printf("1:创建AVL树  2：显示当前AVL树的结构 3:中序遍历序列 4:查找结点 5：插入结点 6:删除结点 7：销毁AVL树\n");
		printf("请输入操作序号\n");
		printf("**************************************************************************\n");
		//fflush(stdin);
		scanf("%d", &select); flush();
		switch (select) {
		case 1:
			printf("请输入结点数据，以-1结束\n");
			int c;
			DestroyAVL(t1);
			c = scanf("%d", &temp);
			while (temp!=-1) {
				if (!c) {
					flush();
					c = scanf("%d", &temp);
					continue;
				}
				ElemType* p = (ElemType*)malloc(sizeof(ElemType));
				if (p)
				{
					p->key = temp;
					InsertAVL(t1, *p, taller);
				}
				c = scanf("%d", &temp);

			}//enter key loop
			break;
		case 2:
		{
			if (!t1) { printf("空树！"); break; }
			else {
				printf("层次遍历序列：");
				Leveltraversal(t1); printf("\n"); printf("\n");
				depth = Depth(t1);
				printAtree(t1, depth);
				printf("\n");
				/*printTree(t1);*/
				break;
			}
		}

		case 3:
		{
			if (t1)
			{
				printf("此AVL树中序遍历序列为:\n");
				MidOrder(t1);
			}
			else
				printf("空树！");
			break;
		}
		case 4:
		{
			printf("查找操作：请输入待查关键字(整数)\n");
			KeyType e; AVLTree p;
			scanf("%d", &e);
			p = SearchBST(t1, e);
			if (!p) printf("数据不存在，查找失败！\n"); break;
		}
		case 5:
		{
			ElemType* p1 = (ElemType*)malloc(sizeof(ElemType));
			Status s; KeyType k;
			printf("插入操作：请输入新结点的关键字\n");
			scanf("%d", &k);
			p1->key = k;
			s = InsertAVL(t1, *p1, taller);
			if (s)  printf("插入成功！");
			else printf("该结点已存在！");
			break;
		}
		case 6:
		{
			KeyType e; Status s;
			printf("删除操作：输入待删结点的关键字（整数）\n");
			scanf("%d", &e);
			s = Delete(t1, e);
			if (!s) printf("删除失败！\n");
			break;
		}
		case 7:
		{	DestroyAVL(t1);
			if (t1 == NULL)
			printf("销毁成功！\n");
			break;
		}
		default:
			printf("非法输入\n"); 
			continue;
		}
	}

}