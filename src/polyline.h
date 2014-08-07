#ifndef NODES2POLYLINE_HPP
#define NODES2POLYLINE_HPP

#include <node.h>
#include <nan.h>
#include "s2polyline.h"

class Polyline : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    inline S2Polyline get() { return this_; }
    static v8::Handle<v8::Value> New(const S2Polyline c);

protected:
    Polyline();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static NAN_METHOD(GetCapBound);
    static NAN_METHOD(GetLength);
    static NAN_METHOD(GetCentroid);
    static NAN_METHOD(Interpolate);
    static NAN_METHOD(GetSuffix);
    static NAN_METHOD(Intersects);
    static NAN_METHOD(Reverse);
    static NAN_METHOD(ApproxEquals);
    static NAN_METHOD(NearlyCoversPolyline);
    static NAN_METHOD(GetRectBound);
    static NAN_METHOD(Contains);
    static NAN_METHOD(Size);

    S2Polyline this_;
};

#endif
