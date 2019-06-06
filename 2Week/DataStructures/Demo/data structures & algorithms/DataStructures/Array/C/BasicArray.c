#include "BasicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ArrayOps g_basic_array_handler = 
{
    basic_array_new, 
    basic_array_destroy,
    basic_array_size,
    basic_array_capacity,
    basic_array_is_empty,
    basic_array_push,
    basic_array_pop,
    basic_array_back,
    basic_array_at,
    basic_array_insert,
    basic_array_delete,
    basic_array_find
};

static void reserve(Array *, int);
static void check_address(void *);

Array* basic_array_new(int capacity)	//添加一个新的节点
{
    Array *pArr = NULL;		//定义一个指针，*pArr等于空值
    if(capacity < 0)	//如果capacity小于0的话，直接return掉，因为节点的开始就是0,结构体中的三个变量都是int型
        return NULL;
    pArr = (Array*)malloc(sizeof(Array));	//计算结构体Array的大小并且申请内存空间
    check_address(pArr);	//判断pArr申请内存空间是否成功

    pArr->m_size = capacity;	//给变量m_size赋值
    pArr->m_capacity = capacity;	//给变量m_capacity赋值
    if(capacity == 0)	//如果m_capacity赋值成功，但是赋值为0
    {
        pArr->m_start = NULL;	//将m_start赋值为空值
    }
    else
    {
        pArr->m_start = (int *)malloc(sizeof(int) * capacity);	//为m_start开辟一块内存空间。
        check_address(pArr->m_start);	//检查内存是否开辟成功
        memset(pArr->m_start, 0, sizeof(int) * capacity);	//将m_start里的值，全部置为0
    }
    pArr->m_handler = &g_basic_array_handler;	//结束的时候等于下一次开始，因为g_basic_array_handler封装了所有函数
    return pArr;
}

void basic_array_destroy(Array *pArr)	//清空整个链表
{
    if(pArr)
    {
		for (int i = 0; i < pArr->m_capacity; ++i)
		{
			free(pArr->m_start[i]);		//如果capacity小于u，把i值全部释放
		}
        free(pArr);
    }
}

int basic_array_size(Array *pArr)
{
    if(pArr)	//判断是否为真，为真则return
        return pArr->m_size;
}

int basic_array_capacity(Array *pArr)
{
    if(pArr)
        return pArr->m_capacity;
}

int basic_array_is_empty(Array *pArr)
{
    return pArr->m_size == 0;
}

void basic_array_push(Array *pArr, int elem)
{
    if(pArr == NULL)
        return ;
    if(pArr->m_size == pArr->m_capacity)
    {
        if(pArr->m_capacity == 0)	
            reserve(pArr, 1);	//如果当前的空间为0，则把当前控制的值修改为1
        else
            reserve(pArr, pArr->m_capacity * 2);
    }		//如果空间不够，对空间进行扩容
    pArr->m_start[pArr->m_size] = elem;
    ++pArr->m_size;
}

void basic_array_pop(Array *pArr)
{
    if(pArr == NULL)
        return ;
    --pArr->m_size;
    if(pArr->m_size != 0 && pArr->m_size * 2 <= pArr->m_capacity)
    {
        reserve(pArr, pArr->m_capacity / 2);
    }	//如果空间不需要那么大，就把这部分空间释放
}

int basic_array_back(Array *pArr)
{
    if(pArr == NULL || pArr->m_size == 0)
        return -1;
    return pArr->m_start[pArr->m_size - 1];
}

int basic_array_at(Array *pArr, int idx)
{
    if(pArr == NULL || pArr->m_size <= idx)
        return -1;
    return pArr->m_start[idx];
}

void basic_array_insert(Array *pArr, int idx, int elem)	//在某个域上插入数据
{
    int i = 0;
    if(pArr == NULL || idx >= pArr->m_size || idx < 0)
        return ;
    if(pArr->m_size == pArr->m_capacity)	//对空间进行检查
    {
        if(pArr->m_capacity == 0)
            reserve(pArr, 1);
        else
            reserve(pArr, pArr->m_capacity * 2);
    }
    for(i=pArr->m_size; i>idx; --i)
    {
        pArr->m_start[i] = pArr->m_start[i - 1];
    }
    pArr->m_start[idx] = elem;	//连接这个指针域到上一个数据域
    ++pArr->m_size;
}

void basic_array_delete(Array *pArr, int idx)	//删除指定节点的数据
{
    int i = 0;
    if(pArr == NULL || idx >= pArr->m_size || idx < 0)
        return ;
    for(i = idx; i < pArr->m_size - 1; ++i)
    {
        pArr->m_start[i] = pArr->m_start[i+1];
    }
    --pArr->m_size;
    if(pArr->m_size != 0 && pArr->m_size * 2 <= pArr->m_capacity)
    {
        reserve(pArr, pArr->m_capacity / 2);
    }
}

int basic_array_find(Array *pArr, int elem)	//查找指定位置的链表的内容
{
    int i = 0;

    if(pArr)
    {
        for(i=0; i<pArr->m_size; ++i)		//遍历
        {
            if(pArr->m_start[i] == elem)
            {
                return i;
            }
        }
    }
    return -1;
}

void reserve(Array *pArr, int capacity)
{
    int i = 0;
    int *pTmp = NULL;
    
    if(pArr == NULL || capacity <= 0)
        return ;
    pTmp = (int*)malloc(sizeof(int) * capacity);
    
    check_address(pTmp);
    for(i=0; i<pArr->m_size; ++i)
    {
        pTmp[i] = pArr->m_start[i];
    }
    if(pArr->m_start)
        free(pArr->m_start);
    pArr->m_start = pTmp;
    pArr->m_capacity = capacity;
}

void check_address(void *p) {	//内存检查，养成好习惯，习惯检查内存是否申请成功
    if (p == NULL) 
    {
        printf("Unable to allocate memory.\n");
        exit(-1);
    }
}

int main()
{
	basic_array_new(1);
	basic_array_new(2);
	basic_array_new(3);
	basic_array_new(4);
	basic_array_new(5);
	basic_array_new(6);
	basic_array_destroy(2);
	
	system("pause");
}