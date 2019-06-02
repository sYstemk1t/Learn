#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int elemType;//�����������ݵ����Ϳ�����int char 

typedef struct NODE{ //��������Ľṹ����
	elemType element;
	struct NODE *next;
}Node;

/************************************************************************/
/*             �����ǹ������Ա����Ӵ洢��������������19���㷨        */

/* 1.��ʼ�����Ա����õ�����ı�ͷָ��Ϊ�� */
/* 2.�������Ա��˺������븺����ֹ��ȡ����*/
/* 3.��ӡ��������ı���*/
/* 4.������Ա�L�е�����Ԫ�أ����ͷŵ�����L�����еĽ�㣬ʹ֮��Ϊһ���ձ� */
/* 5.���ص�����ĳ��� */
/* 6.��鵥�����Ƿ�Ϊ�գ���Ϊ���򷵻أ������򷵻أ� */
/* 7.���ص������е�pos������е�Ԫ�أ���pos������Χ����ֹͣ�������� */
/* 8.�ӵ������в��Ҿ��и���ֵx�ĵ�һ��Ԫ�أ������ҳɹ��򷵻ظý��data��Ĵ洢��ַ�����򷵻�NULL */
/* 9.�ѵ������е�pos������ֵ�޸�Ϊx��ֵ�����޸ĳɹ����أ������򷵻أ� */
/* 10.������ı�ͷ����һ��Ԫ�� */
/* 11.�������ĩβ���һ��Ԫ�� */
/* 12.�������е�pos�����λ�ò���Ԫ��Ϊx�Ľ�㣬������ɹ����أ������򷵻أ� */
/* 13.�����������в���Ԫ��x��㣬ʹ�ò������Ȼ���� */
/* 14.�ӵ�������ɾ����ͷ��㣬���Ѹý���ֵ���أ���ɾ��ʧ����ֹͣ�������� */
/* 15.�ӵ�������ɾ����β��㲢��������ֵ����ɾ��ʧ����ֹͣ�������� */
/* 16.�ӵ�������ɾ����pos����㲢��������ֵ����ɾ��ʧ����ֹͣ�������� */
/* 17.�ӵ�������ɾ��ֵΪx�ĵ�һ����㣬��ɾ���ɹ��򷵻�1,���򷵻�0 */
/* 18.����2��Ԫ�ص�λ�� */
/* 19.�����Ա����ð���� */



/*ע������䵽�Ķ�̬�ڴ��Ƿ�Ϊ��*/




/* 1.��ʼ�����Ա����õ�����ı�ͷָ��Ϊ�� */
void initList(Node **pNode)
{
	*pNode = NULL;
	printf("initList����ִ�У���ʼ���ɹ�\n");
}

/* 2.�������Ա��˺������븺����ֹ��ȡ����*/
Node *creatList(Node *pHead)
{
	Node *p1, *p2;
	p1 = p2 = (Node *)malloc(sizeof(Node));
	if (p1 == NULL || p2 == NULL)
	{
		printf("�ڴ����ʧ��\n");
		exit(0);
	}
	memset(p1, 0, sizeof(Node));

	scanf("%d", &p1->element);
	p1->next = NULL;

	while (p1->element >0)  //�����ֵ����0�����������ֹͣ
	{
		if (pHead == NULL)//�ձ������ͷ
		{
			pHead = p1;
		}
		else
		{
			p2->next = p1;
		}

		p2 = p1;
		p1 = (Node *)malloc(sizeof(Node));

		if (p1 == NULL)
		{
			printf("�ڴ����ʧ��\n");
			exit(0);
		}
		memset(p1, 0, sizeof(Node));
		scanf("%d", &p1->element);
		p1->next = NULL;
	}
	printf("CreatList����ִ�У��������ɹ�\n");
	return pHead;
}

/* 3.��ӡ��������ı���*/
void printList(Node *pHead)
{
	if (NULL == pHead)
	{
		printf("PrintList����ִ�У�����Ϊ��\n");
	}
	else
	{
		while (NULL != pHead)
		{
			printf("%d\n", pHead->element);
			pHead = pHead->next;
		}
	}

}


/* 4.������Ա�L�е�����Ԫ�أ����ͷŵ�����L�����еĽ�㣬ʹ֮��Ϊһ���ձ� */
void clearList(Node *pHead)
{
	Node *pNext;

	if (pHead == NULL)
	{
		printf("clearList����ִ�У�����Ϊ��\n");
		return;
	}
	while (pHead->next != NULL)
	{
		pNext = pHead->next;
		free(pHead);
		pHead = pNext;
	}
	printf("clearList����ִ�У������Ѿ������\n");

}

