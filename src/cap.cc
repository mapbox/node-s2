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

Persistent<FunctionTemplate> Cap::constructor;

void Cap::Init(Handle<Object> target) {
    NanScope();

    constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(Cap::New));
    Local<String> name = String::NewSymbol("S2Cap");

    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    NODE_SET_PROTOTYPE_METHOD(constructor, "getRectBound", GetRectBound);
    NODE_SET_PROTOTYPE_METHOD(constructor, "intersects", Intersects);
    NODE_SET_PROTOTYPE_METHOD(constructor, "interiorIntersects", InteriorIntersects);
    NODE_SET_PROTOTYPE_METHOD(constructor, "contains", Contains);
    NODE_SET_PROTOTYPE_METHOD(constructor, "complement", Complement);

    target->Set(name, constructor->GetFunction());
}

Cap::Cap()
    : ObjectWrap(),
      this_() {}

Handle<Value> Cap::New(const Arguments& args) {
    NanScope();

    if (!args.IsConstructCall()) {
        return NanThrowError("Use the new operator to create instances of this object.");
    }

    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        Cap* ll = static_cast<Cap*>(ptr);
        ll->Wrap(args.This());
        return args.This();
    }

    Cap* obj = new Cap();

    obj->Wrap(args.This());

    if (args.Length() == 2 && args[1]->IsNumber()) {
        Handle<Object> fromObj = args[0]->ToObject();
        if (NanHasInstance(Point::constructor, fromObj)) {
            S2Point p = node::ObjectWrap::Unwrap<Point>(fromObj)->get();
            obj->this_ = S2Cap::FromAxisHeight(p, args[1]->ToNumber()->Value());
        } else {
            return NanThrowError("S2Cap requires arguments (S2Point, number)");
        }
    } else {
        return NanThrowError("S2Cap requires arguments (S2Point, number)");
    }

    return args.This();
}

Handle<Value> Cap::New(S2Cap s2cap) {
    NanScope();
    Cap* obj = new Cap();
    obj->this_ = s2cap;
    Handle<Value> ext = External::New(obj);
    Handle<Object> handleObject = constructor->GetFunction()->NewInstance(1, &ext);
    return scope.Close(handleObject);
}

NAN_METHOD(Cap::GetRectBound) {
    NanScope();
    Cap* cap = node::ObjectWrap::Unwrap<Cap>(args.This());
    NanReturnValue(LatLngRect::New(cap->this_.GetRectBound()));
}

NAN_METHOD(Cap::Intersects) {
    NanScope();
    Cap* cap = node::ObjectWrap::Unwrap<Cap>(args.This());
    S2Cap other = node::ObjectWrap::Unwrap<Cap>(args[0]->ToObject())->get();
    NanReturnValue(NanNew<Boolean>(cap->this_.Intersects(other)));
}

NAN_METHOD(Cap::InteriorIntersects) {
    NanScope();
    Cap* cap = node::ObjectWrap::Unwrap<Cap>(args.This());
    S2Cap other = node::ObjectWrap::Unwrap<Cap>(args[0]->ToObject())->get();
    NanReturnValue(NanNew<Boolean>(cap->this_.Intersects(other)));
}

NAN_METHOD(Cap::Contains) {
    NanScope();
    Cap* cap = node::ObjectWrap::Unwrap<Cap>(args.This());
    S2Cap other = node::ObjectWrap::Unwrap<Cap>(args[0]->ToObject())->get();
    NanReturnValue(NanNew<Boolean>(cap->this_.Contains(other)));
}

NAN_METHOD(Cap::Complement) {
    NanScope();
    Cap* cap = node::ObjectWrap::Unwrap<Cap>(args.This());
    NanReturnValue(Cap::New(cap->this_.Complement()));
}
