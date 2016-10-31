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

Nan::Persistent<FunctionTemplate> Interval::constructor;

void Interval::Init(Handle<Object> target) {
    Local<FunctionTemplate> tpl =
      Nan::New<FunctionTemplate>(Interval::New);
    constructor.Reset(tpl);
    Local<String> name = Nan::New("S1Interval").ToLocalChecked();

    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->SetClassName(name);

    Nan::SetPrototypeMethod(tpl, "length", GetLength);
    Nan::SetPrototypeMethod(tpl, "hi", GetHi);
    Nan::SetPrototypeMethod(tpl, "lo", GetLo);
    Nan::SetPrototypeMethod(tpl, "center", GetCenter);
    Nan::SetPrototypeMethod(tpl, "complementLength", GetComplementCenter);
    Nan::SetPrototypeMethod(tpl, "contains", Contains);

    Nan::Set(target, name, tpl->GetFunction());
}

Interval::Interval()
    : ObjectWrap(),
      this_() {}

NAN_METHOD(Interval::New) {
    if (!info.IsConstructCall()) {
        Nan::ThrowError("Use the new operator to create instances of this object.");
        return;
    }

    if (info[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(info[0]);
        void* ptr = ext->Value();
        Interval* ll = static_cast<Interval*>(ptr);
        ll->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
        return;
    }

    if (info.Length() != 1) {
        Nan::ThrowError("(number) required");
        return;
    }

    Interval* obj = new Interval();
    obj->Wrap(info.This());

    obj->this_ = S1Interval::FromPoint(info[0]->ToNumber()->Value());

    info.GetReturnValue().Set(info.This());
}

Handle<Value> Interval::New(S1Interval s1angle) {
    Nan::EscapableHandleScope scope;
    Interval* obj = new Interval();
    obj->this_ = s1angle;
    Handle<Value> ext = Nan::New<External>(obj);
    Local<FunctionTemplate> constructorHandle = Nan::New(constructor);
    Handle<Object> handleObject =
      constructorHandle->GetFunction()->NewInstance(1, &ext);
    return scope.Escape(handleObject);
}

NAN_METHOD(Interval::GetLength) {
    Interval* obj = ObjectWrap::Unwrap<Interval>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.GetLength()));
}

NAN_METHOD(Interval::GetCenter) {
    Interval* obj = ObjectWrap::Unwrap<Interval>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.GetCenter()));
}

NAN_METHOD(Interval::GetComplementCenter) {
    Interval* obj = ObjectWrap::Unwrap<Interval>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.GetComplementCenter()));
}

NAN_METHOD(Interval::GetHi) {
    Interval* obj = ObjectWrap::Unwrap<Interval>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.hi()));
}

NAN_METHOD(Interval::GetLo) {
    Interval* obj = ObjectWrap::Unwrap<Interval>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.lo()));
}

NAN_METHOD(Interval::Contains) {
    Interval* obj = ObjectWrap::Unwrap<Interval>(info.This());
    if (info.Length() != 1) {
        Nan::ThrowError("(number) required");
    }
    if (!info[0]->IsNumber()) {
        Nan::ThrowError("(number) required");
    }
    info.GetReturnValue().Set(Nan::New<Boolean>(obj->this_.Contains(info[0]->ToNumber()->Value())));
}