/* 5.��������ĳ���*/
int sizeList(Node *pHead)
{
	int size = 0;

	while (pHead != NULL)
	{
		size++;
		pHead = pHead->next;
	}
	printf("sizelist����ִ�У�������Ϊ%d\n", size);
	return size;
}

/* 6.��鵥�����Ƿ�Ϊ�գ���Ϊ���򷵻أ������򷵻أ� */
int isEmptyList(Node *pHead)
{
	if (pHead == NULL)
	{
		printf("isEmptylist����ִ�У�����Ϊ�գ�\n");
		return 1;
	}

	else
		printf("isEmptylist����ִ�У�����ǿգ�\n");
	return 0;

}

/* 7.���������е�post�ڵ�����ݣ���post������Χ����ֹͣ��������*/
int getElement(Node *pHead, int pos)
{
	int i = 0;
	if (pos<1)
	{
		printf("getElement����ִ�У�posֵ�Ƿ���");
		return 0;
	}
	if (pHead == NULL)
	{
		printf("getElement����ִ�У�����Ϊ�գ�");
	}

	while (pHead != NULL)
	{
		++i;
		if (i == pos)
		{
			break;
		}
		pHead = pHead->next;
	}
	if (i<pos)
	{
		printf("getElement����ִ�У�posֵ����������\n");
		return 0;
	}
	printf("getElement����ִ�У�λ��%d�е�Ԫ��Ϊ%d\n", pos, pHead->element);

	return 1;
}

//8.�ӵ�һ�����в��Ҿ��и���ֵx�ĵ�һ��Ԫ�أ������ҳɹ��󣬷��ظýڵ�data��Ĵ洢λ�ã����򷵻�NULL
elemType *getElemAddr(Node *pHead, elemType x)
{
	if (NULL == pHead)
	{
		printf("getEleAddr����ִ�У�����Ϊ��");
		return NULL;
	}
	if (x<0)
	{
		printf("getEleAddr����ִ�У�����ֵx���Ϸ�\n");
		return NULL;
	}
	while ((pHead->element != x) && (NULL != pHead->next))//�ж������Ƿ�Ϊ�գ������Ƿ���������ҵ�Ԫ��
	{
		pHead = pHead->next;
	}
	if (pHead->element != x)
	{
		printf("getElemAddr����ִ�У���������û���ҵ�xֵ\n");
		return NULL;
	}
	else
	{
		printf("getElemAddr����ִ�У�Ԫ��%d�ĵ�ַΪ0x%x\n", x, &(pHead->element));
	}
	return &(pHead->element);

}


/*9.�޸������е�pos����X��ֵ������޸ĳɹ����򷵻�1,���򷵻�0*/
int modifyElem(Node *pNode, int pos, elemType x)
{
	Node *pHead;
	pHead = pNode;
	int i = 0;
	if (NULL == pHead)
	{
		printf("modifyElem����ִ�У�����Ϊ��\n");
		return 0;
	}

	if (pos<1)
	{
		printf("modifyElem����ִ�У�posֵ�Ƿ�\n");
		return 0;
	}

	while (pHead != NULL)
	{
		++i;
		if (i == pos)
		{
			break;
		}
		pHead = pHead->next;
	}

	if (i<pos)
	{
		printf("modifyElem����ִ�У�posֵ����������\n");
		return 0;
	}
	pNode = pHead;
	pNode->element = x;
	printf("modifyElem����ִ��,�޸ĵ�%d���Ԫ��Ϊ%d\n", pos, x);

	return 1;

}

/* 10.������ı�ͷ����һ��Ԫ�� */
int insertHeadList(Node **pNode, elemType insertElem)
{
	Node *pInsert;
	pInsert = (Node *)malloc(sizeof(Node));
	if (pInsert == NULL)  exit(1);
	memset(pInsert, 0, sizeof(Node));
	pInsert->element = insertElem;
	pInsert->next = *pNode;
	*pNode = pInsert;
	printf("insertHeadList����ִ�У����ͷ����Ԫ��%d�ɹ�\n", insertElem);
	return 1;
}

/* 11.�������ĩβ���һ��Ԫ�� */
int insertLastList(Node *pNode, elemType insertElem)
{
	Node *pInsert;
	Node *pHead;
	Node *pTmp;

	pHead = pNode;
	pTmp = pHead;
	pInsert = (Node *)malloc(sizeof(Node));
	if (pInsert == NULL)  exit(1);
	memset(pInsert, 0, sizeof(Node));
	pInsert->element = insertElem;
	pInsert->next = NULL;
	while (pHead->next != NULL)
	{
		pHead = pHead->next;
	}
	pHead->next = pInsert;
	printf("insertLastList����ִ�У����β����Ԫ��%d�ɹ�!\n", insertElem);
	return     1;
}

