#include <emscripten/bind.h>
#include <emscripten/emscripten.h>
#include <stdio.h>
#include <map>
using namespace emscripten;
using namespace std;

float lerp(int instr)
{
    char *str = reinterpret_cast<char *>(instr);
    EM_ASM({
        console.log('I received: ' + UTF8ToString($0));
    },
           str);
}

std::string getString(int addr)
{
    return std::string(reinterpret_cast<char *>(instr));
}


EMSCRIPTEN_BINDINGS(my_module)
{
    function("lerp", &lerp, allow_raw_pointers());
}