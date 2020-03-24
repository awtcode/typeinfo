#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <time.h>
#include <emscripten.h>
#include <iostream>

#include    "inc.h"

using namespace std;


class maintypeinfo : public typeinfo {
public:
    virtual ~maintypeinfo() {}
    virtual void virFn(int input) { printf("maintypeinfo.virFn:%d\n", input); }
};

typedef void (*sideyPODfunc)(int input);
int  main(int argc, char *argv[])
{
  typeinfo* temp = new maintypeinfo();
  temp->virFn(argc);
  
  void* lib_handle = dlopen("/output/side.wasm", RTLD_NOW);
  if (!lib_handle) {
    std::cout << "lib_handle is null!\n";
    return -1;
  }

  sideyPODfunc testSide = (sideyPODfunc)dlsym(lib_handle, "testSide");
  std::cout << "->testSide:\n";
  testSide(argc);
  std::cout << "testSide->:\n";
  delete temp;

  return 0;
}