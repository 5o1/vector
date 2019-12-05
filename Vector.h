//声明部分开始

#ifndef _MALLOC_H
#include <malloc.h>
#define _MALLOC_H
#endif

#ifndef _STRING_H
#include <string.h>
#define _STRING_H
#endif

// #ifndef size_t
// 	typedef int size_t;
// #endif

struct Vector
{
	int *_base;
	size_t _length;
	size_t _capacity;
};

//初始化数组
void Vector_init(struct Vector *, size_t);

//销毁数组，回收数组使用空间
void Vector_destory(struct Vector *);

//清空数组
void Vector_clear(struct Vector *);

//往数组尾后放一个元素
void Vector_push_back(struct Vector *, int);

//获取数组大小
size_t Vector_size(struct Vector *);

//获取数组实际大小
size_t Vector_capacity(struct Vector *);

//获取数组第index位置的元素地址
int *Vector_at(struct Vector *, int);

//获取数组第index位置元素的值
int Vector_value(struct Vector *, int);

//增大数组实际空间，供内部使用
void Vector_increment(struct Vector *);

//数组排序（任意一种排序方式均可）
void Vector_sort(struct Vector *, int (*)(int, int));

//数组查找元素，如果找到元素返回元素所在位置下标，如果未找到返回-1
int Vector_find(struct Vector *, int);

//批量导入数据，连接两个数组
void Vector_cat(struct Vector *, int *, int);

//为指定下标元素的值赋值	返回操作后该元素的值
int Vector_assign(struct Vector *, int, int);

//为指定下标元素的值赋值	返回该元素的地址
int *Vector_assign_at(struct Vector *, int, int);

//声明部分结束

//函数实现部分

//初始化数组	参数1结构体Vector类型（自定义数组）的指针	参数2预设的数组最大元素个数
void Vector_init(struct Vector *v, size_t capacity)
{
	int *p = (int *)malloc((sizeof(int)) * capacity);
	if (p)
	{
		v->_base = p;
		v->_length = 0;
		v->_capacity = capacity;
	}
}

//销毁数组，回收数组使用空间	从内向外free()
void Vector_destory(struct Vector *v)
{
	if (!v)
	{
		free(v->_base);
		free(v);
		v = NULL;
	}
}

//清空数组	将所有值，以及_length设为0
void Vector_clear(struct Vector *v)
{
	int i;
	for (i = 0; i < v->_length; ++i)
	{
		v->_base[i] = 0;
	}
	v->_length = 0;
}

//往数组尾后放一个元素	当数组容量不够时进入低速状态	对大规模数据请使用Vector_cat()输入
void Vector_push_back(struct Vector *v, int n)
{
	int i;
	if (v->_capacity <= v->_length)
	{
		int *p = (int *)realloc(v->_base, (v->_length + 1) * sizeof(int));
		if (p)
		{
			v->_base = p;
			v->_capacity = v->_length + 1;
		}
	}
	if (v->_length < v->_capacity)
	{
		v->_base[v->_length] = n;
		++v->_length;
	}
}

//获取数组大小
size_t Vector_size(struct Vector *v)
{
	return v->_length;
}

//获取数组实际大小
size_t Vector_capacity(struct Vector *v)
{
	return v->_capacity;
}

//获取数组第index位置的元素地址
int *Vector_at(struct Vector *v, int index)
{
	return &(v->_base[index]);
}

//获取数组第index位置元素的值
int Vector_value(struct Vector *v, int index)
{
	return v->_base[index];
}

//增大数组实际空间，供内部使用
void Vector_increment(struct Vector *v)
{
//CAPACITY_BIGGER==用一次increment()之后海绵体膨胀了多少
#define CAPACITY_BIGGER 100
	int *p = (int *)realloc(v->_base, (v->_capacity + CAPACITY_BIGGER) * sizeof(int));
	if (p)
	{
		v->_base = p;
		v->_capacity += CAPACITY_BIGGER;
	}
}

//数组排序	排序规则由辅助函数确定,返回值>0换，返回值<=0不换(默认根据前一项-后一项返回>0的话，是升序)
void Vector_sort(struct Vector *v, int (*ruler)(int, int))
{
	int i, j;
	for (i = 0; i < v->_length - 1; ++i)
	{
		for (j = i + 1; j < v->_length; ++j)
		{
			if (0 < ruler(v->_base[i], v->_base[j]))
			{
				v->_base[i] ^= v->_base[j];
				v->_base[j] ^= v->_base[i];
				v->_base[i] ^= v->_base[j];
			}
		}
	}
}

//数组查找元素，如果找到元素返回元素所在位置下标，如果未找到返回-1	二分查找，要求先排序;否则遍历全部
int Vector_find(struct Vector *v, int key)
{
	int l = 0;
	int r = v->_length - 1;
	int m;
	int i;

	if (v->_base[l] < v->_base[r])
	{
		while (l <= r)
		{
			m = (l + r) / 2;
			if (v->_base[m] == key)
			{
				return m;
			}
			else if (v->_base[m] < key)
			{
				l = m + 1;
			}
			else
			{
				r = m - 1;
			}
		}
		for (i = 0; i < v->_length; ++i)
		{
			if (v->_base[i] == key)
			{
				return i;
			}
		}
	}
	else if (v->_base[r] < v->_base[l])
	{
		while (l <= r)
		{
			m = (l + r) / 2;
			if (v->_base[m] == key)
			{
				return m;
			}
			else if (key < v->_base[m])
			{
				l = m + 1;
			}
			else
			{
				r = m - 1;
			}
		}
		for (i = 0; i < v->_length; ++i)
		{
			if (v->_base[i] == key)
			{
				return i;
			}
		}
	}
	else
	{
		for (i = 0; i < v->_length; ++i)
		{
			if (v->_base[i] == key)
			{
				return i;
			}
		}
	}
	return -1;
}

//批量导入数据，将第二个数组的前len个元素接到第一个数组尾部
void Vector_cat(struct Vector *v, int *source, int n)
{
	if (v->_capacity < v->_length + n)
	{
		int *p = (int *)realloc(v->_base, (v->_length + n) * sizeof(int));
		if (p)
		{
			v->_base = p;
			v->_capacity = v->_length + n;
		}
	}
	if (v->_length + n <= v->_capacity)
	{
		memcpy(&(v->_base[v->_length]), source, n * sizeof(int));
		v->_length += n;
	}
}

//为指定下标元素的值赋值	返回操作后该元素的值
int Vector_assign(struct Vector *v, int p, int n)
{
	if (p <= v->_length)
	{
		v->_base[p] = n;
	}
	return v->_base[p];
}

//为指定下标元素的值赋值	返回该元素的地址
int *Vector_assign_at(struct Vector *v, int p, int n)
{
	if (p <= v->_length)
	{
		v->_base[p] = n;
	}
	return &(v->_base[p]);
}