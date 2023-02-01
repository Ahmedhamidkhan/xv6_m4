#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/riscv.h"

int
main()
{
    int x = munmap(0, PGSIZE*2);
    printf("%d\n", x);
    exit(0);
}
