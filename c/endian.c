#include <stdio.h>

typedef unsigned int uint32_t;

typedef struct IMG_HDR_TAG {

        char        sign[4];   //"SCIM"

        uint32_t    len;

        uint32_t    offset;

        uint32_t    crc32;

} IMG_HDR;

int main(void)
{

        IMG_HDR hdr;

        uint32_t*p = (uint32_t*)hdr.sign;

        hdr.sign[0] = 'S';

        hdr.sign[1] = 'C';

        hdr.sign[2] = 'I';

        hdr.sign[3] = 'M';

        printf("%04X\n", *p);

        if(*p==0x4D494353) printf("LE ENDIAN\n");

        else printf("BIG ENDIAN\n");

	return 0;
}

