// http://www.goldsborough.me/c/low-level/kernel/2016/08/29/16-48-53-the_-ld_preload-_trick/

#define _GNU_SOURCE
#include <dlfcn.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <err.h>

#include <errno.h>

#include <unistd.h>

#include <fcntl.h>

#include <libaio.h>


typedef ssize_t (*real_io_submit_t)(io_context_t ctx_id, long nr, struct iocb **iocbpp);


int io_submit(io_context_t ctx_id, long nr, struct iocb **iocbpp) {

    printf("Intercepted io_submit\n");

    // To call the real libc io_submit, use dlsym with RTLD_NEXT param

    return ((real_io_submit_t)dlsym(RTLD_NEXT, "io_submit"))(ctx_id, nr, iocbpp);

}

 


