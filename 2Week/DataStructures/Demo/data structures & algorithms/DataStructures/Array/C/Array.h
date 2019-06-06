#ifndef _R00TK1T_ARRAY_H
#define _R00TK1T_ARRAY_H

struct ArrayOps;

typedef struct Array{
    int m_size;
    int m_capacity;
    int *m_start;
    struct ArrayOps *m_handler;
} Array;

typedef Array* (*array_new_handler)(int);
typedef void (*array_destroy_handler)(Array *);
typedef int (*array_common_size_handler)(Array *);
typedef void (*array_push_handler)(Array *, int);
typedef void (*array_pop_handler)(Array *);
typedef int (*array_back_handler)(Array *);
typedef int (*array_at_handler)(Array *, int);
typedef void (*array_insert_handler)(Array *, int, int);
typedef void (*array_delete_handler)(Array *, int);
typedef int (*array_find_handler)(Array *, int);

typedef struct ArrayOps{
    array_new_handler           new_handler;
    array_destroy_handler       destroy_handler;
    array_common_size_handler   size_handler;
    array_common_size_handler   capacity_handler;
    array_common_size_handler   is_empty_handler;
    array_push_handler          push_handler;
    array_pop_handler           pop_handler;
    array_back_handler          back_handler;
    array_at_handler            at_handler;
    array_insert_handler        insert_handler;
    array_delete_handler        delete_handler;
    array_find_handler          find_handler;
} ArrayOps;

#endif 