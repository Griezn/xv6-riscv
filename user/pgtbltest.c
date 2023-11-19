#include "kernel/param.h"
#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/riscv.h"
#include "user/user.h"

void pgaccess_test();


int
main(int argc, char *argv[])
{
 pgaccess_test();
 printf("pgtbltest: all tests succeeded\n");
 exit(0);
}


char *testname = "???";


void
err(char *why)
{
    printf("pgtbltest: %s failed: %s, pid=%d\n", testname, why, getpid());
    exit(1); 
}


void
pgaccess_test()
{
    char *pages;
    unsigned int abits;
    printf("pgaccess_test starting\n");
    testname = "pgaccess_test";
    pages = malloc(32 * PGSIZE);

    if (pgaccess(pages, 32, &abits) < 0)
        err("pgaccess failed");

    pages[PGSIZE * 1] += 1;
    pages[PGSIZE * 2] += 1;
    pages[PGSIZE * 30] += 1;

    if (pgaccess(pages, 32, &abits) < 0)
        err("pgaccess failed");
    if (abits != ((1 << 1) | (1 << 2) | (1 << 30)))
        err("incorrect access bits set");

    free(pages);
    printf("pgaccess_test: OK\n");
}