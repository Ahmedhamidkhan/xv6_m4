#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/riscv.h"

int
main()
{
    uint64 x = (uint64)mmap(0, PGSIZE*2, PROT_READ, MAP_PRIVATE, 0, 0);
    printf("x: %d\n", x);
    exit(0);
}
