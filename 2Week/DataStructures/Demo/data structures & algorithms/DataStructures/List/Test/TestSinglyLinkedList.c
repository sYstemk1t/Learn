#include "../C/SinglyLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ENTER printf("Enter %s\n", __FUNCTION__)
#define LEAVE printf("Leave %s\n\n", __FUNCTION__)

void test_push()
{
    ENTER;
    SinglyLinkedList *pList = sllist_create();
    sllist_push_back(pList, 1);
    sllist_push_back(pList, 2);
    sllist_push_back(pList, 3);
    sllist_push_front(pList, 4);
    sllist_push_front(pList, 5);
    sllist_push_front(pList, 6);

    sllist_print(pList);
    sllist_destroy(pList);
    LEAVE;
}

void test_pop()
{
    ENTER;
    SinglyLinkedList *pList = sllist_create();

    sllist_push_back(pList, 1);
    sllist_push_back(pList, 2);
    sllist_push_back(pList, 3);
    sllist_push_front(pList, 4);
    sllist_push_front(pList, 5);
    sllist_push_front(pList, 6);

    printf("pop front %d\n", sllist_pop_front(pList));
    printf("pop front %d\n", sllist_pop_front(pList));
    printf("pop back %d\n", sllist_pop_back(pList));
    printf("pop back %d\n", sllist_pop_back(pList));

    sllist_print(pList);
    sllist_destroy(pList);
    LEAVE;
}

void test_size()
{
    ENTER;
    SinglyLinkedList *pList = sllist_create();
    sllist_push_back(pList, 1);
    sllist_push_back(pList, 2);
    sllist_push_back(pList, 3);
    sllist_pop_back(pList);
    sllist_push_front(pList, 4);
    sllist_push_front(pList, 5);
    sllist_pop_front(pList);
    
    assert(sllist_size(pList) == 3);
    printf("pass\n");
    sllist_destroy(pList);
    LEAVE;
}

void test_empty()
{
    ENTER;
    SinglyLinkedList *pList = sllist_create();
    sllist_push_back(pList, 1);
    sllist_push_back(pList, 2);
    assert(sllist_is_empty(pList) == 0);

    sllist_pop_back(pList);
    sllist_pop_front(pList);
    assert(sllist_is_empty(pList) == 1);

    printf("pass\n");
    sllist_destroy(pList);
    LEAVE;
}

void test_at_front_back()
{
    ENTER;
    SinglyLinkedList *pList = sllist_create();
    sllist_push_back(pList, 1);
    sllist_push_back(pList, 2);
    sllist_push_back(pList, 3);
    sllist_push_back(pList, 4);
    sllist_push_back(pList, 5);
    
    assert(sllist_at(pList, 0) == 1);
    assert(sllist_at(pList, 2) == 3);
    assert(sllist_at(pList, 4) == 5);
    assert(sllist_front(pList) == 1);
    assert(sllist_back(pList) == 5);

    printf("pass\n");
    sllist_destroy(pList);
    LEAVE;
}

void test_insert()
{
    ENTER;
    SinglyLinkedList *pList = sllist_create();
    sllist_insert(pList, 0, 5);
    sllist_insert(pList, 0, 2);
    sllist_insert(pList, 0, 1);
    sllist_insert(pList, 2, 3);
    sllist_insert(pList, 3, 4);

    sllist_print(pList);

    assert(sllist_at(pList, 0) == 1);
    assert(sllist_at(pList, 1) == 2);
    assert(sllist_at(pList, 2) == 3);
    assert(sllist_at(pList, 3) == 4);
    assert(sllist_at(pList, 4) == 5);

    sllist_destroy(pList);
    LEAVE;
}

void test_erase()
{
    ENTER;
    SinglyLinkedList *pList = sllist_create();
    sllist_insert(pList, 0, 5);
    sllist_insert(pList, 0, 2);
    sllist_insert(pList, 0, 1);
    sllist_insert(pList, 2, 3);
    sllist_insert(pList, 3, 4);

    sllist_erase(pList, 0);
    sllist_erase(pList, 1);
    sllist_erase(pList, 2);

    sllist_print(pList);

    assert(sllist_at(pList, 0) == 2);
    assert(sllist_at(pList, 1) == 4);

    sllist_destroy(pList);

    LEAVE;
}

void test_update()
{
    ENTER;
    SinglyLinkedList *pList = sllist_create();
    sllist_insert(pList, 0, 5);
    sllist_insert(pList, 0, 2);
    sllist_insert(pList, 0, 1);
    sllist_insert(pList, 2, 3);
    sllist_insert(pList, 3, 4);

    sllist_update(pList, 2, 10);
    assert(sllist_at(pList, 2) == 10);
    sllist_print(pList);

    sllist_destroy(pList);

    LEAVE;
}

void run_all_tests()
{
    test_push();
    test_pop();
    test_size();
    test_empty();
    test_at_front_back();
    test_insert();
    test_erase();
    test_update();
}

int main()
{
    run_all_tests();
    return 0;
}