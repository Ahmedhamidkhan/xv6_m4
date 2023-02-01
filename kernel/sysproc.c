#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "fcntl.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
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
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
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

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
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

  argint(0, &pid);
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

uint64
sys_mmap(void)
{
  int length;
  argint(1, &length);

  int prot;
  argint(2, &prot);

  int flags;
  argint(3, &flags);

  int fd;
  //struct file *f;
  argint(4, &fd);
  

  struct proc *p = myproc();

  struct VMA *vm = 0;
  for(int i=0; i<16; i++) {
    if(p->vma[i].used == 0) {
      vm = &p->vma[i];
      break;
    }
  }
  
  if(vm) {
    //filedup(f);
    uint64 virtual_memory = p->sz;
    p->sz = virtual_memory + length;

    vm->starting_addr = virtual_memory;
    vm->ending_addr = PGROUNDDOWN(virtual_memory + length);
    vm->prot = prot;
    vm->flags = flags;
    vm->offset = 0;
    //vm->f = f;
    vm->used = 1;

    return virtual_memory;
  } 
  else {
      return 0xffffffffffffffff;
  }
}

uint64
sys_munmap(void)
{
  uint64 addr;
  argaddr(0, &addr);

  int len;
  argint(1, &len);

  printf("%d %d\n", addr, len);
  return -1;
}
