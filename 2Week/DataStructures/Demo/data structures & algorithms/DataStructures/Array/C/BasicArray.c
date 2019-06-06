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

Array* basic_array_new(int capacity)	//���һ���µĽڵ�
{
    Array *pArr = NULL;		//����һ��ָ�룬*pArr���ڿ�ֵ
    if(capacity < 0)	//���capacityС��0�Ļ���ֱ��return������Ϊ�ڵ�Ŀ�ʼ����0,�ṹ���е�������������int��
        return NULL;
    pArr = (Array*)malloc(sizeof(Array));	//����ṹ��Array�Ĵ�С���������ڴ�ռ�
    check_address(pArr);	//�ж�pArr�����ڴ�ռ��Ƿ�ɹ�

    pArr->m_size = capacity;	//������m_size��ֵ
    pArr->m_capacity = capacity;	//������m_capacity��ֵ
    if(capacity == 0)	//���m_capacity��ֵ�ɹ������Ǹ�ֵΪ0
    {
        pArr->m_start = NULL;	//��m_start��ֵΪ��ֵ
    }
    else
    {
        pArr->m_start = (int *)malloc(sizeof(int) * capacity);	//Ϊm_start����һ���ڴ�ռ䡣
        check_address(pArr->m_start);	//����ڴ��Ƿ񿪱ٳɹ�
        memset(pArr->m_start, 0, sizeof(int) * capacity);	//��m_start���ֵ��ȫ����Ϊ0
    }
    pArr->m_handler = &g_basic_array_handler;	//������ʱ�������һ�ο�ʼ����Ϊg_basic_array_handler��װ�����к���
    return pArr;
}

void basic_array_destroy(Array *pArr)	//�����������
{
    if(pArr)
    {
		for (int i = 0; i < pArr->m_capacity; ++i)
		{
			free(pArr->m_start[i]);		//���capacityС��u����iֵȫ���ͷ�
		}
        free(pArr);
    }
}

int basic_array_size(Array *pArr)
{
    if(pArr)	//�ж��Ƿ�Ϊ�棬Ϊ����return
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
            reserve(pArr, 1);	//�����ǰ�Ŀռ�Ϊ0����ѵ�ǰ���Ƶ�ֵ�޸�Ϊ1
        else
            reserve(pArr, pArr->m_capacity * 2);
    }		//����ռ䲻�����Կռ��������
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
    }	//����ռ䲻��Ҫ��ô�󣬾Ͱ��ⲿ�ֿռ��ͷ�
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

void basic_array_insert(Array *pArr, int idx, int elem)	//��ĳ�����ϲ�������
{
    int i = 0;
    if(pArr == NULL || idx >= pArr->m_size || idx < 0)
        return ;
    if(pArr->m_size == pArr->m_capacity)	//�Կռ���м��
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
    pArr->m_start[idx] = elem;	//�������ָ������һ��������
    ++pArr->m_size;
}

void basic_array_delete(Array *pArr, int idx)	//ɾ��ָ���ڵ������
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

int basic_array_find(Array *pArr, int elem)	//����ָ��λ�õ����������
{
    int i = 0;

    if(pArr)
    {
        for(i=0; i<pArr->m_size; ++i)		//����
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

void check_address(void *p) {	//�ڴ��飬���ɺ�ϰ�ߣ�ϰ�߼���ڴ��Ƿ�����ɹ�
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