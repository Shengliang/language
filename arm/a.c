#include<stdio.h>
#include<stdint.h>
/* Reference atomic.h in linux kernel header file */
typedef struct {
        uint32_t counter;
} atomic_t;

typedef struct {
        uint64_t counter;
} atomic64_t;


#define atomic_read(v)	(*(volatile uint32_t *)&(v)->counter)
#define atomic_set(v,i)	(((v)->counter) = (i))

// #define ATOMIC

// #define USE_INLINE 1
#ifdef USE_INLINE
#define INLINE inline
#else
#define INLINE 
#endif

INLINE uint32_t atomic_add_and_fetch(uint32_t i, atomic_t *v)
{
	uint32_t tmp;
	uint32_t result;
	__asm__ __volatile__("@ atomic_add_and_fetch begin");

#ifndef ATOMIC
	result = v->counter;
        result = result + i;
        v->counter = result;
#else
	__asm__ __volatile__("@ atomic code\n"
"1:	ldrex	%0, [%3]\n"
"	add	%0, %0, %4\n"
"	strex	%1, %0, [%3]\n"
"	teq	%1, #0\n"
"	bne	1b"
	: "=&r" (result), "=&r" (tmp), "+Qo" (v->counter)
	: "r" (&v->counter), "Ir" (i)
	: "cc");
#endif
	__asm__ __volatile__("@ atomic_add_and_fetch end");

	return result;
}

INLINE uint32_t atomic_fetch_and_add(uint32_t i, atomic_t *v)
{
	uint32_t tmp;
	uint32_t result;
	__asm__ __volatile__("@ atomic_fetch_and_add begin");
#ifndef ATOMIC
	result = v->counter;
        tmp = result + i;
        v->counter = tmp;
#else
	__asm__ __volatile__("@ atomic code\n"
"1:	ldrex	%0, [%3]\n"
"	add	%1, %0, %4\n"
"	strex	%1, %1, [%3]\n"
"	teq	%1, #0\n"
"	bne	1b"
	: "=&r" (result), "=&r" (tmp), "+Qo" (v->counter)
	: "r" (&v->counter), "Ir" (i)
	: "cc");
#endif
	__asm__ __volatile__("@ atomic_fetch_and_add end");
	return result;
}

int main(void) {
   uint32_t x,y,z;
   atomic_t cnt;
   cnt.counter = 0;
   x = 7;
   y = atomic_fetch_and_add(x, &cnt);

   cnt.counter = 0;
   x = 7;
   z = atomic_add_and_fetch(x, &cnt);
   printf("x:%u y:%u z:%u\n", x, y, z);
   return 0;
}

