#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s2cell.h"
#include "s2cellid.h"
#include "s2latlng.h"
#include "s2polygon.h"
#include "latlng.h"
#include "cell.h"
#include "polygon.h"
#include "point.h"
#include "cap.h"
#include "cellid.h"

using namespace v8;

Persistent<FunctionTemplate> Polygon::constructor;

void Polygon::Init(Handle<Object> target) {
    NanScope();

    constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(Polygon::New));
    Local<String> name = String::NewSymbol("Polygon");

    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    // NODE_SET_PROTOTYPE_METHOD(constructor, "approxArea", ApproxArea);

    target->Set(name, constructor->GetFunction());
}

Polygon::Polygon()
    : ObjectWrap() {}

Handle<Value> Polygon::New(const Arguments& args) {
    NanScope();

    if (!args.IsConstructCall()) {
        return NanThrowError("Use the new operator to create instances of this object.");
    }

    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        Polygon* ll = static_cast<Polygon*>(ptr);
        ll->Wrap(args.This());
        return args.This();
    }

    if (args.Length() != 1) {
        return NanThrowError("(latlng) required");
    }

    Polygon* obj = new Polygon();

    obj->Wrap(args.This());

    Handle<Object> ll = args[0]->ToObject();

    return args.This();
}

// NAN_METHOD(Polygon::ApproxArea) {
//     NanScope();
//     Polygon* obj = ObjectWrap::Unwrap<Polygon>(args.This());
//     NanReturnValue(NanNew<Number>(obj->this_.ApproxArea()));
// }
