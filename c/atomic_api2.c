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
#include<stdio.h>

#define PRINTF(a,b) 

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
uint32_t _atomic_fetch_and_add(uint32_t* ptr, uint32_t value) {
      return  __sync_fetch_and_add(ptr, value);
}
uint32_t _atomic_fetch_and_sub(uint32_t* ptr, uint32_t value) {
      return  __sync_fetch_and_sub(ptr, value);
}
uint32_t _atomic_fetch_and_or(uint32_t* ptr, uint32_t value) {
      return  __sync_fetch_and_or(ptr, value);
}
uint32_t _atomic_fetch_and_and(uint32_t* ptr, uint32_t value) {
      return  __sync_fetch_and_or(ptr, value);
}
uint32_t _atomic_fetch_and_xor(uint32_t* ptr, uint32_t value) {
      return  __sync_fetch_and_xor(ptr, value);
}
// { *ptr = ~(*ptr & value); return *ptr; }   // nand
uint32_t _atomic_fetch_and_nand(uint32_t* ptr, uint32_t value) {
      return  __sync_fetch_and_nand(ptr, value);
}

uint32_t _atomic_add_and_fetch(uint32_t* ptr, uint32_t value) {
      return  __sync_add_and_fetch(ptr, value);
}
uint32_t _atomic_sub_and_fetch(uint32_t* ptr, uint32_t value) {
      return  __sync_sub_and_fetch(ptr, value);
}
uint32_t _atomic_or_and_fetch(uint32_t* ptr, uint32_t value) {
      return  __sync_or_and_fetch(ptr, value);
}
uint32_t _atomic_and_and_fetch(uint32_t* ptr, uint32_t value) {
      return  __sync_and_and_fetch(ptr, value);
}
uint32_t _atomic_xor_and_fetch(uint32_t* ptr, uint32_t value) {
      return  __sync_xor_and_fetch(ptr, value);
}
uint32_t _atomic_nand_and_fetch(uint32_t* ptr, uint32_t value) {
      return  __sync_nand_and_fetch(ptr, value);
}

uint32_t _atomic_bool_compare_and_swap(uint32_t *ptr, uint32_t oldval, uint32_t newval)
{
 	return __sync_bool_compare_and_swap(ptr, oldval, newval);
}

uint32_t _atomic_val_compare_and_swap(uint32_t *ptr, uint32_t oldval, uint32_t newval)
{
	return __sync_val_compare_and_swap (ptr, oldval, newval);
}

// It writes value into *ptr, and returns the previous contents of *ptr.
uint32_t _atomic_exchange(uint32_t *ptr, uint32_t value)
{
	return __sync_lock_test_and_set (ptr, value);
}

void _atomic_lock_release(uint32_t *ptr) {
	return __sync_lock_release(ptr);
}

uint32_t global_shared_counter = 200;
int main(int argc, char*argv[])
{
	uint32_t val = 0;
	val = _atomic_fetch_and_add(&global_shared_counter, 100);
	PRINTF("val:%X\n", val);
	val = _atomic_fetch_and_sub(&global_shared_counter, 100);
	PRINTF("val:%X\n", val);
	val = _atomic_fetch_and_or(&global_shared_counter, 0);
	PRINTF("val:%X\n", val);
	val = _atomic_fetch_and_and(&global_shared_counter, 0xFFFFFFFF);
	PRINTF("val:%X\n", val);
	val = _atomic_fetch_and_xor(&global_shared_counter, 0);
	PRINTF("val:%X\n", val);
	val = _atomic_fetch_and_nand(&global_shared_counter, 0xFFFFFFFF);
	PRINTF("val:%X\n", val);

	val = _atomic_add_and_fetch(&global_shared_counter, 100);
	PRINTF("val:%X\n", val);
	val = _atomic_sub_and_fetch(&global_shared_counter, 100);
	PRINTF("val:%X\n", val);
	val = _atomic_or_and_fetch(&global_shared_counter, 0);
	PRINTF("val:%X\n", val);
	val = _atomic_and_and_fetch(&global_shared_counter, 0xFFFFFFFF);
	PRINTF("val:%X\n", val);
	val = _atomic_xor_and_fetch(&global_shared_counter, 0);
	PRINTF("val:%X\n", val);
	val = _atomic_nand_and_fetch(&global_shared_counter, 0xFFFFFFFF);
	PRINTF("val:%X\n", val);

	val = _atomic_bool_compare_and_swap(&global_shared_counter, 0x0, 0xFFFFFFFF);
	PRINTF("val:%X\n", val);
	val = _atomic_val_compare_and_swap(&global_shared_counter, 0x0, 0xFFFFFFFF);
	PRINTF("val:%X\n", val);
	val = _atomic_exchange(&global_shared_counter,0xFFFFFFFF);
	PRINTF("val:%X\n", val);
	_atomic_lock_release(&global_shared_counter);
	return 0;
}


