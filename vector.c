#ifndef __STRING_H__
#include <string.h>
#define __STRING_H__
#endif

#ifndef __ASSERT_H__
#include <assert.h>
#define __ASSERT_H__
#endif

#ifndef __STDLIB_H__
#include <stdlib.h>
#define __STDLIB_H__
#endif

#ifndef VECTOR_H
#include "vector.h"
#define VECTOR_H
#endif

//函数实现部分

int vector_init(struct Vector *v, size_t capacity)
{
    if (!v)
    {
        return -1;
    }

    int *p = (int *)malloc((sizeof(int)) * capacity);
    if (!p)
    {
        return -2;
    }

    v->_base = p;
    v->_length = 0;
    v->_capacity = capacity;

    return 0;
}

int vector_destory(struct Vector *v)
{
    if (!v)
    {
        return -1;
    }

    free(v->_base);
    free(v);

    return 0;
}

int vector_clear(struct Vector *v)
{
    if (!v)
    {
        return -1;
    }

    memset(v->_base, 0, v->_length);

    v->_length = 0;

    return 0;
}

int vector_push_back(struct Vector *v, int n)
{
    if (!v)
    {
        return -1;
    }

    int i;
    if (v->_capacity < v->_length + 1)
    {
        int _result_vector_increment = vector_increment(v);
        if (!_result_vector_increment)
        {
            return _result_vector_increment;
        }
    }

    v->_base[v->_length] = n;
    ++v->_length;

    return 0;
}

size_t vector_size(struct Vector *v)
{
    if (!v)
    {
        return -1;
    }
    return v->_length;
}

size_t vector_capacity(struct Vector *v)
{
    if (!v)
    {
        return -1;
    }
    return v->_capacity;
}

int *vector_at(struct Vector *v, int index)
{

    assert(index <= v->_capacity);

    return &(v->_base[index]);
}

int vector_value(struct Vector *v, int index)
{

    assert(index <= v->_capacity);

    return v->_base[index];
}

int vector_increment(struct Vector *v)
{
    if (!v)
    {
        return -1;
    }
//CAPACITY_BROADEN==膨胀倍率
#define CAPACITY_BROADEN_RATE 1.5
    int *p = (int *)realloc(v->_base, v->_capacity * CAPACITY_BROADEN_RATE * sizeof(int));
    if (!p)
    {
        return -2;
    }

    v->_base = p;
    v->_capacity *= CAPACITY_BROADEN_RATE;
#undef CAPACITY_BROADEN_RATE

    return 0;
}

int vector_sort(struct Vector *v, int (*ruler)(const void *, const void *))
{
    if (!v)
    {
        return -1;
    }

    qsort(v->_base, v->_length, sizeof(int), ruler);

    return 0;
}

int vector_find(struct Vector *v, int key)
{
    if (!v)
    {
        return -1;
    }

    int i;
    for (i = 0; i < v->_length; ++i)
    {
        if (v->_base[i] == key)
        {
            return i;
        }
    }

    return -2;
}

int vector_cat(struct Vector *v, int *source, int len)
{
    if (!v)
    {
        return -1;
    }

    while (v->_capacity < v->_length + len)
    {
        vector_increment(v);
    }

    memcpy(&(v->_base[v->_length]), source, len * sizeof(int));
    v->_length += len;
}

int vector_assign(struct Vector *v, int index, int n)
{
    assert(v);
    assert(index <= v->_capacity);

    v->_base[index] = n;

    return v->_base[index];
}

int *vector_assign_at(struct Vector *v, int index, int n)
{
    assert(v);
    assert(index <= v->_capacity);

    v->_base[index] = n;

    return &(v->_base[index]);
}