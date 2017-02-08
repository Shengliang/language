/*
 * Compile:
 *   gcc zero_size_array.c
 *
 * Run:
 *  ./a.out
 *
 * Output:
 */
#include <stdio.h>
#include <stdint.h>

typedef struct packet_s {
        uint32_t    hdr;
	uint8_t     data[0];
} packet_type;

int main(void) {
	int sz = sizeof(packet_type);
	printf("sizeof(packet_type):=%d\n", sz);
	return 0;
}

