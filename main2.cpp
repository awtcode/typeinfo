#include <stdio.h>
#include "inc.h"

void inc::setFnPtr(VOID_FNPTR a) {
  fnPtr = a;
}

VOID_FNPTR inc::getFnPtr() {
  return fnPtr;
}
static VOID_FNPTR gCurFnptr = nullptr;
void fnA() { printf("fnA\n"); }
void fnB() { printf("fnB\n"); }

struct cmdStruct
{
    const char* fnname;
    VOID_FNPTR fnptr;
};

static cmdStruct cmdsArray[] = { { "fnA", fnA }, { "fnB", fnB } };

void init(inc& input, int i) {
  input.setFnPtr(cmdsArray[i].fnptr);
  if (i == 0)
    gCurFnptr = fnA;  
  else
  {
    gCurFnptr = fnB;
  }
  gCurFnptr();

}
