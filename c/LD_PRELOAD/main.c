// https://oxnz.github.io/2016/10/13/linux-aio/
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

#ifdef TEST_WRAPPER
size_t __real_io_submit(io_context_t ctx_id, long nr, struct iocb **iocbpp);
size_t __wrap_io_submit(io_context_t ctx_id, long nr, struct iocb **iocbpp)
{
        printf("HERE: %s", __FUNCTION__);
        return __real_io_submit(ctx_id, nr, iocbpp);
}
#endif

int main(void) {

	io_context_t ctx;

	struct iocb iocb;

	struct iocb * iocbs[1];

	struct io_event events[1];

	struct timespec timeout;

	int fd;

	fd = open("/tmp/test", O_WRONLY | O_CREAT);

	if (fd < 0) err(1, "open");



	memset(&ctx, 0, sizeof(ctx));

	if (io_setup(10, &ctx) != 0) err(1, "io_setup");


	const char *msg = "hello\n";

	io_prep_pwrite(&iocb, fd, (void *)msg, strlen(msg), 0);

	iocb.data = (void *)msg;


	iocbs[0] = &iocb;


	if (io_submit(ctx, 1, iocbs) != 1) {

		io_destroy(ctx);

		err(1, "io_submit");

	}



	while (1) {

		timeout.tv_sec = 0;

		timeout.tv_nsec = 500000000;

		if (io_getevents(ctx, 0, 1, events, &timeout) == 1) {

			close(fd);

			break;

		}

		printf("not done yet\n");

		sleep(1);

	}

	io_destroy(ctx);



	return 0;

}
