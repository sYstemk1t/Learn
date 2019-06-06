#include "SinglyLinkedList.h"
#include <stdlib.h>
#include <stdio.h>

static void check_address(void *p) 
{
    if (p == NULL) 
    {
        printf("Invalid address.\n");
        exit(-1);
    }
}

SinglyLinkedList* sllist_create()	//�����µ�����ڵ�
{
    SinglyLinkedList *pList = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));	//����һ���ڴ�ռ䣬��СΪSinglyLinkedList����ṹ����ô��
    check_address(pList);	//�ڴ���
    pList->m_head = (Node*)malloc(sizeof(Node));	//�����ڴ�ռ䣬���Դ������
    pList->m_head->m_data = 0;	//������ĵ�һ��Ԫ�ؽ��и�ֵ
    pList->m_head->m_next = NULL;	//ָ��������һ���ڵ�Ϊ��
    pList->m_count = 0;	//
    return pList;
}

void sllist_destroy(SinglyLinkedList *pList)	//�������
{
    Node *head, *curr;	//�Խṹ�嶨����������ָ��
    int index;	//�±�

    check_address(pList);	//�ڴ���
    head = pList->m_head;	//ͷ�ڵ���ڴ������ݵ�ͷ
    for(index=0;index<pList->m_count;++index)	
    {
        curr = head->m_next;
        head->m_next = curr->m_next;
        free(curr);
    }
    free(pList->m_head);
    free(pList);	//�ͷ��ڴ棬Ҳ�ͷ����������ڵ������
}

int sllist_size(SinglyLinkedList *pList)	//���㳤��
{	
    check_address(pList);
    return pList->m_count;
}

int sllist_is_empty(SinglyLinkedList *pList)		//���������Ƿ�Ϊ��
{	
    check_address(pList);
    return pList->m_count == 0;
}

void sllist_push_front(SinglyLinkedList *pList, int value)		//value������ֵ
{
    Node *pNode;	//�ṹ��ָ��
		
    check_address(pList);	//����ָ��
    pNode = (Node*)malloc(sizeof(Node));	//�����ڴ�ռ�
    pNode->m_data = value;	//data���ں������ݽ�����ֵ
    pNode->m_next = pList->m_head->m_next;	//���ֱ��ָ�򣬻���ԭ��������Ȼ��ͻ�����Ҳ�����һ��
    pList->m_head->m_next = pNode;
    pList->m_count++;
}

int sllist_pop_front(SinglyLinkedList *pList)
{
    Node *pNode;
    int data;

    if(sllist_is_empty(pList))
    {
        printf("LinkedList is empty.\n");
        return -1;
    }
    pNode = pList->m_head->m_next;
    pList->m_head->m_next = pNode->m_next;
    pList->m_count--;
    data = pNode->m_data;
    free(pNode);
    return data;
}

void sllist_push_back(SinglyLinkedList *pList, int value)
{
    Node *pNode;
    Node *curr;

    check_address(pList);
    pNode = (Node*)malloc(sizeof(Node));
    pNode->m_next = NULL;
    pNode->m_data = value;

    curr = pList->m_head;
    while(curr->m_next)
    {
        curr = curr->m_next;
    }
    curr->m_next = pNode;
    pList->m_count++;
}

int sllist_pop_back(SinglyLinkedList *pList)
{
    int data;
    Node *prev, *curr;

    if(sllist_is_empty(pList))
    {
        printf("LinkedList is empty.\n");
        return -1;
    }
    prev = pList->m_head;
    curr = pList->m_head->m_next;
    while(curr->m_next)
    {
        prev = curr;
        curr = curr->m_next;
    }

    data = curr->m_data;
    prev->m_next = NULL;
    pList->m_count--;
    free(curr);
    return data;
}

int sllist_front(SinglyLinkedList *pList)
{
    if(sllist_is_empty(pList))
    {
        printf("LinkedList is empty.\n");
        return -1;
    }

    return pList->m_head->m_next->m_data;
}

int sllist_back(SinglyLinkedList *pList)	//���������β�ڵ�
{
    Node *curr;

    if(sllist_is_empty(pList))
    {
        printf("LinkedList is empty.\n");
        return -1;
    }

    curr = pList->m_head;
    while(curr->m_next)
    {
        curr = curr->m_next;
    }    
    return curr->m_data;
}

int sllist_at(SinglyLinkedList *pList, int index)	//���ز�������ֵ���±������
{
    int i = 0;
    Node *curr;

    if(sllist_is_empty(pList) || pList->m_count <= index)
    {
        printf("Out of range.\n");
        return -1;
    }

    curr = pList->m_head;
    for(i=0;i<=index;++i)
    {
        curr = curr->m_next;
    }
    return curr->m_data;
}

void sllist_insert(SinglyLinkedList *pList, int index, int value)
{
    Node *pNode, *curr;
    int i;

    check_address(pList);
    if(pList->m_count < index)
    {
        printf("Out of range.\n");
        return ;
    }

    pNode = (Node*)malloc(sizeof(Node));
    pNode->m_data = value;
    
    curr = pList->m_head;
    for(i=0;i<index;++i)
    {
        curr = curr->m_next;
    }
    pNode->m_next = curr->m_next;
    curr->m_next = pNode;
    pList->m_count++;
}

void sllist_erase(SinglyLinkedList *pList, int index)	//ɾ��ĳ���ڵ�
{
    Node *curr, *prev = NULL;
    int i;

    check_address(pList);
    if(pList->m_count <= index)
    {
        printf("Out of range.\n");
        return ;
    }

    curr = pList->m_head;
    for(i=0;i<=index;++i)
    {
        prev = curr;
        curr = curr->m_next;
    }    
    prev->m_next = curr->m_next;		//����ɾ������һ���ڵ����һ���ڵ㽨������
    free(curr);
    pList->m_count--;
}

int sllist_search(SinglyLinkedList *pList, int value)
{
    int index = 0;	//�±�Ϊ0
    Node *curr;

    check_address(pList);
    curr = pList->m_head;	//�����ͷ
    while(curr->m_next)		
    {
        curr = curr->m_next;	//curr�ǵ�һ��Ԫ�ص�β��
        index++;	//�±�Ӽ�
        if(curr->m_data == value)	//�ж��±��Ƿ��������ȣ��������ȣ�����-1
            return index;
    }
    return -1;
}

void sllist_update(SinglyLinkedList *pList, int index, int value)	//���ƶ���λ�ò���Ԫ��ֵ
{
    Node *curr;		
    int i;

    check_address(pList);		//�ڴ���
    if(pList->m_count <= index)	
    {
        printf("Out of range.\n");
        return ;
    }

    curr = pList->m_head;
    for(i=0;i<=index;++i)
    {
        curr = curr->m_next;	//ָ����һ���ڵ�
    }
    curr->m_data = value;	//�����Ĵ���ֵ���и�ֵ
}

void sllist_print(SinglyLinkedList *pList)	//��ӡ�����ڵ�����
{
    Node *curr;
    int index = 0;

    check_address(pList);
    curr = pList->m_head;
    while(curr->m_next)
    {
        curr = curr->m_next;
        printf("Node index[%d]\tdata[%d]\n", index, curr->m_data);
        ++index;
    }
}