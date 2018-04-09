#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include "control.h"
#define SE_NUM 10
struct Semaphore
{
 int value;
 struct ProcessTable *block;
};
typedef struct Semaphore Semaphore;
extern Semaphore st[SE_NUM];
extern int sem_free;

void P(Semaphore** sem);
void V(Semaphore** sem);
void sem_init(uint32_t *sem,uint32_t value);
void init_sem_table();
//void create_sem(int value);
#endif
