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

Nan::Persistent<FunctionTemplate> Angle::constructor;

void Angle::Init(Handle<Object> target) {
    Local<FunctionTemplate> tpl =
      Nan::New<FunctionTemplate>(Angle::New);
    constructor.Reset(tpl);
    Local<String> name = Nan::New("S1Angle").ToLocalChecked();

    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->SetClassName(name);

    // Add all prototype methods, getters and setters here.
    Nan::SetPrototypeMethod(tpl, "normalize", Normalize);

    // This has to be last, otherwise the properties won't show up on the
    // object in JavaScript.
    Nan::Set(target, name, tpl->GetFunction());
}

Angle::Angle()
    : ObjectWrap(),
      this_() {}

NAN_METHOD(Angle::New) {
    if (!info.IsConstructCall()) {
        Nan::ThrowError("Use the new operator to create instances of this object.");
        return;
    }

    if (info[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(info[0]);
        void* ptr = ext->Value();
        Angle* ll = static_cast<Angle*>(ptr);
        ll->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
        return;
    }

    if (info.Length() != 2) {
        Nan::ThrowError("(point, point) required");
        return;
    }

    Angle* obj = new Angle();
    obj->Wrap(info.This());

    Handle<Object> a = info[0]->ToObject();
    Handle<Object> b = info[1]->ToObject();

    Local<FunctionTemplate> constructorHandle =
      Nan::New(Point::constructor);
    if (!constructorHandle->HasInstance(a)) {
        Nan::ThrowError("(point, point) required");
        return;
    }

    obj->this_ = S1Angle(
        node::ObjectWrap::Unwrap<Point>(a)->get(),
        node::ObjectWrap::Unwrap<Point>(b)->get());

    info.GetReturnValue().Set(info.This());
}

Handle<Value> Angle::New(S1Angle s1angle) {
    Nan::EscapableHandleScope scope;
    Angle* obj = new Angle();
    obj->this_ = s1angle;
    Handle<Value> ext = Nan::New<External>(obj);
    Local<FunctionTemplate> constructorHandle = Nan::New(constructor);
    Handle<Object> handleObject =
      constructorHandle->GetFunction()->NewInstance(1, &ext);
    return scope.Escape(handleObject);
}

NAN_METHOD(Angle::Normalize) {
    Nan::EscapableHandleScope scope;
    Angle* obj = ObjectWrap::Unwrap<Angle>(info.This());
    obj->this_.Normalize();
    info.GetReturnValue().Set(scope.Escape(info.This()));
}
