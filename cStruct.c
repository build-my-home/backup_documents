#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include "cStruct.h"

list_t list_create(unsigned int element_size)
{
	list_t l;
	if(element_size == 0)
		return NULL;
	l = (list_t)malloc(sizeof(list_info_t));
	if(l)
	{
		bzero(l, sizeof(list_info_t));
		l->element_size = element_size;
		return l;
	}
	return NULL;
}

void list_destroy(list_t list)
{
	if(!list)
		return;
	list_clear(list);
	free(list);
}

unsigned int list_size(list_t list)
{
	if(!list)
		return 0;
	return list->list_size;
}

void* list_front(list_t list)
{
	if(!list)
		return NULL;
	if(!list->head)
		return NULL;
	return list->head->data;
}

void* list_back(list_t list)
{
	if(!list)
		return NULL;
	if(!list->tail)
		return NULL;
	return list->tail->data;
}

list_iterater_t list_push_front(list_t list, void* value)
{
	list_iterater_t it;
	void *element;
	
	if(!list)
		return NULL;
	
	element = malloc(list->element_size);
	if(!element)
		return NULL;
	
	it = (list_iterater_t)malloc(sizeof(list_ele_t));
	if(!it)
	{
		free(element);
		return NULL;
	}

	if(value)
		memcpy(element, value, list->element_size);
	else
		bzero(element, list->element_size);
	bzero(it, sizeof(list_ele_t));
	it->data = element;
	if(list->list_size == 0)
	{
		list->head = it;
		list->tail = it;
		list->list_size ++;
	}
	else
	{
		list->head->prev = it;
		it->next = list->head;
		list->head = it;
		list->list_size ++;
	}
	return it;
}


list_iterater_t list_push_back(list_t list, void* value)
{
	list_iterater_t it;
	void *element;
	
	if(!list)
		return NULL;
	
	element = malloc(list->element_size);
	if(!element)
		return NULL;
	
	it = (list_iterater_t)malloc(sizeof(list_ele_t));
	if(!it)
	{
		free(element);
		return NULL;
	}

	if(value)
		memcpy(element, value, list->element_size);
	else
		bzero(element, list->element_size);
	bzero(it, sizeof(list_ele_t));
	it->data = element;
	if(list->list_size == 0)
	{
		list->head = it;
		list->tail = it;
		list->list_size ++;
	}
	else
	{
		list->tail->next = it;
		it->prev = list->tail;
		list->tail = it;
		list->list_size ++;
	}
	return it;
}

int list_pop_front(list_t list)
{
	list_iterater_t it;
	if(!list)
		return 0;
	//void *data = NULL;
	it = list->head;
	//if(list->head == list->tail)
	if(list->list_size == 0 || list->list_size == 1)
	{
		list->head = NULL;
		list->tail = NULL;
		//list->list_size = 0;
	}
	else
	{
		list->head = it->next;
		list->head->prev = NULL;
	}

	if(it)
	{
		free(it->data);
		free(it);
		list->list_size --;
		if(list->list_size == 0)
		{
			list->head = NULL;
			list->tail = NULL;
		}
		return 1;
	}
	else
		return 0;
}

int list_pop_back(list_t list)
{
	list_iterater_t it;
	if(!list)
		return 0;
	//void *data = NULL;
	it = list->tail;
	if(list->list_size == 0 || list->list_size == 1)
	{
		list->head = NULL;
		list->tail = NULL;
		//list->list_size = 0;
	}
	else
	{
		list->tail = it->prev;
		list->tail->next = NULL;
	}

	if(it)
	{
		free(it->data);
		free(it);
		list->list_size --;
		if(list->list_size == 0)
		{
			list->head = NULL;
			list->tail = NULL;
		}
		return 1;
	}
	else
		return 0;
}

unsigned int list_erase_by_element(list_t list, void *element)
{
	if((!list) || (!element))
		return 0;
	list_iterater_t it;
	void *p;
	for(it = list_begin(list); it != list_end(list); it = list_iterater_plus(list, it))
	{
		p = list_get_element_by_iterater(list, it);
		if(p == element)
		{
			if(it->next)
				it->next->prev = it->prev;
			if(it->prev)
				it->prev->next = it->next;
			if(it == list->head)
				list->head = it->next;
			if(it == list->tail)
				list->tail = it->prev;
			free(p);
			free(it);
			list->list_size --;
			if(list->list_size == 0)
			{
				list->head = NULL;
				list->tail = NULL;
			}
			return 1;
		}
	}
	return 0;
}

unsigned int list_erase_by_iterater(list_t list, list_iterater_t it)
{
	if((!list) || (!it))
		return 0;
	if(it->next)
		it->next->prev = it->prev;
	if(it->prev)
		it->prev->next = it->next;
	if(it == list->head)
		list->head = it->next;
	if(it == list->tail)
		list->tail = it->prev;
	free(it->data);
	free(it);
	list->list_size --;
	if(list->list_size == 0)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	return 1;
}

