#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s2cap.h"
#include "s2latlngrect.h"
#include "point.h"
#include "cap.h"
#include "latlngrect.h"

using namespace v8;

Nan::Persistent<FunctionTemplate> Cap::constructor;

void Cap::Init(Handle<Object> target) {
    Local<FunctionTemplate> tpl =
      Nan::New<FunctionTemplate>(Cap::New);
    constructor.Reset(tpl);
    Local<String> name = Nan::New("S2Cap").ToLocalChecked();

    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->SetClassName(name);

    Nan::SetPrototypeMethod(tpl, "getRectBound", GetRectBound);
    Nan::SetPrototypeMethod(tpl, "intersects", Intersects);
    Nan::SetPrototypeMethod(tpl, "interiorIntersects", InteriorIntersects);
    Nan::SetPrototypeMethod(tpl, "contains", Contains);
    Nan::SetPrototypeMethod(tpl, "complement", Complement);

    Nan::Set(target, name, tpl->GetFunction());
}

Cap::Cap()
    : ObjectWrap(),
      this_() {}

NAN_METHOD(Cap::New) {
    if (!info.IsConstructCall()) {
        Nan::ThrowError("Use the new operator to create instances of this object.");
        return;
    }

    if (info[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(info[0]);
        void* ptr = ext->Value();
        Cap* ll = static_cast<Cap*>(ptr);
        ll->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
        return;
    }

    Cap* obj = new Cap();

    obj->Wrap(info.This());

    if (info.Length() == 2 && info[1]->IsNumber()) {
        Handle<Object> fromObj = info[0]->ToObject();
        Local<FunctionTemplate> constructorHandle =
          Nan::New(Point::constructor);
        if (constructorHandle->HasInstance(fromObj)) {
            S2Point p = node::ObjectWrap::Unwrap<Point>(fromObj)->get();
            obj->this_ = S2Cap::FromAxisHeight(p, info[1]->ToNumber()->Value());
        } else {
            Nan::ThrowError("S2Cap requires arguments (S2Point, number)");
            return;
        }
    } else {
        Nan::ThrowError("S2Cap requires arguments (S2Point, number)");
        return;
    }

    info.GetReturnValue().Set(info.This());
}

Handle<Value> Cap::New(S2Cap s2cap) {
    Nan::EscapableHandleScope scope;
    Cap* obj = new Cap();
    obj->this_ = s2cap;
    Handle<Value> ext = Nan::New<External>(obj);
    Local<FunctionTemplate> constructorHandle = Nan::New(constructor);
    Handle<Object> handleObject =
      constructorHandle->GetFunction()->NewInstance(1, &ext);
    return scope.Escape(handleObject);
}

NAN_METHOD(Cap::GetRectBound) {
    Cap* cap = node::ObjectWrap::Unwrap<Cap>(info.This());
    info.GetReturnValue().Set(LatLngRect::New(cap->this_.GetRectBound()));
}

NAN_METHOD(Cap::Intersects) {
    Cap* cap = node::ObjectWrap::Unwrap<Cap>(info.This());
    S2Cap other = node::ObjectWrap::Unwrap<Cap>(info[0]->ToObject())->get();
    info.GetReturnValue().Set(Nan::New<Boolean>(cap->this_.Intersects(other)));
}

NAN_METHOD(Cap::InteriorIntersects) {
    Cap* cap = node::ObjectWrap::Unwrap<Cap>(info.This());
    S2Cap other = node::ObjectWrap::Unwrap<Cap>(info[0]->ToObject())->get();
    info.GetReturnValue().Set(Nan::New<Boolean>(cap->this_.Intersects(other)));
}

NAN_METHOD(Cap::Contains) {
    Cap* cap = node::ObjectWrap::Unwrap<Cap>(info.This());
    S2Cap other = node::ObjectWrap::Unwrap<Cap>(info[0]->ToObject())->get();
    info.GetReturnValue().Set(Nan::New<Boolean>(cap->this_.Contains(other)));
}

NAN_METHOD(Cap::Complement) {
    Cap* cap = node::ObjectWrap::Unwrap<Cap>(info.This());
    info.GetReturnValue().Set(Cap::New(cap->this_.Complement()));
}
