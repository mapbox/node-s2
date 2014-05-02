#include <node.h>

// C standard library
#include <cstdlib>
#include <ctime>

using namespace v8;

void RegisterModule(Handle<Object> target) {
}

NODE_MODULE(modulename, RegisterModule);
