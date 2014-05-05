#include <node.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s2latlng.h"
#include "s2cellid.h"
#include "s2cell.h"
#include "s2polygon.h"
#include "s2loop.h"
#include "s2polygonbuilder.h"
#include "s2regioncoverer.h"

using namespace v8;

Handle<Value> GetCover(const Arguments& args) {
    HandleScope scope;
    scoped_ptr<S2PolygonBuilder> builder(
        new S2PolygonBuilder(
            S2PolygonBuilderOptions::DIRECTED_XOR()));

    if (args.Length() < 1) {
        return ThrowException(Exception::TypeError(
            String::New("(array) required")));
    }

    // Array points = args[0]->ToArray();

    return scope.Close(Integer::New(0));
}

void RegisterModule(Handle<Object> target) {
    LatLng::Init(target);
    target->Set(String::NewSymbol("getCover"),
        FunctionTemplate::New(GetCover)->GetFunction());
}

NODE_MODULE(_s2, RegisterModule);
