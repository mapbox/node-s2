#ifndef NODES2POLYGON_HPP
#define NODES2POLYGON_HPP

#include <node.h>
#include <nan.h>
#include "s2polygon.h"

class Polygon : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);

protected:
    Polygon();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    // static v8::Handle<v8::Value> ApproxArea(const v8::Arguments& args);
    // static NAN_METHOD(ApproxArea);
};

#endif
