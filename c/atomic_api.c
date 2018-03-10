/*
 * 1) try native compiler to find the echo output.
 * gcc atomic_api.c
 * ./a.out
 * echo $?
 *
 * 2) Use mips-mti-elf-objdump to get MIPS32 assembly code and machien code of the wrapper_function().
 *   mips-mti-elf-gcc -std=c99 -O3 atomic_api.c -o atomic_api.out
 *   mips-mti-elf-objdump -D atomic_api.out
 */

#include<stdint.h>

/* Please study MIPS32 Architecture to understand the MIPS machine code.
0040029c <wrapper_function>:
  40029c:	0000000f 	sync
  4002a0:	c0820000 	ll	v0,0(a0)
  4002a4:	00450821 	addu	at,v0,a1
  4002a8:	e0810000 	sc	at,0(a0)
  4002ac:	1020fffc 	beqz	at,4002a0 <wrapper_function+0x4>
  4002b0:	00000000 	nop
  4002b4:	0000000f 	sync
  4002b8:	03e00008 	jr	ra
  4002bc:	00000000 	nop
*/
uint32_t wrapper_function(uint32_t* ptr, uint32_t value) {
      return  __sync_fetch_and_add(ptr, value);
}

uint32_t global_shared_counter = 200;
int main(int argc, char*argv[])
{
          return wrapper_function(&global_shared_counter, 100);
}

