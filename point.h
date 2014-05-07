#ifndef NODES2POINT_HPP
#define NODES2POINT_HPP

#include <node.h>
#include <nan.h>
#include "s2.h"

class Point : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    inline S2Point get() { return this_; }
    static v8::Handle<v8::Value> New(const S2Point c);

protected:
    Point();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> X(const v8::Arguments& args);
    static v8::Handle<v8::Value> Y(const v8::Arguments& args);
    static v8::Handle<v8::Value> Z(const v8::Arguments& args);

    S2Point this_;
};

#endif
