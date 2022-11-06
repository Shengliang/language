#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include<vector>
#include<unordered_map>
#include<string>
#include<iostream>

typedef void (*func_type)(void);

struct Container {
   Container() { }
   ~Container() {
      for(auto & e : handles) {
          dlclose(e.second);
      }
   }
   std::unordered_map<std::string, void*> handles;
   std::unordered_map<std::string, std::unordered_map<std::string, func_type> > func_map;

   void* open(std::string libname) {
       auto it = handles.find(libname);
       if (it != handles.end()) {
	  return it->second;
       }
       void* handle = dlopen (libname.c_str(), RTLD_LAZY);
       if (handle == nullptr) {
          return nullptr;
       }
       std::cout << __FUNCTION__ << " " << libname << " " << handle << std::endl;
       handles[libname] = handle;
       return handle;
   }

   func_type load_function(std::string libname, std::string func_name) {
      func_type func = nullptr;
      void * handle = open(libname);
      if (handle == nullptr) {
	  return func;
      }
      auto it_lib = func_map.find(libname);
      if (it_lib != func_map.end()) {
	      auto it_func = it_lib->second.find(func_name);
	      if (it_func != it_lib->second.end()) {
		      func = it_func->second;
	      }
      }

      if (func == nullptr) {
	      std::cout << "dlsym read " << libname << ":" << func_name << std::endl;
        func = (func_type)dlsym(handle, func_name.c_str());
        char *error =dlerror();
        if (error != nullptr)  {
            fputs(error, stderr);
	    return nullptr;
        }
	if (func == nullptr) {
	    return nullptr;
	}
        func_map[libname][func_name] = func;
      }

      std::cout << __FUNCTION__ << " " << libname << ":" << func_name << " func:" << func  << std::endl;
      Dl_info info;
      int rc = dladdr((const void*)func, &info);
      if (rc != 0) {
           printf("rc: %d fname:%s fbase:%p, sname:%s, saddr:%p func:%p\n", rc, info.dli_fname, info.dli_fbase, info.dli_sname, info.dli_saddr, func);
      }
     return func;
   }
  void run(std::string libname, std::string func_name) {
      func_type func = load_function(libname, func_name);
      std::cout << __FUNCTION__ << " " << libname << ":" << func_name << " " << func << std::endl;
      if (func != nullptr)
        (*func)();
  }
};


int main(int argc, char **argv) {
        Container sch;
	if (argc == 3) {
           std::cout << "run " << argv[1] << ":" << argv[2] << std::endl;
           sch.run(argv[1], argv[2]);
	   return 0;
	}
	sch.run("./libalt.so", "x1");
	sch.run("./libfoo.so", "x1");
	sch.run("./libfoo.so", "x2");
	sch.run("./libfoo.so", "x3");
	std::cout << "call 2nd time:" << std::endl;
	sch.run("./libalt.so", "x1");
	sch.run("./libfoo.so", "x1");
	sch.run("./libfoo.so", "x2");
	sch.run("./libfoo.so", "x3");
	return 0;
}
