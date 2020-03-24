#include <string>
#include <stdio.h>
#include <emscripten.h>
#include <iostream>

#include "inc.h"
class sidetypeinfo : public typeinfo {
public:
    virtual ~sidetypeinfo() {}
    virtual void virFn(int input) { printf("sidetypeinfo.virFn:%d\n", input);}
};

EMSCRIPTEN_KEEPALIVE extern "C" void testSide(int input) {
    printf("testSide+:\n");
    typeinfo* temp = new sidetypeinfo();
    temp->virFn(input);
    delete temp;
}