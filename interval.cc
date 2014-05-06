#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s1angle.h"
#include "latlng.h"
#include "point.h"
#include "interval.h"

using namespace v8;

Persistent<FunctionTemplate> Interval::constructor;

void Interval::Init(Handle<Object> target) {
    NanScope();

    constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(Interval::New));
    Local<String> name = String::NewSymbol("Interval");

    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    // Add all prototype methods, getters and setters here.
    NODE_SET_PROTOTYPE_METHOD(constructor, "length", GetLength);
    NODE_SET_PROTOTYPE_METHOD(constructor, "hi", GetHi);
    NODE_SET_PROTOTYPE_METHOD(constructor, "lo", GetLo);
    NODE_SET_PROTOTYPE_METHOD(constructor, "center", GetCenter);
    NODE_SET_PROTOTYPE_METHOD(constructor, "complementLength", GetComplementCenter);

    // This has to be last, otherwise the properties won't show up on the
    // object in JavaScript.
    target->Set(name, constructor->GetFunction());
}

Interval::Interval()
    : ObjectWrap(),
      this_() {}

Handle<Value> Interval::New(const Arguments& args) {
    NanScope();

    if (!args.IsConstructCall()) {
        return NanThrowError("Use the new operator to create instances of this object.");
    }

    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        Interval* ll = static_cast<Interval*>(ptr);
        ll->Wrap(args.This());
        return args.This();
    }

    if (args.Length() != 1) {
        return NanThrowError("(number) required");
    }

    Interval* obj = new Interval();

    obj->Wrap(args.This());

    obj->this_ = S1Interval::FromPoint(args[0]->ToNumber()->Value());

    return args.This();
}

Handle<Value> Interval::New(S1Interval s1angle) {
    NanScope();
    Interval* obj = new Interval();
    obj->this_ = s1angle;
    Handle<Value> ext = External::New(obj);
    Handle<Object> handleObject = constructor->GetFunction()->NewInstance(1, &ext);
    return scope.Close(handleObject);
}

NAN_METHOD(Interval::GetLength) {
    NanScope();
    Interval* obj = ObjectWrap::Unwrap<Interval>(args.This());
    NanReturnValue(NanNew<Number>(obj->this_.GetLength()));
}

NAN_METHOD(Interval::GetCenter) {
    NanScope();
    Interval* obj = ObjectWrap::Unwrap<Interval>(args.This());
    NanReturnValue(NanNew<Number>(obj->this_.GetCenter()));
}

NAN_METHOD(Interval::GetComplementCenter) {
    NanScope();
    Interval* obj = ObjectWrap::Unwrap<Interval>(args.This());
    NanReturnValue(NanNew<Number>(obj->this_.GetComplementCenter()));
}

NAN_METHOD(Interval::GetHi) {
    NanScope();
    Interval* obj = ObjectWrap::Unwrap<Interval>(args.This());
    NanReturnValue(NanNew<Number>(obj->this_.hi()));
}

NAN_METHOD(Interval::GetLo) {
    NanScope();
    Interval* obj = ObjectWrap::Unwrap<Interval>(args.This());
    NanReturnValue(NanNew<Number>(obj->this_.lo()));
}
