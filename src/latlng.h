#ifndef NODES2LATLNG_HPP
#define NODES2LATLNG_HPP

#include <node.h>
#include <nan.h>
#include "s2latlng.h"

class LatLng : public node::ObjectWrap {
public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    inline S2LatLng get() { return this_; }
    static v8::Handle<v8::Value> New(const S2LatLng ll);

protected:
    LatLng();

    static NAN_METHOD(New);
    static NAN_GETTER(Lat);
    static NAN_GETTER(Lng);
    static NAN_METHOD(IsValid);
    static NAN_METHOD(Normalized);
    static NAN_METHOD(ToPoint);
    static NAN_METHOD(ToString);
    static NAN_METHOD(Distance);

    S2LatLng this_;
};

#endif
