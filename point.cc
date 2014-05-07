#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"
#include "v8.h"

#include "s2.h"
#include "point.h"

using namespace v8;

Persistent<FunctionTemplate> Point::constructor;

void Point::Init(Handle<Object> target) {
    NanScope();

    constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(Point::New));
    Local<String> name = String::NewSymbol("Point");

    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    NODE_SET_PROTOTYPE_METHOD(constructor, "x", X);
    NODE_SET_PROTOTYPE_METHOD(constructor, "y", Y);
    NODE_SET_PROTOTYPE_METHOD(constructor, "z", Z);

    target->Set(name, constructor->GetFunction());
}

Point::Point()
    : ObjectWrap(),
      this_() {}

Handle<Value> Point::New(const Arguments& args) {
    NanScope();

    if (!args.IsConstructCall()) {
        return NanThrowError("Use the new operator to create instances of this object.");
    }

    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        Point* p = static_cast<Point*>(ptr);
        p->Wrap(args.This());
        return args.This();
    }

    if (args.Length() != 3) {
        return NanThrowError("(number, number, number) required");
    }

    Point* obj = new Point();

    obj->Wrap(args.This());

    obj->this_ = S2Point(
        args[0]->ToNumber()->Value(),
        args[1]->ToNumber()->Value(),
        args[2]->ToNumber()->Value());

    return args.This();
}

Handle<Value> Point::New(S2Point s2cell) {
    NanScope();
    Point* obj = new Point();
    obj->this_ = s2cell;
    Handle<Value> ext = External::New(obj);
    Handle<Object> handleObject = constructor->GetFunction()->NewInstance(1, &ext);
    return scope.Close(handleObject);
}

NAN_METHOD(Point::X) {
    NanScope();
    Point* obj = ObjectWrap::Unwrap<Point>(args.This());
    NanReturnValue(NanNew<Number>(obj->this_.x()));
}

NAN_METHOD(Point::Y) {
    NanScope();
    Point* obj = ObjectWrap::Unwrap<Point>(args.This());
    NanReturnValue(NanNew<Number>(obj->this_.y()));
}

NAN_METHOD(Point::Z) {
    NanScope();
    Point* obj = ObjectWrap::Unwrap<Point>(args.This());
    NanReturnValue(NanNew<Number>(obj->this_.z()));
}
