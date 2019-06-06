#include "../C/Array.h"
#include "../C/BasicArray.h"
#include <stdio.h>
#include <stdlib.h>

static void test_array_print(Array *pArr);
static void run_all_tests();
static void test_array_new();
static void test_array_push();
static void test_array_is_empty();
static void test_array_at();
static void test_array_pop();
static void test_array_insert();
static void test_array_delete();
static void test_array_back();
static void test_array_find();

#define ENTER printf("Enter %s\n", __FUNCTION__)
#define LEAVE printf("Leave %s\n\n", __FUNCTION__)

int main()
{
    run_all_tests();
    return 0;
}

void run_all_tests()
{
    test_array_new();
    test_array_push();
    test_array_pop();
    test_array_insert();
    test_array_delete();
    test_array_is_empty();
    test_array_at();
    test_array_back();
    test_array_find();
}

void test_array_new()
{
    ENTER;
    Array *pArr = g_basic_array_handler.new_handler(5);
    ArrayOps *pOps = pArr->m_handler;
    printf("array size: %d, capacity: %d\n", pOps->size_handler(pArr), pOps->capacity_handler(pArr));
    test_array_print(pArr);
    pOps->destroy_handler(pArr);
    LEAVE;
}

void test_array_push()
{
    ENTER;
    Array *pArr = g_basic_array_handler.new_handler(0);
    ArrayOps *pOps = pArr->m_handler;
    pOps->push_handler(pArr, 2);
    pOps->push_handler(pArr, 3);
    pOps->push_handler(pArr, 5);
    printf("array size: %d, capacity: %d\n", pOps->size_handler(pArr), pOps->capacity_handler(pArr));
    test_array_print(pArr);
    pOps->destroy_handler(pArr);
    LEAVE;
}

void test_array_pop()
{
    ENTER;
    Array *pArr = g_basic_array_handler.new_handler(0);
    ArrayOps *pOps = pArr->m_handler;
    pOps->push_handler(pArr, 2);
    pOps->push_handler(pArr, 3);
    pOps->push_handler(pArr, 5);
    printf("array size: %d, capacity: %d\n", pOps->size_handler(pArr), pOps->capacity_handler(pArr));
    test_array_print(pArr);

    pOps->pop_handler(pArr);
    printf("array size: %d, capacity: %d\n", pOps->size_handler(pArr), pOps->capacity_handler(pArr));
    test_array_print(pArr);

    pOps->pop_handler(pArr);
    printf("array size: %d, capacity: %d\n", pOps->size_handler(pArr), pOps->capacity_handler(pArr));
    test_array_print(pArr);

    pOps->pop_handler(pArr);
    printf("array size: %d, capacity: %d\n", pOps->size_handler(pArr), pOps->capacity_handler(pArr));
    test_array_print(pArr);
    pOps->destroy_handler(pArr);
    LEAVE;
}

void test_array_insert()
{
    ENTER;
    Array *pArr = g_basic_array_handler.new_handler(5);
    ArrayOps *pOps = pArr->m_handler;
    printf("array size: %d, capacity: %d\n", pOps->size_handler(pArr), pOps->capacity_handler(pArr));
    test_array_print(pArr);
    pOps->insert_handler(pArr, 2, 10);
    printf("array size: %d, capacity: %d\n", pOps->size_handler(pArr), pOps->capacity_handler(pArr));
    test_array_print(pArr);
    pOps->destroy_handler(pArr);
    LEAVE;
}

void test_array_delete()
{
    ENTER;
    Array *pArr = g_basic_array_handler.new_handler(0);
    ArrayOps *pOps = pArr->m_handler;
    pOps->push_handler(pArr, 2);
    pOps->push_handler(pArr, 3);
    pOps->push_handler(pArr, 5);
    printf("array size: %d, capacity: %d\n", pOps->size_handler(pArr), pOps->capacity_handler(pArr));
    test_array_print(pArr);
    pOps->delete_handler(pArr, 1);
    printf("array size: %d, capacity: %d\n", pOps->size_handler(pArr), pOps->capacity_handler(pArr));
    test_array_print(pArr);
    pOps->destroy_handler(pArr);
    LEAVE;
}

void test_array_is_empty()
{
    ENTER;
    Array *pArr = g_basic_array_handler.new_handler(0);
    ArrayOps *pOps = pArr->m_handler;
    test_array_print(pArr);
    printf("Is array empty ? [%c]\n", pOps->is_empty_handler(pArr) == 1 ? 'Y' : 'N');
    pOps->push_handler(pArr, 2);
    pOps->push_handler(pArr, 3);
    pOps->push_handler(pArr, 5);
    printf("Push 3 elements\n");
    test_array_print(pArr);
    printf("Is array empty ? [%c]\n", pOps->is_empty_handler(pArr) == 1 ? 'Y' : 'N');
    pOps->destroy_handler(pArr);
    LEAVE;
}

void test_array_at()
{
    ENTER;
    Array *pArr = g_basic_array_handler.new_handler(0);
    ArrayOps *pOps = pArr->m_handler;
    int i;

    pOps->push_handler(pArr, 2);
    pOps->push_handler(pArr, 3);
    pOps->push_handler(pArr, 5);
    for(i=0; i<pOps->size_handler(pArr); ++i)
    {
        printf("elem %d is %d\n", i, pOps->at_handler(pArr, i));
    }
    pOps->destroy_handler(pArr);
    LEAVE;
}

void test_array_back()
{
    ENTER;
    Array *pArr = g_basic_array_handler.new_handler(0);
    ArrayOps *pOps = pArr->m_handler;

    pOps->push_handler(pArr, 2);
    pOps->push_handler(pArr, 3);
    pOps->push_handler(pArr, 5);
    test_array_print(pArr);
    printf("the back elem is %d\n", pOps->back_handler(pArr));
    pOps->destroy_handler(pArr);
    LEAVE;
}

void test_array_find()
{
    ENTER;
    Array *pArr = g_basic_array_handler.new_handler(0);
    ArrayOps *pOps = pArr->m_handler;
    int i;

    pOps->push_handler(pArr, 23);
    pOps->push_handler(pArr, 14);
    pOps->push_handler(pArr, 35);
    pOps->push_handler(pArr, 7);
    pOps->push_handler(pArr, 11);
    pOps->push_handler(pArr, 75);
    test_array_print(pArr);
    printf("find 35 at %d\n", pOps->find_handler(pArr, 35));
    pOps->destroy_handler(pArr);
    LEAVE;
}

void test_array_print(Array *pArr)
{
    int i = 0;

    if(pArr)
    {
        printf("Array Elements: \n");
        for(i=0; i<pArr->m_size; ++i)
        {
            printf("%d\t", pArr->m_start[i]);
        }
        printf("\n");
    }
}