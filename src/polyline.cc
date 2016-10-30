#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "angle.h"
#include "cap.h"
#include "cell.h"
#include "latlng.h"
#include "latlngrect.h"
#include "point.h"
#include "polyline.h"
#include "s2.h"
#include "s1angle.h"
#include "s2cell.h"
#include "s2latlngrect.h"
#include "s2polyline.h"

#include <string>
#include <vector>

using namespace v8;

Nan::Persistent<FunctionTemplate> Polyline::constructor;

void Polyline::Init(Handle<Object> target) {
    Local<FunctionTemplate> tpl =
      Nan::New<FunctionTemplate>(Polyline::New);
    constructor.Reset(tpl);
    Local<String> name = Nan::New("S2Polyline").ToLocalChecked();

    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->SetClassName(name);

    Nan::SetPrototypeMethod(tpl, "getCapBound", GetCapBound);
    Nan::SetPrototypeMethod(tpl, "getLength", GetLength);
    Nan::SetPrototypeMethod(tpl, "getCentroid", GetCentroid);
    Nan::SetPrototypeMethod(tpl, "interpolate", Interpolate);
    Nan::SetPrototypeMethod(tpl, "getSuffix", GetSuffix);
    Nan::SetPrototypeMethod(tpl, "intersects", Intersects);
    Nan::SetPrototypeMethod(tpl, "reverse", Reverse);
    Nan::SetPrototypeMethod(tpl, "approxEquals", ApproxEquals);
    Nan::SetPrototypeMethod(tpl, "nearlyCoversPolyline", NearlyCoversPolyline);
    Nan::SetPrototypeMethod(tpl, "getRectBound", GetRectBound);
    Nan::SetPrototypeMethod(tpl, "contains", Contains);
    Nan::SetPrototypeMethod(tpl, "size", Size);

    Nan::Set(target, name, tpl->GetFunction());
}

Polyline::Polyline()
    : ObjectWrap(),
      this_() {}

NAN_METHOD(Polyline::New) {
    if (!info.IsConstructCall()) {
        Nan::ThrowError("Use the new operator to create instances of this object.");
        return;
    }

    if (info[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(info[0]);
        void* ptr = ext->Value();
        Polyline* ll = static_cast<Polyline*>(ptr);
        ll->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
        return;
    }

    if (info.Length() != 1) {
        Nan::ThrowError("array<LatLng> required");
        return;
    }

    if (!info[0]->IsArray()) {
       Nan::ThrowError("array<LatLng> required");
       return;
    }

    // unwrap array into std::vector
    v8::Handle<v8::Array> array = v8::Handle<v8::Array>::Cast(info[0]);
    std::vector<S2LatLng> coordinate_vector;
    for (unsigned i = 0; i < array->Length(); i++) {
        v8::Handle<v8::Value> value = array->Get(i);
        if (value->IsUndefined() || value->IsNull()) {
            Nan::ThrowError("array entry undefined");
            return;
        }
        LatLng* ll = node::ObjectWrap::Unwrap<LatLng>(value->ToObject());
        coordinate_vector.emplace_back(ll->get());
        // TODO: complete

        // std::cout << "[" << i << "] " << coordinate_vector.at(i).lat() << "," << coordinate_vector.at(i).lng() << std::endl;
    }
    Polyline* obj = new Polyline();
    obj->Wrap(info.This());

    // pass std::vector<S2LatLng> to c'tor
    obj->this_ = S2Polyline(coordinate_vector);
    info.GetReturnValue().Set(info.This());
}

Handle<Value> Polyline::New(S2Polyline s2cap) {
    Nan::EscapableHandleScope scope;
    Polyline* obj = new Polyline();
    obj->this_ = s2cap;
    Handle<Value> ext = Nan::New<External>(obj);
    Local<FunctionTemplate> constructorHandle = Nan::New(constructor);
    Handle<Object> handleObject =
      constructorHandle->GetFunction()->NewInstance(1, &ext);
    return scope.Escape(handleObject);
}

NAN_METHOD(Polyline::GetCapBound) {
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(info.This());
    info.GetReturnValue().Set(Cap::New(polyline->this_.GetCapBound()));
}

NAN_METHOD(Polyline::GetLength) {
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(info.This());
    info.GetReturnValue().Set(Angle::New(polyline->this_.GetLength()));
}

NAN_METHOD(Polyline::GetCentroid) {
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(info.This());
    info.GetReturnValue().Set(Point::New(polyline->this_.GetCentroid()));
}

NAN_METHOD(Polyline::Interpolate) {
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(info.This());
    info.GetReturnValue().Set(Point::New(polyline->this_.Interpolate(info[0]->ToNumber()->Value())));
}

NAN_METHOD(Polyline::GetSuffix) {
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(info.This());
    int next_vertex = info[1]->ToInteger()->Value();
    info.GetReturnValue().Set(Point::New(polyline->this_.GetSuffix(info[0]->ToNumber()->Value(), &next_vertex)));
    // TODO: set argv[1] to next_vertex
}

NAN_METHOD(Polyline::Intersects) {
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(info.This());
    S2Polyline other = node::ObjectWrap::Unwrap<Polyline>(info[0]->ToObject())->get();
    info.GetReturnValue().Set(Nan::New<Boolean>(polyline->this_.Intersects(&other)));
}

NAN_METHOD(Polyline::Reverse) {
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(info.This());
    polyline->this_.Reverse();
    info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(Polyline::ApproxEquals) {
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(info.This());
    S2Polyline other = node::ObjectWrap::Unwrap<Polyline>(info[0]->ToObject())->get();
    double max_error = info[1]->ToNumber()->Value();
    info.GetReturnValue().Set(Nan::New<Boolean>(polyline->this_.ApproxEquals(&other, max_error)));
}

NAN_METHOD(Polyline::NearlyCoversPolyline) {
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(info.This());
    S2Polyline other = node::ObjectWrap::Unwrap<Polyline>(info[0]->ToObject())->get();
    S1Angle max_error =  node::ObjectWrap::Unwrap<Angle>(info[0]->ToObject())->get();
    info.GetReturnValue().Set(Nan::New<Boolean>(polyline->this_.NearlyCoversPolyline(other, max_error)));
}

NAN_METHOD(Polyline::GetRectBound) {
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(info.This());
    info.GetReturnValue().Set(LatLngRect::New(polyline->this_.GetRectBound()));
}

NAN_METHOD(Polyline::Contains) {
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(info.This());
    S2Cell other = node::ObjectWrap::Unwrap<Cell>(info[0]->ToObject())->get();
    info.GetReturnValue().Set(Nan::New<Boolean>(polyline->this_.Contains(other)));
}

NAN_METHOD(Polyline::Size) {
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(info.This());
    info.GetReturnValue().Set(Nan::New<Integer>(polyline->this_.num_vertices()));
}
