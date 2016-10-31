#ifndef NODES2ANGLE_HPP
#define NODES2ANGLE_HPP

#include <node.h>
#include <nan.h>
#include "s1angle.h"

class Angle : public node::ObjectWrap {
public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    inline S1Angle get() { return this_; }
    static v8::Handle<v8::Value> New(const S1Angle c);

protected:
    Angle();

    static NAN_METHOD(New);
    static NAN_METHOD(Normalize);

    S1Angle this_;
};

#endif