/* 12.�������е�pos�����λ�ò���Ԫ��Ϊx�Ľ�㣬������ɹ����أ������򷵻أ�*/
int isAddPos(Node *pNode, int pos, elemType x)
{
	Node *pHead;
	pHead = pNode;
	Node *pTmp;
	int i = 0;

	if (NULL == pHead)
	{
		printf("AddPos����ִ�У�����Ϊ��\n");
		return 0;
	}

	if (pos<1)
	{
		printf("AddPos����ִ�У�posֵ�Ƿ�\n");
		return 0;
	}

	while (pHead != NULL)
	{
		++i;
		if (i == pos)
			break;
		pHead = pHead->next;
	}

	if (i<pos)
	{
		printf("AddPos����ִ�У�posֵ����������\n");
		return 0;
	}

	pTmp = (Node *)malloc(sizeof(Node));
	if (pTmp == NULL)  exit(1);
	memset(pTmp, 0, sizeof(Node));
	pTmp->next = pHead->next;
	pHead->next = pTmp;
	pTmp->element = x;

	printf("AddPos����ִ�гɹ�����ڵ�%d�������ֵ%d\n", pos, x);
	return 1;
}

/* 13.�����������в���Ԫ��x��㣬ʹ�ò������Ȼ���� */
int OrrderList(Node *pNode, elemType x)
{
	//ע���������ֵҪ�ŵ���βҪ�޸ı�����
	Node *pHead;
	pHead = pNode;
	Node *pTmp;

	if (NULL == pHead)
	{
		printf("OrrderList����ִ�У�����Ϊ��\n");
		return 0;
	}

	if (x<1)
	{
		printf("OrrderList����ִ�У�xֵ�Ƿ�\n");
		return 0;
	}

	while (pHead != NULL)
	{
		if ((pHead->element) >= x)
			break;
		pHead = pHead->next;
	}


	if (pHead == NULL)
	{
		printf("OrrderList����������ϣ��ú�����û�и�ֵ\n");
		return 0;
	}


	pTmp = (Node *)malloc(sizeof(Node));
	if (pTmp == NULL)  exit(1);
	memset(pTmp, 0, sizeof(Node));
	pTmp->next = pHead->next;
	pHead->next = pTmp;
	pTmp->element = x;

	printf("OrrderList�����ɹ�������ֵ%d\n", x);
	return 1;
}

/*14.�ӵ�������ɾ����ͷ��㣬���Ѹý���ֵ���أ���ɾ��ʧ����ֹͣ��������*/
int DelHeadList(Node **pList)
{
	Node *pHead;
	pHead = *pList;
	if (pHead != NULL)
		printf("DelHeadList����ִ��,������Ԫ��Ϊ%dɾ���ɹ�\n", pHead->element);
	else
	{
		printf("DelHeadList����ִ��,����Ϊ��!");
		return 0;
	}
	*pList = pHead->next;
	return 1;
}

/* 15.�ӵ�������ɾ����β��㲢��������ֵ����ɾ��ʧ����ֹͣ�������� */
int DelLastList(Node *pNode)
{
	Node *pHead;
	Node *pTmp;

	pHead = pNode;
	while (pHead->next != NULL)
	{
		pTmp = pHead;
		pHead = pHead->next;
	}
	printf("����βɾ��Ԫ��%d�ɹ�!\n", pHead->element);
	free(pHead);
	pTmp->next = NULL;
	return     1;
}

/* 16.�ӵ�������ɾ����pos����㲢��������ֵ����ɾ��ʧ����ֹͣ�������� */
int DelPos(Node *pNode, int pos)
{
	Node *pHead;
	pHead = pNode;
	Node *pTmp;

	int i = 0;

	if (NULL == pHead)
	{
		printf("DelPos����ִ�У�����Ϊ��\n");
		return 0;
	}

	if (pos<1)
	{
		printf("DelPos����ִ�У�posֵ�Ƿ�\n");
		return 0;
	}

	while (pHead != NULL)
	{
		++i;
		if (i == pos)
			break;
		pTmp = pHead;
		pHead = pHead->next;
	}

	if (i<pos)
	{
		printf("DelPos����ִ�У�posֵ����������\n");
		return 0;
	}
	printf("DelPos����ִ�гɹ����ڵ�%dɾ����ֵ%d\n", pos, pHead->element);
	pTmp->next = pHead->next;
	free(pHead);
	return 1;
}

