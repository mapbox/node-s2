#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"
#include "v8.h"

#include "s2.h"
#include "point.h"

using namespace v8;

Nan::Persistent<FunctionTemplate> Point::constructor;

void Point::Init(Handle<Object> target) {
    Local<FunctionTemplate> tpl =
      Nan::New<FunctionTemplate>(Point::New);
    constructor.Reset(tpl);
    Local<String> name = Nan::New("S2Point").ToLocalChecked();

    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->SetClassName(name);

    Nan::SetPrototypeMethod(tpl, "x", X);
    Nan::SetPrototypeMethod(tpl, "y", Y);
    Nan::SetPrototypeMethod(tpl, "z", Z);

    Nan::Set(target, name, tpl->GetFunction());
}

Point::Point()
    : ObjectWrap(),
      this_() {}

NAN_METHOD(Point::New) {
    if (!info.IsConstructCall()) {
        Nan::ThrowError("Use the new operator to create instances of this object.");
        return;
    }

    if (info[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(info[0]);
        void* ptr = ext->Value();
        Point* p = static_cast<Point*>(ptr);
        p->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
        return;
    }

    if (info.Length() != 3) {
        Nan::ThrowError("(number, number, number) required");
        return;
    }

    Point* obj = new Point();
    obj->Wrap(info.This());

    obj->this_ = S2Point(
        info[0]->ToNumber()->Value(),
        info[1]->ToNumber()->Value(),
        info[2]->ToNumber()->Value());

    info.GetReturnValue().Set(info.This());
}

Handle<Value> Point::New(S2Point s2cell) {
    Nan::EscapableHandleScope scope;
    Point* obj = new Point();
    obj->this_ = s2cell;
    Handle<Value> ext = Nan::New<External>(obj);
    Local<FunctionTemplate> constructorHandle = Nan::New(constructor);
    Handle<Object> handleObject =
      constructorHandle->GetFunction()->NewInstance(1, &ext);
    return scope.Escape(handleObject);
}

NAN_METHOD(Point::X) {
    Point* obj = ObjectWrap::Unwrap<Point>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.x()));
}

NAN_METHOD(Point::Y) {
    Point* obj = ObjectWrap::Unwrap<Point>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.y()));
}

NAN_METHOD(Point::Z) {
    Point* obj = ObjectWrap::Unwrap<Point>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.z()));
}
