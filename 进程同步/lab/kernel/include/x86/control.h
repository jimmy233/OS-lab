#ifndef __X86_CONTROL_H__
#define __X86_CONTROL_H__

#include "memory.h"
#include "semaphore.h"
#define TASK_RUNNING 0
#define TASK_BLOCKED 1
#define TASK_RUNNABLE 2
#define TASK_NEW 3
#define TASK_DEAD 4

#define PCB_NUM 10
#define STACK_SIZE 4096

typedef struct ProcessTable
{
 struct TrapFrame sp;
 int state;
 int timeCount;
 int sleepTime;
 unsigned int pid;
 struct Semaphore* sem;
 struct ProcessTable *next;	
}ProcessTable;

extern ProcessTable pcb[PCB_NUM];
extern ProcessTable *block_head,*block_tail;
extern ProcessTable *run_head,*run_tail;
extern ProcessTable *freec;
extern ProcessTable *rn;
extern ProcessTable *idle_pcb;

 void init_pcb();
 ProcessTable *newp();
 void insert2(ProcessTable *pcb);
 void insert(ProcessTable *pcb);
 void delet2(ProcessTable *pcb);
 void delet(ProcessTable *pcb);
 void free_pcb(ProcessTable *pcb);

#endif
