/* Test if your machine is big-endian or little-endian
 * Compile:
 * gcc endian.c
 * Run:
 * ./a.out
 * Output on a Little Endian machine.
 * d32=0x64636261.
 * byte[0]=a 61
 * byte[1]=b 62
 * byte[2]=c 63
 * byte[3]=d 64
 * LE ENDIAN
 * http://stackoverflow.com/questions/12687274/size-of-stack-and-heap-memory
 * http://stackoverflow.com/questions/8367001/how-to-check-heap-size-for-a-process-on-linux
 */
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint32_t;
typedef union {
      char d8[4];
      uint32_t d32;
} SignType;

typedef struct IMG_HDR_TAG {
        SignType    signiture;
        uint32_t    len;
        uint32_t    offset;
        uint32_t    crc32;
} IMG_HDR;

int foo(int* p) {
    int volatile x = 0;

    printf(" p:%p\n", p);
    printf("&p:%p\n", &p);
    printf("&x:%p\n", &x);
    printf("&x:%p %s p:%p\n", &x, (&x>p)?">":"<", p);
    return (&x > p);
}
int is_stack_grow_up(void) {
    int a = 0;
    return foo(&a);
}

void check_stack_heap(int depth) {
    char c;
    char *ptr = (char*) malloc(1024);
    printf("stack at %p, heap at %p\n", &c, ptr);
    if (depth <= 0) return;
    check_stack_heap(depth-1);
    free(ptr);
}

static int g_x = 17;

void memory_layout(IMG_HDR* hdr);

int main(void) {
        IMG_HDR hdr;
        hdr.signiture.d8[0] = 0x61;
        hdr.signiture.d8[1] = 0x62;
        hdr.signiture.d8[2] = 0x63;
        hdr.signiture.d8[3] = 0x64;
	hdr.len = 1024;
	hdr.offset = 256;
	hdr.crc32  = (uint32_t)-1;

        printf("d32=0x%04X.\n", hdr.signiture.d32);
	for(int i=0; i<4; i++) {
		char ch = hdr.signiture.d8[i];
		printf("byte[%d]=%c %02X\n", i, ch, ch);
	}
        if(hdr.signiture.d32 == 0x64636261)
		printf("LE ENDIAN\n");
        else
		printf("BIG ENDIAN\n");

	printf("Stack Direction: %s\n", is_stack_grow_up()?"UP":"DOWN");

	memory_layout(&hdr);

        check_stack_heap(10);

	return 0;
}

// ulimit -s
// 8MB
#define BUF_SIZE 1024*1024*1

void memory_layout(IMG_HDR* hdr)
{
    IMG_HDR* heap_hdr =  (IMG_HDR*)malloc(sizeof(IMG_HDR));
    int stack_buf[BUF_SIZE];
    int* mem = (int*) heap_hdr;
    unsigned long long x = (unsigned long long) -1;
    unsigned long long y = x >> 12;
    unsigned long long z = y << 12;
    printf("%llx %llx %llx\n", x, y, z);

    for(int i=0; i < BUF_SIZE; i++) stack_buf[i] = i;

    *heap_hdr = *hdr;
    printf("&stack_buf[BUF_SIZE]  = %p\n", &stack_buf[BUF_SIZE]);
    printf("stack_buf (local var) = %p\n", stack_buf);
    printf("&hdr  (args)          = %p\n", &hdr);
    printf("&heap_hdr (local_var) = %p\n", &heap_hdr);
    printf("&mem  (local var)     = %p\n", &mem);
    printf("heap_hdr (heap)       = %p\n", heap_hdr);
    printf("&g_x                  = %p\n", &g_x);
    printf("memory_layout         = %p\n", memory_layout);
    printf("main                  = %p\n", main);

    int sz = sizeof(IMG_HDR)/sizeof(int);
    for(int i=-2; i < sz; i++) {
	printf("mem[%02d] %08X\n", i, mem[i]);
    }
    free(heap_hdr);

}
