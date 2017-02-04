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
 */
#include <stdio.h>

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

int main(void) {
        IMG_HDR hdr;
        hdr.signiture.d8[0] = 0x61;
        hdr.signiture.d8[1] = 0x62;
        hdr.signiture.d8[2] = 0x63;
        hdr.signiture.d8[3] = 0x64;

        printf("d32=0x%04X.\n", hdr.signiture.d32);
	for(int i=0; i<4; i++) {
		char ch = hdr.signiture.d8[i];
		printf("byte[%d]=%c %02X\n", i, ch, ch);
	}
        if(hdr.signiture.d32 == 0x64636261)
		printf("LE ENDIAN\n");
        else
		printf("BIG ENDIAN\n");
	return 0;
}

