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
		printf("1:����AVL��  2����ʾ��ǰAVL���Ľṹ 3:����������� 4:���ҽ�� 5�������� 6:ɾ����� 7������AVL��\n");
		printf("������������\n");
		printf("**************************************************************************\n");
		//fflush(stdin);
		scanf("%d", &select); flush();
		switch (select) {
		case 1:
			printf("�����������ݣ���-1����\n");
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
			if (!t1) { printf("������"); break; }
			else {
				printf("��α������У�");
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
				printf("��AVL�������������Ϊ:\n");
				MidOrder(t1);
			}
			else
				printf("������");
			break;
		}
		case 4:
		{
			printf("���Ҳ��������������ؼ���(����)\n");
			KeyType e; AVLTree p;
			scanf("%d", &e);
			p = SearchBST(t1, e);
			if (!p) printf("���ݲ����ڣ�����ʧ�ܣ�\n"); break;
		}
		case 5:
		{
			ElemType* p1 = (ElemType*)malloc(sizeof(ElemType));
			Status s; KeyType k;
			printf("����������������½��Ĺؼ���\n");
			scanf("%d", &k);
			p1->key = k;
			s = InsertAVL(t1, *p1, taller);
			if (s)  printf("����ɹ���");
			else printf("�ý���Ѵ��ڣ�");
			break;
		}
		case 6:
		{
			KeyType e; Status s;
			printf("ɾ�������������ɾ���Ĺؼ��֣�������\n");
			scanf("%d", &e);
			s = Delete(t1, e);
			if (!s) printf("ɾ��ʧ�ܣ�\n");
			break;
		}
		case 7:
		{	DestroyAVL(t1);
			if (t1 == NULL)
			printf("���ٳɹ���\n");
			break;
		}
		default:
			printf("�Ƿ�����\n"); 
			continue;
		}
	}

}