unsigned int list_erase_by_index(list_t list, unsigned int index)
{
	if(!list || index >= list_size(list))
		return 0;
	int i;
	list_iterater_t it = list->head;
	for(i = 0; i < index; i ++)
		it = it->next;
	if(it->next)
		it->next->prev = it->prev;
	if(it->prev)
		it->prev->next = it->next;
	if(it == list->head)
		list->head = it->next;
	if(it == list->tail)
		list->tail = it->prev;
	free(it->data);
	free(it);
	list->list_size --;
	if(list->list_size == 0)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	return 1;
}

unsigned int list_clear(list_t list)
{
	list_iterater_t p, q;
	if(!list)
		return 0;
	for(p = list->head; p != NULL; p = q)
	{
		q = p->next;
		free(p->data);
		free(p);
	}
	list->head = NULL;
	list->tail = NULL;
	list->list_size = 0;
}

list_iterater_t list_begin(list_t list)
{
	if(list)
		return list->head;
}

list_iterater_t list_end(list_t list)
{
	return NULL;
}

list_iterater_t list_iterater_plus(list_t list, list_iterater_t it)
{
	if(it)
		return it->next;
	return NULL;
}

list_iterater_t list_iterater_minus(list_t list, list_iterater_t it)
{
	if(it)
		return it->prev;
	return NULL;
}

list_iterater_t list_get_iterater_by_index(list_t list, unsigned int index)
{
	list_iterater_t it;
	if(!list || index >= list_size(list))
		return NULL;
	int i;
	it = list->head;
	for(i = 0; i < index; i ++)
		it = it->next;
	return it;
}

list_iterater_t list_find_iterater_by_element(list_t list, void *element)
{
	if((!list) || !(element))
		return NULL;
	list_iterater_t it;
	for(it = list->head; it != NULL; it = it->next)
	{
		if(it->data == element)
			return it;
	}
	return NULL;
}

void* list_get_element_by_iterater(list_t list, list_iterater_t it)
{
	if((!list) || !(it))
		return NULL;
	return it->data;
}


void list_sort_increase(list_t list, int (*func_compare)(const void *x, const void *y))
{
	list_iterater_t it;
	list_iterater_t new_head, new_tail, old_head, a, b;
	
	new_head = list->head;
	old_head = list->head->next;
	new_head->prev = NULL;
	new_head->next = NULL;
	new_tail = new_head;
	
	while(old_head != NULL)
	{
		a = new_head;
		b = old_head;
		old_head = old_head->next;
		while(1)
		{
			if((*func_compare)(a->data , b->data) >= 0)
			{
				// p <--> ...(b)... a <--> n
				b->prev = a->prev;
				b->next = a;
				if(a->prev)
					a->prev->next = b;
				a->prev = b;
				if(a == new_head)
					new_head = b;
				break;
			}
			else if(a->next == NULL)
			{
				a->next = b;
				b->prev = a;
				b->next = 0;
				new_tail = b;
				break;
			}
			a = a->next;
		}
	}
	list->head = new_head;
	list->tail = new_tail;
}

int list_cmp(const void *x, const void *y)
{
	if( *(const int *)x < *(const int *)y)
		return -1;
	else if( *(const int *)x == *(const int *)y)
		return 0;
	else
		return 1;
}

/*
int main(void)
{
	list_t list;
	list_iterater_t it, p;
	list = list_create(sizeof(int));
	int e, i, *s;
	srand(time(0));
	for(i = 0; i < 100; i++)
	{
		e = rand() % 1000;
		if(e % 2)
		{
			it = list_push_front(list, &e);
			printf("==>list push front: %d\n", e);
		}
		else
		{
			it = list_push_back(list, &e);
			printf("==>list push back: %d\n", e);
		}
		
		list_sort_increase(list, list_cmp);
		
		printf("==>list size: %d\n==>list content:", list_size(list));
		for(it = list_begin(list); it != list_end(list); it = list_iterater_plus(list, it))
		{
			printf(" %d", *(int *)list_get_element_by_iterater(list, it));
		}
		printf("\n");
	}
	for(i = 0; i < 30; i ++)
	{
		e = rand() % list_size(list);
		if(e % 3 == 0)
		{
			it = list_get_iterater_by_index(list, e);
			s = (int *)list_get_element_by_iterater(list, it);
			printf("==>list erase by iterater: %d\n", *s);
			list_erase_by_iterater(list, it);
		}
		else if(e % 3 == 1)
		{
			it = list_get_iterater_by_index(list, e);
			s = (int *)list_get_element_by_iterater(list, it);
			printf("==>list erase by element: %d\n", *s);
			list_erase_by_element(list, s);	
		}
		else
		{
			it = list_get_iterater_by_index(list, e);
			s = (int *)list_get_element_by_iterater(list, it);
			printf("==>list erase by index: %d\n", *s);
			list_erase_by_index(list, e);
		}
		list_sort_increase(list, list_cmp);
		printf("==>list size: %d\n==>list content:", list_size(list));
		for(it = list_begin(list); it != list_end(list); it = list_iterater_plus(list, it))
		{
			printf(" %d", *(int *)list_get_element_by_iterater(list, it));
		}
		printf("\n");
	}
	list_clear(list);
	list_destroy(list);
	return 0;
}
*/



