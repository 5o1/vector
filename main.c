#include "Vector.h"
#include <stdio.h>

typedef struct Vector Vector;

int ruler(int a, int b){
    return b-a;
}

int main(){
    int i;
    Vector v1;
    Vector *v=&v1;
    printf("The address of v is %p\n",v);
    printf("Create Array!\n");
    Vector_init(v,100);
    printf("The address of v->base is %p\n",Vector_at(v,0));
    
    printf("\n");
    printf("Putin!\n");
    for(i=0;i<100;++i){
       Vector_push_back(v,i);
    }
    printf("Length is %d\n",Vector_size(v));
	
	printf("\n");
	printf("Value 55 is at %d\n",Vector_find(v,55));
    Vector_sort(v,ruler);
    printf("Sort!\n");
    printf("Now, Value 55 is at %d\n",Vector_find(v,55));
    
    printf("\n");

    printf("The value of 5th is %d\n",Vector_value(v,5));
    printf("The address of 5th is %p\n",Vector_at(v,5));
    
    printf("\n");
    
    int a[]={100,101,102,103,104,105,106,107,108,109,110};
    Vector_cat(v,a,10);
    printf("Nyaaaaaa!!!!\n");
    printf("Length is %d\n",Vector_size(v));
    printf("Capacity is %d\n",Vector_capacity(v));
    printf("The value of 105th is %d\n",Vector_value(v,105));
 	printf("\n");
    
    Vector_increment(v);
    printf("名台词：这比射精还爽100倍啊!!!!\n");
    printf("Capacity is %d\n",Vector_capacity(v));
    
    printf("\n");
    Vector_clear(v);
    printf("Clear Array!\n");
    printf("Value 55 is at %d\n",Vector_find(v,55));
    printf("The value of 5th is %d\n",Vector_value(v,5));

	printf("\n");
    printf("The address of v is %p\n",v);
    Vector_destory(v);
    printf("我……我要坏掉了!\n");
    printf("The address of v is %p\n",v);
    v=NULL;
    printf("空空如也!\n");
    printf("The address of v is %p\n",v);

}
