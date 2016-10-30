#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s2cell.h"
#include "s2cellid.h"
#include "s2latlng.h"
#include "latlng.h"
#include "point.h"
#include "cellid.h"
#include "strutil.h"

using namespace v8;

Nan::Persistent<FunctionTemplate> CellId::constructor;

void CellId::Init(Handle<Object> target) {
    Local<FunctionTemplate> tpl =
      Nan::New<FunctionTemplate>(CellId::New);
    constructor.Reset(tpl);
    Local<String> name = Nan::New("S2CellId").ToLocalChecked();

    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->SetClassName(name);

    Nan::SetPrototypeMethod(tpl, "level", Level);
    Nan::SetPrototypeMethod(tpl, "toToken", ToToken);
    Nan::SetPrototypeMethod(tpl, "fromToken", FromToken);
    Nan::SetPrototypeMethod(tpl, "toPoint", ToPoint);
    Nan::SetPrototypeMethod(tpl, "toString", ToString);
    Nan::SetPrototypeMethod(tpl, "toLatLng", ToLatLng);
    Nan::SetPrototypeMethod(tpl, "parent", Parent);
    Nan::SetPrototypeMethod(tpl, "prev", Prev);
    Nan::SetPrototypeMethod(tpl, "next", Next);
    Nan::SetPrototypeMethod(tpl, "isFace", IsFace);
    Nan::SetPrototypeMethod(tpl, "rangeMin", RangeMin);
    Nan::SetPrototypeMethod(tpl, "rangeMax", RangeMax);
    Nan::SetPrototypeMethod(tpl, "id", Id);
    Nan::SetPrototypeMethod(tpl, "child", Child);
    Nan::SetPrototypeMethod(tpl, "contains", Contains);

    Nan::Set(target, name, tpl->GetFunction());
}

CellId::CellId()
    : ObjectWrap(),
      this_() {}

NAN_METHOD(CellId::New) {
    if (!info.IsConstructCall()) {
        Nan::ThrowError("Use the new operator to create instances of this object.");
        return;
    }

    if (info[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(info[0]);
        void* ptr = ext->Value();
        CellId* cellid = static_cast<CellId*>(ptr);
        cellid->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
        return;
    }

    CellId* obj = new CellId();

    obj->Wrap(info.This());

    if (info.Length() == 1) {
        Handle<Object> fromObj = info[0]->ToObject();
        Local<FunctionTemplate> constructorHandle =
          Nan::New(Point::constructor);
        Local<FunctionTemplate> constructorHandle2 =
          Nan::New(LatLng::constructor);
        if (constructorHandle->HasInstance(fromObj)) {
            S2Point p = node::ObjectWrap::Unwrap<Point>(fromObj)->get();
            obj->this_ = S2CellId::FromPoint(p);
        } else if (constructorHandle2->HasInstance(fromObj)) {
            S2LatLng ll = node::ObjectWrap::Unwrap<LatLng>(fromObj)->get();
            obj->this_ = S2CellId::FromLatLng(ll);
        } else if (info[0]->IsString()) {
            std::string strnum {*Nan::Utf8String(info[0])};
            obj->this_ = S2CellId(ParseLeadingUInt64Value(strnum, 0));
        } else {
            Nan::ThrowError("Invalid input");
            return;
        }
    } else {
        obj->this_ = S2CellId();
    }

    info.GetReturnValue().Set(info.This());
}

Handle<Value> CellId::New(S2CellId s2cellid) {
    Nan::EscapableHandleScope scope;
    CellId* obj = new CellId();
    obj->this_ = s2cellid;
    Handle<Value> ext = Nan::New<External>(obj);
    Local<FunctionTemplate> constructorHandle = Nan::New(constructor);
    Handle<Object> handleObject =
      constructorHandle->GetFunction()->NewInstance(1, &ext);
    return scope.Escape(handleObject);
}

NAN_METHOD(CellId::FromToken) {
    if (info.Length() != 1 || !info[0]->IsString()) {
        Nan::ThrowError("(str) required");
        return;
    }
    std::string strtoken {*Nan::Utf8String(info[0])};
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(info.This());
    obj->this_ = S2CellId::FromToken(strtoken);
    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(CellId::Level) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.level()));
}

NAN_METHOD(CellId::ToToken) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(info.This());
    info.GetReturnValue().Set(
      Nan::New(obj->this_.ToToken().c_str()).ToLocalChecked());
}

NAN_METHOD(CellId::ToString) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(info.This());
    info.GetReturnValue().Set(
      Nan::New(obj->this_.ToString().c_str()).ToLocalChecked());
}

NAN_METHOD(CellId::ToPoint) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(info.This());
    info.GetReturnValue().Set(Point::New(obj->this_.ToPoint()));
}

NAN_METHOD(CellId::Parent) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(info.This());
    if (info.Length() == 1 && info[0]->IsNumber()) {
        info.GetReturnValue().Set(CellId::New(obj->this_.parent(info[0]->ToNumber()->Value())));
    } else {
        info.GetReturnValue().Set(CellId::New(obj->this_.parent()));
    }
}
NAN_METHOD(CellId::Prev) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(info.This());
    info.GetReturnValue().Set(CellId::New(obj->this_.prev()));
}

NAN_METHOD(CellId::Next) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(info.This());
    info.GetReturnValue().Set(CellId::New(obj->this_.next()));
}

NAN_METHOD(CellId::IsFace) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(info.This());
    info.GetReturnValue().Set(Nan::New<Boolean>(obj->this_.is_face()));
}

NAN_METHOD(CellId::RangeMin) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(info.This());
    info.GetReturnValue().Set(CellId::New(obj->this_.range_min()));
}

NAN_METHOD(CellId::RangeMax) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(info.This());
    info.GetReturnValue().Set(CellId::New(obj->this_.range_max()));
}

NAN_METHOD(CellId::Contains) {
    CellId* cellid = node::ObjectWrap::Unwrap<CellId>(info.This());
    S2CellId other = node::ObjectWrap::Unwrap<CellId>(info[0]->ToObject())->get();
    info.GetReturnValue().Set(Nan::New<Boolean>(cellid->this_.contains(other)));
}

NAN_METHOD(CellId::Id) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.id()));
}

NAN_METHOD(CellId::Child) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(info.This());
    if (info.Length() != 1) {
        Nan::ThrowError("(number) required");
        return;
    }
    info.GetReturnValue().Set(CellId::New(obj->this_.child(info[0]->ToNumber()->Value())));
}

NAN_METHOD(CellId::ToLatLng) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(info.This());
    info.GetReturnValue().Set(LatLng::New(obj->this_.ToLatLng()));
}
