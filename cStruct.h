#ifndef _CSTRUCT_H
#define _CSTRUCT_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _list_ele_t
{
	void* data;
	struct _list_ele_t *prev;
	struct _list_ele_t *next;
}list_ele_t;

typedef struct _list_info_t
{
	unsigned int element_size;
	unsigned int list_size;
	struct _list_ele_t *head, *tail;
} list_info_t;

/* 链表的实现 */
typedef list_ele_t* list_iterater_t;
typedef list_info_t* list_t;

//链表的创建和销毁
list_t list_create(unsigned int element_size);
void list_destory(list_t list);
//链表大小
unsigned int list_size(list_t list);
//链表压入元素
list_iterater_t list_push_front(list_t list, void *value);
list_iterater_t list_push_back(list_t list, void *value);
//查询链表
void* list_front(list_t list);
void* list_back(list_t list);
//链表压出元素
int list_pop_front(list_t list);
int list_pop_back(list_t list);
//链表的迭代器操作
list_iterater_t list_begin(list_t list);
list_iterater_t list_end(list_t list);
list_iterater_t list_iterater_plus(list_t list, list_iterater_t it);
list_iterater_t list_iterater_minus(list_t list, list_iterater_t it);
list_iterater_t list_find_iterater_by_element(list_t list, void *element);
void* list_get_element_by_iterater(list_t list, list_iterater_t it);
list_iterater_t list_get_iterater_by_index(list_t list, unsigned int index);
//链表的排序(需定义<方法)
void list_sort_increase(list_t list, int (* func_compare)(const void *x, const void *y));
void list_sort_decrease(list_t list, int (* func_compare)(const void *x, const void *y));
//链表的擦除
unsigned int list_erase_by_element(list_t list, void *element);
unsigned int list_erase_by_iterater(list_t list, list_iterater_t it);
unsigned int list_erase_by_index(list_t list, unsigned int index);
unsigned int list_clear(list_t list);

/* 队列的实现 */
/*
typedef list_ele_t* queue_iterater_t;
typedef list_info_t* queue_t;
queue_t queue_creat(unsigned int element_size);
void queue_destory(queue_t queue);
unsigned int queue_size(queue_t queue);
unsigned int queue_push(queue_t queue, void* value);
unsigned int queue_pop(queue_t queue, void* value);
unsigned int queue_clear(queue_t queue);
*/
/* 栈的实现 */
/*
typedef list_ele_t* stack_iterater_t;
typedef list_info_t* stack_t;
stack_t stack_creat(unsigned int element_size);
void stack_destory(stack_t stack);
unsigned int stack_size(stack_t stack);
unsigned int stack_push(stack_t stack, void* value);
unsigned int stack_pop(stack_t stack, void* value);
unsigned int stack_clear(stack_t stack);
*/
/* map容器的实现 */
//key,
/* set容器的实现 */

#ifdef __cplusplus
}
#endif

#endif