/* 17.�ӵ�������ɾ��ֵΪx�ĵ�һ����㣬��ɾ���ɹ��򷵻�1,���򷵻�0 */
int Delx(Node **pNode, int x)
{
	Node *pHead;
	Node *pTmp;
	pHead = *pNode;
	int i = 0;

	if (NULL == pHead)
	{
		printf("Delx����ִ�У�����Ϊ��");
		return 0;
	}
	if (x<0)
	{
		printf("Delx����ִ�У�����ֵx���Ϸ�\n");
		return 0;
	}
	while ((pHead->element != x) && (NULL != pHead->next))//�ж������Ƿ�Ϊ�գ������Ƿ���������ҵ�Ԫ��
	{
		++i;
		pTmp = pHead;
		pHead = pHead->next;
	}
	if (pHead->element != x)
	{
		printf("Delx����ִ�У���������û���ҵ�xֵ\n");
		return 0;
	}
	if ((i == 0) && (NULL != pHead->next))
	{
		printf("Delx����ִ�У��������ײ��ҵ���Ԫ��,��Ԫ���Ѿ���ɾ��\n");
		*pNode = pHead->next;
		free(pHead);
		return 1;
	}
	printf("Delx����ִ�У��׸�Ϊ%dԪ�ر�ɾ��\n", x);
	pTmp->next = pHead->next;
	free(pHead);
	return 1;
}

/* 18.����2��Ԫ�ص�λ�� */
int exchange2pos(Node *pNode, int pos1, int pos2)
{
	Node *pHead;
	int *pTmp;
	int *pInsert;
	int a;
	int i = 0;

	if (pos1<1 || pos2<1)
	{
		printf("DelPos����ִ�У�posֵ�Ƿ�\n");
		return 0;
	}

	pHead = pNode;
	while (pHead != NULL)
	{
		++i;
		if (i == pos1)
			break;
		pHead = pHead->next;
	}

	if (i<pos1)
	{
		printf("DelPos����ִ�У�pos1ֵ����������\n");
		return 0;
	}

	pTmp = &(pHead->element);
	i = 0;
	pHead = pNode;
	while (pHead != NULL)
	{
		++i;
		if (i == pos2)
			break;
		pHead = pHead->next;
	}

	if (i<pos2)
	{
		printf("DelPos����ִ�У�pos2ֵ����������\n");
		return 0;
	}

	pInsert = &(pHead->element);
	a = *pTmp;
	*pTmp = *pInsert;
	*pInsert = a;

	printf("DelPos����ִ��,������%d���͵�%d��pos���ֵ\n", pos1, pos2);
	return 1;
}

int swap(int *p1, int *p2)
{
	int a;
	if (*p1>*p2)
	{
		a = *p1;
		*p1 = *p2;
		*p2 = a;
	}
	return 0;
}

/* 19.�����Ա����ð������ */
int Arrange(Node *pNode)
{
	Node *pHead;
	pHead = pNode;

	int a = 0, i, j;

	if (NULL == pHead)
	{
		printf("Arrange����ִ�У�����Ϊ��\n");
		return 0;
	}

	while (pHead != NULL)
	{
		++a;
		pHead = pHead->next;
	}

	pHead = pNode;
	for (i = 0; i<a - 1; i++)
	{
		for (j = 1; j<a - i; j++)
		{
			swap(&(pHead->element), &(pHead->next->element));
			pHead = pHead->next;
		}
		pHead = pNode;
	}
	printf("Arrange����ִ�У������������!\n");
	return 0;
}

int main()
{
	Node *pList = NULL;
	int length = 0;

	elemType posElem;

	initList(&pList);
	printList(pList);

	pList = creatList(pList);
	printList(pList);

	sizeList(pList);
	printList(pList);

	isEmptyList(pList);


	posElem = getElement(pList, 3);
	printList(pList);

	getElemAddr(pList, 5);

	modifyElem(pList, 4, 1);
	printList(pList);

	insertHeadList(&pList, 5);
	printList(pList);

	insertLastList(pList, 10);
	printList(pList);

	isAddPos(pList, 4, 5);
	printList(pList);

	OrrderList(pList, 6);
	printList(pList);

	DelHeadList(&pList);
	printList(pList);

	DelLastList(pList);
	printList(pList);

	DelPos(pList, 5);
	printList(pList);

	Delx(&pList, 5);
	printList(pList);

	exchange2pos(pList, 2, 5);
	printList(pList);

	Arrange(pList);
	printList(pList);

	clearList(pList);
	return 0;
}