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

SinglyLinkedList* sllist_create()	//创建新的链表节点
{
    SinglyLinkedList *pList = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));	//开辟一块内存空间，大小为SinglyLinkedList这个结构体这么大
    check_address(pList);	//内存检查
    pList->m_head = (Node*)malloc(sizeof(Node));	//开辟内存空间，用以存放数据
    pList->m_head->m_data = 0;	//对链表的第一个元素进行赋值
    pList->m_head->m_next = NULL;	//指向链表下一个节点为空
    pList->m_count = 0;	//
    return pList;
}

void sllist_destroy(SinglyLinkedList *pList)	//清空链表
{
    Node *head, *curr;	//以结构体定义两个两个指针
    int index;	//下标

    check_address(pList);	//内存检查
    head = pList->m_head;	//头节点等于传入数据的头
    for(index=0;index<pList->m_count;++index)	
    {
        curr = head->m_next;
        head->m_next = curr->m_next;
        free(curr);
    }
    free(pList->m_head);
    free(pList);	//释放内存，也释放了这个链表节点的数据
}

int sllist_size(SinglyLinkedList *pList)	//计算长度
{	
    check_address(pList);
    return pList->m_count;
}

int sllist_is_empty(SinglyLinkedList *pList)		//返回链表是否为空
{	
    check_address(pList);
    return pList->m_count == 0;
}

void sllist_push_front(SinglyLinkedList *pList, int value)		//value是数据值
{
    Node *pNode;	//结构体指针
		
    check_address(pList);	//检查空指针
    pNode = (Node*)malloc(sizeof(Node));	//开辟内存空间
    pNode->m_data = value;	//data等于函数传递进来的值
    pNode->m_next = pList->m_head->m_next;	//如果直接指向，会打断原来的链表，然后就会出现找不到下一个
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

int sllist_back(SinglyLinkedList *pList)	//返回链表的尾节点
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

int sllist_at(SinglyLinkedList *pList, int index)	//返回参数传递值的下标的数据
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

void sllist_erase(SinglyLinkedList *pList, int index)	//删除某个节点
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
    prev->m_next = curr->m_next;		//链表被删除后，上一个节点和下一个节点建立连接
    free(curr);
    pList->m_count--;
}

int sllist_search(SinglyLinkedList *pList, int value)
{
    int index = 0;	//下标为0
    Node *curr;

    check_address(pList);
    curr = pList->m_head;	//链表的头
    while(curr->m_next)		
    {
        curr = curr->m_next;	//curr是第一个元素的尾部
        index++;	//下标加加
        if(curr->m_data == value)	//判断下标是否和数据相等，如果不相等，等于-1
            return index;
    }
    return -1;
}

void sllist_update(SinglyLinkedList *pList, int index, int value)	//在制定的位置插入元素值
{
    Node *curr;		
    int i;

    check_address(pList);		//内存检查
    if(pList->m_count <= index)	
    {
        printf("Out of range.\n");
        return ;
    }

    curr = pList->m_head;
    for(i=0;i<=index;++i)
    {
        curr = curr->m_next;	//指向下一个节点
    }
    curr->m_data = value;	//函数的传入值进行赋值
}

void sllist_print(SinglyLinkedList *pList)	//打印链表内的内容
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