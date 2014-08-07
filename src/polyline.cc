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

Persistent<FunctionTemplate> Polyline::constructor;

void Polyline::Init(Handle<Object> target) {
    NanScope();

    constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(Polyline::New));
    Local<String> name = String::NewSymbol("S2Polyline");

    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    NODE_SET_PROTOTYPE_METHOD(constructor, "getCapBound", GetCapBound);
    NODE_SET_PROTOTYPE_METHOD(constructor, "getLength", GetLength);
    NODE_SET_PROTOTYPE_METHOD(constructor, "getCentroid", GetCentroid);
    NODE_SET_PROTOTYPE_METHOD(constructor, "interpolate", Interpolate);
    NODE_SET_PROTOTYPE_METHOD(constructor, "getSuffix", GetSuffix);
    NODE_SET_PROTOTYPE_METHOD(constructor, "intersects", Intersects);
    NODE_SET_PROTOTYPE_METHOD(constructor, "reverse", Reverse);
    NODE_SET_PROTOTYPE_METHOD(constructor, "approxEquals", ApproxEquals);
    NODE_SET_PROTOTYPE_METHOD(constructor, "nearlyCoversPolyline", NearlyCoversPolyline);
    NODE_SET_PROTOTYPE_METHOD(constructor, "getRectBound", GetRectBound);
    NODE_SET_PROTOTYPE_METHOD(constructor, "contains", Contains);
    NODE_SET_PROTOTYPE_METHOD(constructor, "size", Size);

    target->Set(name, constructor->GetFunction());
}

Polyline::Polyline()
    : ObjectWrap(),
      this_() {}

Handle<Value> Polyline::New(const Arguments& args) {
    NanScope();

    if (!args.IsConstructCall()) {
        return NanThrowError("Use the new operator to create instances of this object.");
    }

    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        Polyline* ll = static_cast<Polyline*>(ptr);
        ll->Wrap(args.This());
        return args.This();
    }

    if (args.Length() != 1) {
        return NanThrowError("array<LatLng> required");
    }

    if (!args[0]->IsArray()) {
       return NanThrowError("array<LatLng> required");
    }

    // unwrap array into std::vector
    v8::Handle<v8::Array> array = v8::Handle<v8::Array>::Cast(args[0]);
    std::vector<S2LatLng> coordinate_vector;
    for (unsigned i = 0; i < array->Length(); i++) {
        v8::Handle<v8::Value> value = array->Get(i);
        if (value->IsUndefined() || value->IsNull()) {
            return NanThrowError("array entry undefined");
        }
        LatLng* ll = node::ObjectWrap::Unwrap<LatLng>(value->ToObject());
        coordinate_vector.emplace_back(ll->get());
        // TODO: complete

        // std::cout << "[" << i << "] " << coordinate_vector.at(i).lat() << "," << coordinate_vector.at(i).lng() << std::endl;
    }
    Polyline* obj = new Polyline();
    obj->Wrap(args.This());

    // pass std::vector<S2LatLng> to c'tor
    obj->this_ = S2Polyline(coordinate_vector);
    return args.This();
}

Handle<Value> Polyline::New(S2Polyline s2cap) {
    NanScope();
    Polyline* obj = new Polyline();
    obj->this_ = s2cap;
    Handle<Value> ext = External::New(obj);
    Handle<Object> handleObject = constructor->GetFunction()->NewInstance(1, &ext);
    return scope.Close(handleObject);
}

NAN_METHOD(Polyline::GetCapBound) {
    NanScope();
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(args.This());
    NanReturnValue(Cap::New(polyline->this_.GetCapBound()));
}

NAN_METHOD(Polyline::GetLength) {
    NanScope();
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(args.This());
    NanReturnValue(Angle::New(polyline->this_.GetLength()));
}

NAN_METHOD(Polyline::GetCentroid) {
    NanScope();
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(args.This());
    NanReturnValue(Point::New(polyline->this_.GetCentroid()));
}

NAN_METHOD(Polyline::Interpolate) {
    NanScope();
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(args.This());
    NanReturnValue(Point::New(polyline->this_.Interpolate(args[0]->ToNumber()->Value())));
}

NAN_METHOD(Polyline::GetSuffix) {
    NanScope();
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(args.This());
    int next_vertex = args[1]->ToInteger()->Value();
    NanReturnValue(Point::New(polyline->this_.GetSuffix(args[0]->ToNumber()->Value(),
                                                          &next_vertex)));
    // TODO: set argv[1] to next_vertex
}

NAN_METHOD(Polyline::Intersects) {
    NanScope();
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(args.This());
    S2Polyline other = node::ObjectWrap::Unwrap<Polyline>(args[0]->ToObject())->get();
    NanReturnValue(NanNew<Boolean>(polyline->this_.Intersects(&other)));
}

NAN_METHOD(Polyline::Reverse) {
    NanScope();
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(args.This());
    polyline->this_.Reverse();
    NanReturnUndefined();
}

NAN_METHOD(Polyline::ApproxEquals) {
    NanScope();
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(args.This());
    S2Polyline other = node::ObjectWrap::Unwrap<Polyline>(args[0]->ToObject())->get();
    double max_error = args[1]->ToNumber()->Value();
    NanReturnValue(NanNew<Boolean>(polyline->this_.ApproxEquals(&other, max_error)));
}

NAN_METHOD(Polyline::NearlyCoversPolyline) {
    NanScope();
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(args.This());
    S2Polyline other = node::ObjectWrap::Unwrap<Polyline>(args[0]->ToObject())->get();
    S1Angle max_error =  node::ObjectWrap::Unwrap<Angle>(args[0]->ToObject())->get();
    NanReturnValue(NanNew<Boolean>(polyline->this_.NearlyCoversPolyline(other, max_error)));
}

NAN_METHOD(Polyline::GetRectBound) {
    NanScope();
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(args.This());
    NanReturnValue(LatLngRect::New(polyline->this_.GetRectBound()));
}

NAN_METHOD(Polyline::Contains) {
    NanScope();
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(args.This());
    S2Cell other = node::ObjectWrap::Unwrap<Cell>(args[0]->ToObject())->get();
    NanReturnValue(NanNew<Boolean>(polyline->this_.Contains(other)));
}

NAN_METHOD(Polyline::Size) {
    NanScope();
    Polyline* polyline = node::ObjectWrap::Unwrap<Polyline>(args.This());
    NanReturnValue(NanNew<Integer>(polyline->this_.num_vertices()));
}
