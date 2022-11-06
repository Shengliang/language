#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

void run(char* libname, char *func_name) {
    void *handle;
    void (*func)(void);
    char *error;

    handle = dlopen (libname, RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(1);
    }

    func = dlsym(handle, func_name);
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }

    Dl_info info;
    int rc = dladdr(func, &info);
    if (rc != 0) {
	    printf("rc: %d fname:%s fbase:%p, sname:%s, saddr:%p func:%p\n", rc, info.dli_fname, info.dli_fbase, info.dli_sname, info.dli_saddr, func);
    }

    if (func != NULL)
      (*func)();
    dlclose(handle);
}

int main(int argc, char **argv) {
	run("./libalt.so", "x1");
	run("./libfoo.so", "x1");
	run("./libfoo.so", "x2");
	run("./libfoo.so", "x3");
	return 0;
}
