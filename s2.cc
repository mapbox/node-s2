#include <node.h>

#include "s2.h"
#include "s2latlng.h"
#include "s1interval.h"

using namespace v8;


Persistent<FunctionTemplate> Interval::constructor;

void Interval::Init(Handle<Object> target) {
    HandleScope scope;

    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    Local<String> name = String::NewSymbol("Interval");

    constructor = Persistent<FunctionTemplate>::New(tpl);
    // ObjectWrap uses the first internal field to store the wrapped pointer.
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    // Add all prototype methods, getters and setters here.
    NODE_SET_PROTOTYPE_METHOD(constructor, "value", Value);

    // This has to be last, otherwise the properties won't show up on the
    // object in JavaScript.
    target->Set(name, constructor->GetFunction());
}

Interval::Interval(int val)
    : ObjectWrap(),
      value_(val) {}


Handle<Value> Interval::New(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall()) {
        return ThrowException(Exception::TypeError(
            String::New("Use the new operator to create instances of this object."))
        );
    }

    if (args.Length() < 1) {
        return ThrowException(Exception::TypeError(
            String::New("First argument must be a number")));
    }

    // Creates a new instance object of this type and wraps it.
    Interval* obj = new Interval(args[0]->ToInteger()->Value());
    obj->Wrap(args.This());

    return args.This();
}


Handle<Value> Interval::Value(const Arguments& args) {
    HandleScope scope;

    // Retrieves the pointer to the wrapped object instance.
    Interval* obj = ObjectWrap::Unwrap<Interval>(args.This());

    return scope.Close(Integer::New(obj->value_));
}

Handle<Value> LatLngToPoint(const Arguments& args) {
    HandleScope scope;

    // Check that there are enough arguments. If we access an index that doesn't
    // exist, it'll be Undefined().
    if (args.Length() != 2) {
        // No argument was passed. Throw an exception to alert the user to
        // incorrect usage. Alternatively, we could just use 0.
        return ThrowException(
            Exception::TypeError(String::New("Two numbers required."))
        );
    }

    Local<Number> latitude = args[0]->ToNumber();
    Local<Number> longitude = args[1]->ToNumber();
    int32_t lat = latitude->Value();
    int32_t lon = longitude->Value();

    S2LatLng ll = S2LatLng::FromDegrees(0.0, 0.0);
    ll.ToPoint();

    //S2Point p = S2LatLng::FromDegrees(
    //  latitude->Value(),
    //  longitude->Value()
    //).ToPoint();

    // return scope.Close(Number::New(p.x()));
    return scope.Close(Number::New(0));
}

void RegisterModule(Handle<Object> target) {
    Interval::Init(target);
    target->Set(String::NewSymbol("latLngToPoint"),
        FunctionTemplate::New(LatLngToPoint)->GetFunction());
}

NODE_MODULE(_s2, RegisterModule);
