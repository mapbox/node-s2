#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s1angle.h"
#include "latlng.h"
#include "point.h"
#include "angle.h"

using namespace v8;

Persistent<FunctionTemplate> Angle::constructor;

void Angle::Init(Handle<Object> target) {
    NanScope();

    constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(Angle::New));
    Local<String> name = String::NewSymbol("Angle");

    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    // Add all prototype methods, getters and setters here.
    // NODE_SET_PROTOTYPE_METHOD(constructor, "lat", Lat);

    // This has to be last, otherwise the properties won't show up on the
    // object in JavaScript.
    target->Set(name, constructor->GetFunction());
}

Angle::Angle()
    : ObjectWrap(),
      this_() {}

Handle<Value> Angle::New(const Arguments& args) {
    NanScope();

    if (!args.IsConstructCall()) {
        return NanThrowError("Use the new operator to create instances of this object.");
    }

    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        Angle* ll = static_cast<Angle*>(ptr);
        ll->Wrap(args.This());
        return args.This();
    }

    if (args.Length() != 2) {
        return NanThrowError("(point, point) required");
    }

    Angle* obj = new Angle();

    obj->Wrap(args.This());

    obj->this_ = S1Angle(
        node::ObjectWrap::Unwrap<Point>(args[0]->ToObject())->get(),
        node::ObjectWrap::Unwrap<Point>(args[1]->ToObject())->get());

    return args.This();
}

Handle<Value> Angle::New(S1Angle s1angle) {
    NanScope();
    Angle* obj = new Angle();
    obj->this_ = s1angle;
    Handle<Value> ext = External::New(obj);
    Handle<Object> handleObject = constructor->GetFunction()->NewInstance(1, &ext);
    return scope.Close(handleObject);
}

// NAN_METHOD(Angle::Lat) {
//     NanScope();
//     Angle* obj = ObjectWrap::Unwrap<Angle>(args.This());
//     NanReturnValue(NanNew<Number>(obj->this_.lat().degrees()));
// }
