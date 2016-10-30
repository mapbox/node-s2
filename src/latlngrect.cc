#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s2cell.h"
#include "s2latlngrect.h"
#include "latlngrect.h"
#include "latlng.h"
#include "cell.h"
#include "cap.h"
#include "cellid.h"

using namespace v8;

Nan::Persistent<FunctionTemplate> LatLngRect::constructor;

void LatLngRect::Init(Handle<Object> target) {
    Local<FunctionTemplate> tpl =
      Nan::New<FunctionTemplate>(LatLngRect::New);
    constructor.Reset(tpl);
    Local<String> name = Nan::New("S2LatLngRect").ToLocalChecked();

    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->SetClassName(name);

    Nan::SetPrototypeMethod(tpl, "center", GetCenter);
    Nan::SetPrototypeMethod(tpl, "size", GetSize);
    Nan::SetPrototypeMethod(tpl, "area", GetArea);
    Nan::SetPrototypeMethod(tpl, "getVertex", GetVertex);
    Nan::SetPrototypeMethod(tpl, "getCapBound", GetCapBound);
    Nan::SetPrototypeMethod(tpl, "contains", Contains);
    Nan::SetPrototypeMethod(tpl, "isValid", IsValid);
    Nan::SetPrototypeMethod(tpl, "isEmpty", IsEmpty);
    Nan::SetPrototypeMethod(tpl, "isPoint", IsPoint);
    Nan::SetPrototypeMethod(tpl, "union", Union);
    Nan::SetPrototypeMethod(tpl, "intersection", Intersection);
    Nan::SetPrototypeMethod(tpl, "approxEquals", ApproxEquals);

    Nan::Set(target, name, tpl->GetFunction());
}

LatLngRect::LatLngRect()
    : ObjectWrap(),
      this_() {}

NAN_METHOD(LatLngRect::New) {
    if (!info.IsConstructCall()) {
      Nan::ThrowError("Use the new operator to create instances of this object.");
      return;
    }

    if (info[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(info[0]);
        void* ptr = ext->Value();
        LatLngRect* ll = static_cast<LatLngRect*>(ptr);
        ll->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
        return;
    }

    if (info.Length() == 0) {
        Nan::ThrowError("(latlng) or (latlng, latlng) required");
        return;
    }

    LatLngRect* obj = new LatLngRect();

    obj->Wrap(info.This());

    Handle<Object> ll = info[0]->ToObject();

    Local<FunctionTemplate> constructorHandle =
      Nan::New(LatLng::constructor);
    if (!constructorHandle->HasInstance(ll)) {
        Nan::ThrowError("(latlng) required");
        return;
    }

    if (info.Length() == 1) {
        obj->this_ = S2LatLngRect(
            S2LatLngRect::FromPoint(node::ObjectWrap::Unwrap<LatLng>(ll)->get()));
    } else if (info.Length() == 2) {
        Handle<Object> llb = info[1]->ToObject();

        if (!constructorHandle->HasInstance(llb)) {
            Nan::ThrowError("(latlng, latlng) required");
            return;
        }

        obj->this_ = S2LatLngRect(
            S2LatLngRect::FromPointPair(
                node::ObjectWrap::Unwrap<LatLng>(ll)->get(),
                node::ObjectWrap::Unwrap<LatLng>(llb)->get()));
    }

    info.GetReturnValue().Set(info.This());
}

Handle<Value> LatLngRect::New(S2LatLngRect s2cell) {
    Nan::EscapableHandleScope scope;
    LatLngRect* obj = new LatLngRect();
    obj->this_ = s2cell;
    Handle<Value> ext = Nan::New<External>(obj);
    Local<FunctionTemplate> constructorHandle = Nan::New(constructor);
    Handle<Object> handleObject =
      constructorHandle->GetFunction()->NewInstance(1, &ext);
    return scope.Escape(handleObject);
}

NAN_METHOD(LatLngRect::GetCenter) {
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(info.This());
    info.GetReturnValue().Set(LatLng::New(latlngrect->this_.GetCenter()));
}

NAN_METHOD(LatLngRect::GetCapBound) {
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(info.This());
    info.GetReturnValue().Set(Cap::New(latlngrect->this_.GetCapBound()));
}

NAN_METHOD(LatLngRect::GetSize) {
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(info.This());
    info.GetReturnValue().Set(LatLng::New(latlngrect->this_.GetSize()));
}

NAN_METHOD(LatLngRect::GetArea) {
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(latlngrect->this_.Area()));
}

NAN_METHOD(LatLngRect::GetVertex) {
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(info.This());
    info.GetReturnValue().Set(LatLng::New(latlngrect->this_.GetVertex(info[0]->ToNumber()->Value())));
}

NAN_METHOD(LatLngRect::Contains) {
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(info.This());
    S2LatLng other = node::ObjectWrap::Unwrap<LatLng>(info[0]->ToObject())->get();
    info.GetReturnValue().Set(Nan::New<Boolean>(latlngrect->this_.Contains(other)));
}

NAN_METHOD(LatLngRect::IsValid) {
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(info.This());
    info.GetReturnValue().Set(Nan::New<Boolean>(latlngrect->this_.is_valid()));
}

NAN_METHOD(LatLngRect::IsEmpty) {
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(info.This());
    info.GetReturnValue().Set(Nan::New<Boolean>(latlngrect->this_.is_empty()));
}

NAN_METHOD(LatLngRect::IsPoint) {
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(info.This());
    info.GetReturnValue().Set(Nan::New<Boolean>(latlngrect->this_.is_point()));
}

NAN_METHOD(LatLngRect::Union) {
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(info.This());
    S2LatLngRect other = node::ObjectWrap::Unwrap<LatLngRect>(info[0]->ToObject())->get();
    info.GetReturnValue().Set(LatLngRect::New(latlngrect->this_.Union(other)));
}

NAN_METHOD(LatLngRect::Intersection) {
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(info.This());
    S2LatLngRect other = node::ObjectWrap::Unwrap<LatLngRect>(info[0]->ToObject())->get();
    info.GetReturnValue().Set(LatLngRect::New(latlngrect->this_.Intersection(other)));
}

NAN_METHOD(LatLngRect::ApproxEquals) {
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(info.This());
    S2LatLngRect other = node::ObjectWrap::Unwrap<LatLngRect>(info[0]->ToObject())->get();
    info.GetReturnValue().Set(Nan::New<Boolean>(latlngrect->this_.ApproxEquals(other)));
}
