#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define MAP_HUGETLB     0x40000         /*  create a huge page mapping */
#define MAP_HUGE_SHIFT  26
#define MAP_HUGE_1GB    (30 << MAP_HUGE_SHIFT)

#define KSIZE 1024L
#define MSIZE (1024L*1024L)
#define GSIZE (1024L*1024L*1024L)
#define TSIZE (1024L*GSIZE)

#define INIT_MEM 0
// Fail on my MacBook Pro (Retina, 13-inch, Early 2015)
// Darwin Kernel Version 16.5.0:x86_64
// #define NUMSIZE  (16L * TSIZE)

// mmap ok; init: got killed; signal 9
// #define NUMSIZE  (8L * TSIZE)

// Got killed signal 9
// #define NUMSIZE  (1L * TSIZE)

// OK
// #define NUMSIZE  (200L * GSIZE)

// OK
#define NUMSIZE  (20L * GSIZE)
typedef unsigned long long ETYPE;

#define MEMSIZE (NUMSIZE*sizeof(ETYPE))
#define PGSIZE (16*KSIZE)

void init(ETYPE* ptr) {
        *ptr = (ETYPE)ptr;
}

int verify(ETYPE* ptr) {
        if (*ptr != (ETYPE)ptr) {
                fprintf(stderr, "ERROR: 0x%016llx != %p.\n", *ptr, ptr);
                return -1;
        }
        else {
                fprintf(stdout, "OK: 0x%016llx = %p.\n", *ptr, ptr);
        }
        return 0;
}

int garr[10000];

void* poolmap(uint64_t base, uint64_t size)
{
    int i;
    int fd;
    ETYPE *pBegin;
    int flags = MAP_SHARED | MAP_ANONYMOUS | MAP_HUGETLB | MAP_HUGE_1GB;
    printf("mmap memory size:%llu GB\n", size/GSIZE);
    pBegin = (ETYPE*) mmap((void*)base, size, PROT_READ | PROT_WRITE, flags, -1, 0);
    if (pBegin == MAP_FAILED) {
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }

    ETYPE* pEnd = pBegin + NUMSIZE;
    ETYPE* pCur = pBegin;

    init(&pBegin[0]);
    init(&pBegin[NUMSIZE-1]);

    verify(&pBegin[0]);
    verify(&pBegin[NUMSIZE-1]);
    return pBegin;
}
int poolfree(void* ptr, uint64_t size) {
    int rc = munmap(ptr, size);
    if (rc  == -1) {
        perror("Error un-mmapping the file");
    }
    return rc;
}

int main(int argc, char *argv[])
{
    int i;
    int fd;
    ETYPE *pBegin;

    int * p = (int *) malloc(sizeof(int));
    *p= 0xcafe;
    printf("global garr:%p\n", garr);
    printf("heap p:%p\n", p);
    printf("code p:%p\n", main);
    printf("stack p:%p\n", &fd);
    printf("%08X\n", p[0]);
    printf("%08X\n", p[-1000]);
    printf("%08X\n", p[100000]);
    // Segmentation fault: 11
    // printf("%08X\n", p[-1000000]);
    // printf("%08X\n", p[ 1000000]);
    free(p);

    ETYPE* arr[8];
    uint64_t base = 0x100000000000LL;
    for (int i = 0; i < 4; i++) {
    	arr[i] = (ETYPE*) poolmap(base, MEMSIZE);
    }
    for (int i = 0; i < 4; i++) {
    	poolfree(arr[i], MEMSIZE);
    }
    return 0;
}
