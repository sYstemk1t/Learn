#ifndef _R00TK1T_BASIC_ARRAY_H
#define _R00TK1T_BASIC_ARRAY_H

#include "Array.h"

ArrayOps g_basic_array_handler;

Array* basic_array_new(int);
void basic_array_destroy(Array *);

int basic_array_size(Array *);
int basic_array_capacity(Array *);
int basic_array_is_empty(Array *);

void basic_array_push(Array *, int);
void basic_array_pop(Array *);
int basic_array_back(Array *);
int basic_array_at(Array *, int);
void basic_array_insert(Array *, int, int);
void basic_array_delete(Array *, int);
int basic_array_find(Array *, int);

#endif