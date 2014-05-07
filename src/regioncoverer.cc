#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s2cell.h"
#include "s2cellid.h"
#include "s2latlng.h"
#include "s2regioncoverer.h"
#include "latlng.h"
#include "cell.h"
#include "point.h"
#include "regioncoverer.h"
#include "cap.h"
#include "cellid.h"

using namespace v8;

Persistent<FunctionTemplate> RegionCoverer::constructor;

void RegionCoverer::Init(Handle<Object> target) {
    NanScope();

    constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(RegionCoverer::New));
    Local<String> name = String::NewSymbol("S2RegionCoverer");

    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    // NODE_SET_PROTOTYPE_METHOD(constructor, "getCenter", GetCenter);

    target->Set(name, constructor->GetFunction());
}

RegionCoverer::RegionCoverer()
    : ObjectWrap(),
      this_() {}

Handle<Value> RegionCoverer::New(const Arguments& args) {
    NanScope();

    if (!args.IsConstructCall()) {
        return NanThrowError("Use the new operator to create instances of this object.");
    }

    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        RegionCoverer* ll = static_cast<RegionCoverer*>(ptr);
        ll->Wrap(args.This());
        return args.This();
    }

    RegionCoverer* obj = new RegionCoverer();

    obj->Wrap(args.This());

    Handle<Object> ll = args[0]->ToObject();

    S2RegionCoverer cov;

    obj->this_ = cov;

    return args.This();
}

Handle<Value> RegionCoverer::New(S2RegionCoverer rc) {
    NanScope();
    RegionCoverer* obj = new RegionCoverer();
    obj->this_ = rc;
    Handle<Value> ext = External::New(obj);
    Handle<Object> handleObject = constructor->GetFunction()->NewInstance(1, &ext);
    return scope.Close(handleObject);
}
