#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s2latlng.h"
#include "latlng.h"
#include "point.h"

using namespace v8;

Nan::Persistent<FunctionTemplate> LatLng::constructor;

void LatLng::Init(Handle<Object> target) {
    Local<FunctionTemplate> tpl =
      Nan::New<FunctionTemplate>(LatLng::New);
  	constructor.Reset(tpl);
    Local<String> name = Nan::New("S2LatLng").ToLocalChecked();

    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->SetClassName(name);

    // Add all prototype methods, getters and setters here.
    Nan::SetPrototypeMethod(tpl, "normalized", Normalized);
    Nan::SetPrototypeMethod(tpl, "isValid", IsValid);
    Nan::SetPrototypeMethod(tpl, "toPoint", ToPoint);
    Nan::SetPrototypeMethod(tpl, "distance", Distance);
    Nan::SetPrototypeMethod(tpl, "toString", ToString);

    Local<ObjectTemplate> proto = tpl->PrototypeTemplate();
    Nan::SetAccessor(proto, Nan::New("lat").ToLocalChecked(), Lat);
    Nan::SetAccessor(proto, Nan::New("lng").ToLocalChecked(), Lng);

    // This has to be last, otherwise the properties won't show up on the
    // object in JavaScript.
    Nan::Set(target, name, tpl->GetFunction());
}

LatLng::LatLng()
    : ObjectWrap(),
      this_() {}

NAN_METHOD(LatLng::New) {
    if (!info.IsConstructCall()) {
        Nan::ThrowError("Use the new operator to create instances of this object.");
        return;
    }

    if (info[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(info[0]);
        void* ptr = ext->Value();
        LatLng* ll = static_cast<LatLng*>(ptr);
        ll->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
        return;
    }

    LatLng* obj = new LatLng();
    obj->Wrap(info.This());

    if (info.Length() == 2) {
        if (info[0]->IsNumber() &&
            info[1]->IsNumber()) {
            obj->this_ = S2LatLng::FromDegrees(
                info[0]->ToNumber()->Value(),
                info[1]->ToNumber()->Value());
        }
    } else if (info.Length() == 1) {
        Handle<Object> fromObj = info[0]->ToObject();
        Local<FunctionTemplate> constructorHandle =
          Nan::New(Point::constructor);
        if (constructorHandle->HasInstance(fromObj)) {
            S2Point p = node::ObjectWrap::Unwrap<Point>(fromObj)->get();
            obj->this_ = S2LatLng(p);
        } else {
            Nan::ThrowError("Use the new operator to create instances of this object.");
            return;
        }
    }

    info.GetReturnValue().Set(info.This());
}

Handle<Value> LatLng::New(S2LatLng s2latlng) {
    Nan::EscapableHandleScope scope;
    LatLng* obj = new LatLng();
    obj->this_ = s2latlng;
    Handle<Value> ext = Nan::New<External>(obj);
    Local<FunctionTemplate> constructorHandle = Nan::New(constructor);
    Handle<Object> handleObject =
      constructorHandle->GetFunction()->NewInstance(1, &ext);
    return scope.Escape(handleObject);
}

NAN_GETTER(LatLng::Lat) {
    LatLng* obj = ObjectWrap::Unwrap<LatLng>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.lat().degrees()));
}

NAN_GETTER(LatLng::Lng) {
    LatLng* obj = ObjectWrap::Unwrap<LatLng>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.lng().degrees()));
}

NAN_METHOD(LatLng::IsValid) {
    LatLng* obj = ObjectWrap::Unwrap<LatLng>(info.This());
    info.GetReturnValue().Set(Nan::New<Boolean>(obj->this_.is_valid()));
}

NAN_METHOD(LatLng::Normalized) {
    Nan::EscapableHandleScope scope;
    LatLng* obj = ObjectWrap::Unwrap<LatLng>(info.This());
    info.GetReturnValue().Set(scope.Escape(LatLng::New(obj->this_.Normalized())));
}

NAN_METHOD(LatLng::ToPoint) {
    Nan::EscapableHandleScope scope;
    LatLng* obj = ObjectWrap::Unwrap<LatLng>(info.This());
    info.GetReturnValue().Set(scope.Escape(Point::New(obj->this_.ToPoint())));
}

NAN_METHOD(LatLng::Distance) {
    LatLng* latlng = node::ObjectWrap::Unwrap<LatLng>(info.This());
    S2LatLng other = node::ObjectWrap::Unwrap<LatLng>(info[0]->ToObject())->get();
    info.GetReturnValue().Set(Nan::New<Number>(latlng->this_.GetDistance(other).degrees()));
}

NAN_METHOD(LatLng::ToString) {
    LatLng* latlng = node::ObjectWrap::Unwrap<LatLng>(info.This());
    info.GetReturnValue().Set(Nan::New(latlng->this_.ToStringInDegrees().c_str()).ToLocalChecked());
}
