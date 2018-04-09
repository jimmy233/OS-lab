#include "lib.h"
#include "types.h"
#include <sys/syscall.h>
#include <stdarg.h>
/*
 * io lib here
 * 库函数写在这
 */
int32_t syscall(int num, uint32_t a1,uint32_t a2,
		uint32_t a3, uint32_t a4, uint32_t a5)
{
	int32_t ret = 0;

	/* 内嵌汇编 保存 num, a1, a2, a3, a4, a5 至通用寄存器*/
  
	asm volatile("int $0x80": "=a"(ret) : "a"(num), "b"(a1), "c"(a2), "d"(a3), "S"(a4), "D"(a5));
		
	return ret;
}

void printf(const char *format,...){
   void *args = (void **)&format + 1;
   char p[70000];
   int temp=0;
   int NO=0;
    va_list arg;  
    va_start(arg, format);   
  
    while (*format)  
    {  
        char ret = *format;  
        if (ret == '%')  
        { 
 	int val = *(int32_t*)((void**)args + NO); 
            switch (*++format)  
            {
  
            case 'c':  
            {  
                        int ch = va_arg(arg, int);  
                        p[temp]=ch; 
			temp++; 
                        break;  
            }  
            case 's':  
            {  
            		char *str = *(char**)((void**)args + NO);
			int t = 0;
			while(str[t] != 0)
				{
					p[temp++] = str[t];
							t++;
				}
						break; 

            }
	    case 'd':
	    {
	    		char buf1[16];
			int m = val,k = 0;
			//unsigned int n = val;
			int j;
			if(val == 0){
				buf1[k++] = '0';
				j = k-1;
				    }
			else{
			while(m != 0){
				if(m > 0)
					buf1[k] = (m%10 + '0');
				else
					buf1[k] = (-(m%10) + '0');
					m =m/10;
					k++;
				     }
			         if(val < 0)
					buf1[k++] = '-';
					j = k-1;
			    }
			    while(j>=0)
			    {
				p[temp++] = buf1[j];
				j--;
			   }
			break;
	    }
	    case 'x':
	    {
	        	char buf2[16];
			unsigned int n = val;
			int k = 0;
			int j;
			if(n==0)
			{
 				p[temp++]='0';
			}
			while(n != 0){
			unsigned int bit4 = n&0xf;
			if(bit4 < 10)
				buf2[k++] = bit4 + '0';
			else
				buf2[k++] = (bit4 - 0xa) + 'A';
			n =n>> 4;
				}
				j = k-1;
			      while(j>=0)
			      {
				p[temp++] = buf2[j];
				j--;
			      }
			break; 
	    }
            default:  
                break;  
            }
	NO++;  
        }  
        else  
        {  
           p[temp]=*format; 
	   temp++;
        }  
        format++;  
    }  
    va_end(arg);  
    p[temp]='\0';
    syscall(4,1,(uint32_t)p,temp,0,0);
}

int fork(void)
{
	return syscall(2,0,0,0,0,0);
}

void sleep(int time)
{
	syscall(162,time,0,0,0,0);
}

void exit()
{
 syscall(1,0,0,0,0,0);
}
int sem_init(sem_t *sem,uint32_t value)
{
 *sem=0;
 syscall(5,value,*sem,0,0,0);
 return 0;
}
int sem_post(sem_t *sem)
{
syscall(8,0,*sem,0,0,0);
return 0;
}
int sem_wait(sem_t *sem)
{
 syscall(7,0,*sem,0,0,0);
 return 0;
}

int sem_destroy(sem_t *sem)
{
	syscall(6,0,*sem,0,0,0);
	return 0;
}
