#ifndef NODES2POLYLINE_HPP
#define NODES2POLYLINE_HPP

#include <node.h>
#include <nan.h>
#include "s2polyline.h"

class Polyline : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    // inline S2Polyline get() { return this_; }
    static v8::Handle<v8::Value> New(const S2Polyline c);

protected:
    Polyline();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    // static v8::Handle<v8::Value> ApproxArea(const v8::Arguments& args);
    // static NAN_METHOD(ApproxArea);
    S2Polyline this_;
};

#endif
