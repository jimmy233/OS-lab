#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "common.h"

typedef struct Queue
{
 struct Queue *pre;
 struct Queue *next;
}Queue;

//typedef struct Queue Queue;
Queue freec,block,ready;

#define queue_entry(ptr, type, component) \
     ((type*)((char*)(ptr) - (int)(&((type*)0)->component)))

//void process_load(PCB *pcb){
//}
static inline void add(Queue *pre, Queue *next, Queue *data)
{
	data->pre=pre;
	data->next=next;
		if(pre!=NULL)
		pre->next=data;
		if(next!=NULL)
		next->pre=data;
}

static inline void add_forward(Queue *queue, Queue *data)
{
	add(queue->pre,queue,data);
}

static inline void add_down(Queue *queue, Queue *data)
{
	add(queue,queue->next,data);
}

static inline void delet(Queue *data)
{
  Queue *pre=data->pre;
  Queue *next=data->next;
  	if(pre!=NULL)
		pre->next=next;
	if(next!=NULL)
		next->pre=pre;
}

static inline void initial(Queue *queue)
{
	queue->pre=queue->next=queue;
}

static inline int empty(Queue *queue)
{
  if(queue==queue->next)
  	return 1;
  else
  	return 0;
}

#define queue_foreach(ptr, head) \
	for((prt) = (head)->next; (ptr) != (head); (ptr)=(ptr)->next)

#endif


