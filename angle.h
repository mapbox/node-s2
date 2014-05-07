#ifndef NODES2ANGLE_HPP
#define NODES2ANGLE_HPP

#include <node.h>
#include <nan.h>
#include "s1angle.h"

class Angle : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    inline S1Angle get() { return this_; }
    static v8::Handle<v8::Value> New(const S1Angle c);

protected:
    Angle();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> Normalize(const v8::Arguments& args);

    S1Angle this_;
};

#endif
