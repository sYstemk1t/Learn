#ifndef R00TK1T_SINGLYLINKEDLIST
#define R00TK1T_SINGLYLINKEDLIST

typedef struct Node {
    struct Node *m_next;
    int m_data;
} Node;

typedef struct SinglyLinkedList {
    Node *m_head;
    int m_count;
} SinglyLinkedList; 

SinglyLinkedList* sllist_create();
void sllist_destroy(SinglyLinkedList *pList);
int sllist_size(SinglyLinkedList *pList);
int sllist_is_empty(SinglyLinkedList *pList);
void sllist_push_front(SinglyLinkedList *pList, int value);
int sllist_pop_front(SinglyLinkedList *pList);
void sllist_push_back(SinglyLinkedList *pList, int value);
int sllist_pop_back(SinglyLinkedList *pList);
int sllist_front(SinglyLinkedList *pList);
int sllist_back(SinglyLinkedList *pList);
int sllist_at(SinglyLinkedList *pList, int index);
void sllist_insert(SinglyLinkedList *pList, int index, int value);
void sllist_erase(SinglyLinkedList *pList, int index);
int sllist_search(SinglyLinkedList *pList, int value);
void sllist_update(SinglyLinkedList *pList, int index, int value);
void sllist_print(SinglyLinkedList *pList);

#endif