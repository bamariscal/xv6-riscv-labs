#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


//#6 HW1 - TODO - look at sys_sleep and call procinfo() from here. 
uint64
sys_getprocs(uint64 addr) //uint64 addr as alt
{
//  struct file *f;
//  uint64 st; // user pointer to struct stat
//
//  if(argfd(0, 0, &f) < 0 || argaddr(1, &st) < 0)
//    return -1;
//  return filestat(f, st); //in kernel/file.c and foes work of getting file info

//   return 0;

    int numprocs = procinfo(addr);


    printf("---------- getprocs() after procinfo call");
    printf("\nnum proc >%u<", addr);    
    printf("\nnum proc >%u<", &addr);
    printf("\nnum proc >%s<", addr);
    printf("\nnum proc >%s<", &addr);
    printf("\nnum proc >%d<", addr);
    printf("\nnum proc >%d<", &addr);

    
    return numprocs;

}













