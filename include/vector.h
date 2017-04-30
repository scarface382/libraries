#pragma once
#include "utilities.h"

// ERROR_EXIT is a macro defined in utilities.h

typedef struct vector {
    int size;
    int length;
    int cap;
    void* begin;
    void* end;
} vector;

void vector_realloc(vector* v)
{
    if (v->length == v->cap) {
        v->cap *= 2;
        void* tmp = realloc(v->begin, v->size * v->cap);
        if (tmp == NULL) {
            free(v->begin);
            ERROR_EXIT("vector: init malloc failedl\n");
        }
        v->begin = tmp;
        v->end = v->begin + (v->size * v->length);
    }
}

// x MUST BE AN L-VALUE
void vector_push(vector* v, void* x)
{
    vector_realloc(v);
    memmove(v->end, x, v->size);
    v->end += v->size;
    v->length++;
}

void* vector_index(vector* v, int pos)
{
   return v->begin + pos * v->size;
}

// 1) vector pointer 2) object to insert, 3) insert position
void vector_insert(vector* v, void* x, int pos)
{
    vector_push(v, x);
    if (pos >= v->length)
        return;

    void* start = vector_index(v, pos);
    memcpy(start + v->size, start, v->size * (v->length - pos - 1));
    memcpy(start, x, v->size);
}

void vector_insert_int(vector* v,int x, int pos)
{
    vector_push(v, &x);
    if (pos >= v->length)
        return;

    int* start = vector_index(v, pos);
    memcpy(start+1, start, (v->length - pos - 1)*sizeof(int));
    memcpy(start, &x, v->size);
}

void vector_dest(vector* v)
{
   free(v->begin);
}

// users better give a c
void vector_init(vector* v, int size, size_t cap)
{
   if (cap <= 0)
       cap = 1;

   v->length = 0;
   v->size = size;
   v->begin = malloc(size*cap);
   if (v->begin == NULL) ERROR_EXIT("vector: init malloc failedl\n");
   v->end = v->begin;
   v->cap = cap;
}
