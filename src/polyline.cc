#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s2polyline.h"
#include "s2latlngrect.h"
#include "cap.h"
#include "latlngrect.h"

using namespace v8;

Persistent<FunctionTemplate> Polyline::constructor;

void Polyline::Init(Handle<Object> target) {
    NanScope();

    constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(Polyline::New));
    Local<String> name = String::NewSymbol("S2Polyline");

    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    NODE_SET_PROTOTYPE_METHOD(constructor, "getRectBound", GetRectBound);
    NODE_SET_PROTOTYPE_METHOD(constructor, "intersects", Intersects);
    NODE_SET_PROTOTYPE_METHOD(constructor, "contains", Contains);
    NODE_SET_PROTOTYPE_METHOD(constructor, "complement", Complement);

    target->Set(name, constructor->GetFunction());
}

Polyline::Polyline()
    : ObjectWrap(),
      this_() {}

Handle<Value> Polyline::New(const Arguments& args) {
    NanScope();

    if (!args.IsConstructCall()) {
        return NanThrowError("Use the new operator to create instances of this object.");
    }

    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        Polyline* ll = static_cast<Polyline*>(ptr);
        ll->Wrap(args.This());
        return args.This();
    }


    Polyline* obj = new Polyline();

    obj->Wrap(args.This());

    obj->this_ = S2Polyline();

    if (args.Length() == 0) {
    }

    return args.This();
}

Handle<Value> Polyline::New(S2Polyline s2cap) {
    NanScope();
    Polyline* obj = new Polyline();
    obj->this_ = s2cap;
    Handle<Value> ext = External::New(obj);
    Handle<Object> handleObject = constructor->GetFunction()->NewInstance(1, &ext);
    return scope.Close(handleObject);
}

// NAN_METHOD(Polyline::GetRectBound) {
//     NanScope();
//     Polyline* cap = node::ObjectWrap::Unwrap<Polyline>(args.This());
//     NanReturnValue(LatLngRect::New(cap->this_.GetRectBound()));
// }
