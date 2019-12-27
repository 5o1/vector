//声明部分开始


#ifndef size_t
	typedef int size_t;
#endif

struct Vector
{
	size_t _length;
	size_t _capacity;
	int *_base;
};

//初始化数组;0:成功;-1:参数1错误
int vector_init(struct Vector *, size_t);

//销毁数组，回收数组使用空间;0:成功;-1:参数1错误
int vector_destory(struct Vector *);

//清空数组;0:成功;-1:参数1错误
int vector_clear(struct Vector *);

//往数组尾后放一个元素;0:成功;-1:参数1错误
int vector_push_back(struct Vector *, int);

//获取数组大小;非负:成功;-1:参数1错误
size_t vector_size(struct Vector *);

//获取数组容量;非负:成功;-1:参数1错误
size_t vector_capacity(struct Vector *);

//获取数组第index位置的元素地址;大于0:成功;
int *vector_at(struct Vector *, int);

//获取数组第index位置元素的值;0:成功;
int vector_value(struct Vector *, int);

//增大数组实际空间，供内部使用
int vector_increment(struct Vector *);

//数组排序（任意一种排序方式均可）;0:成功;-1:参数1错误
int vector_sort(struct Vector *, int (*)(const void *, const void *));

//数组查找元素;非负:成功;-1:参数1错误;-2:未找到
int vector_find(struct Vector *, int);

//批量导入数据，连接两个数组;0:成功;-1:参数1错误
int vector_cat(struct Vector *, int *, int);

//为指定下标元素的值赋值;返回操作后该元素的值;0:成功;-1:参数1错误
int vector_assign(struct Vector *, int, int);

//为指定下标元素的值赋值;返回该元素的地址;0:成功;-1:参数1错误
int *vector_assign_at(struct Vector *, int, int);

//声明部分结束

