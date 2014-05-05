#include <node.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s2latlng.h"

using namespace v8;

Persistent<FunctionTemplate> LatLng::constructor;

void LatLng::Init(Handle<Object> target) {
    HandleScope scope;

    constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(LatLng::New));
    Local<String> name = String::NewSymbol("LatLng");

    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    // Add all prototype methods, getters and setters here.
    NODE_SET_PROTOTYPE_METHOD(constructor, "lat", Lat);
    NODE_SET_PROTOTYPE_METHOD(constructor, "lng", Lng);
    NODE_SET_PROTOTYPE_METHOD(constructor, "normalized", Normalized);
    NODE_SET_PROTOTYPE_METHOD(constructor, "is_valid", IsValid);

    // This has to be last, otherwise the properties won't show up on the
    // object in JavaScript.
    target->Set(name, constructor->GetFunction());
}

LatLng::LatLng()
    : ObjectWrap(),
      this_() {}

Handle<Value> LatLng::New(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall()) {
        return ThrowException(Exception::TypeError(
            String::New("Use the new operator to create instances of this object."))
        );
    }

    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        LatLng* ll = static_cast<LatLng*>(ptr);
        ll->Wrap(args.This());
        return args.This();
    }

    if (args.Length() != 2) {
        return ThrowException(Exception::TypeError(
            String::New("(number, number) required")));
    }

    LatLng* obj = new LatLng();

    obj->Wrap(args.This());

    obj->this_ = S2LatLng::FromDegrees(
        args[0]->ToNumber()->Value(),
        args[1]->ToNumber()->Value());

    return args.This();
}

Handle<Value> LatLng::New(S2LatLng s2latlng) {
    HandleScope scope;
    LatLng* obj = new LatLng();
    obj->this_ = s2latlng;
    Handle<Value> ext = External::New(obj);
    Handle<Object> handleObject = constructor->GetFunction()->NewInstance(1, &ext);
    return scope.Close(handleObject);
}

Handle<Value> LatLng::Lat(const Arguments& args) {
    HandleScope scope;
    LatLng* obj = ObjectWrap::Unwrap<LatLng>(args.This());
    return scope.Close(Number::New(obj->this_.lat().degrees()));
}

Handle<Value> LatLng::Lng(const Arguments& args) {
    HandleScope scope;
    LatLng* obj = ObjectWrap::Unwrap<LatLng>(args.This());
    return scope.Close(Number::New(obj->this_.lng().degrees()));
}

Handle<Value> LatLng::IsValid(const Arguments& args) {
    HandleScope scope;
    LatLng* obj = ObjectWrap::Unwrap<LatLng>(args.This());
    return scope.Close(Boolean::New(obj->this_.is_valid()));
}

Handle<Value> LatLng::Normalized(const Arguments& args) {
    HandleScope scope;
    LatLng* obj = ObjectWrap::Unwrap<LatLng>(args.This());
    return scope.Close(LatLng::New(obj->this_.Normalized()));
}
