#ifndef NODES2LATLNGRECT_HPP
#define NODES2LATLNGRECT_HPP

#include <node.h>
#include <nan.h>
#include "s2latlngrect.h"

class LatLngRect : public node::ObjectWrap {
public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    inline S2LatLngRect get() { return this_; }
    static v8::Handle<v8::Value> New(const S2LatLngRect ll);

protected:
    LatLngRect();

    static NAN_METHOD(New);
    static NAN_METHOD(GetCenter);
    static NAN_METHOD(GetSize);
    static NAN_METHOD(GetArea);
    static NAN_METHOD(GetVertex);
    static NAN_METHOD(GetCapBound);
    static NAN_METHOD(Contains);
    static NAN_METHOD(IsValid);
    static NAN_METHOD(IsEmpty);
    static NAN_METHOD(IsPoint);
    static NAN_METHOD(Union);
    static NAN_METHOD(Intersection);
    static NAN_METHOD(ApproxEquals);

    S2LatLngRect this_;
};

#endif
