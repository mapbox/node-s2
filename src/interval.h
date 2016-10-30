#ifndef NODES2INTERVAL_HPP
#define NODES2INTERVAL_HPP

#include <node.h>
#include <nan.h>
#include "s1interval.h"

class Interval : public node::ObjectWrap {
public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    inline S1Interval get() { return this_; }
    static v8::Handle<v8::Value> New(const S1Interval c);

protected:
    Interval();

    static NAN_METHOD(New);
    static NAN_METHOD(GetLength);
    static NAN_METHOD(GetCenter);
    static NAN_METHOD(GetComplementCenter);
    static NAN_METHOD(GetHi);
    static NAN_METHOD(GetLo);
    static NAN_METHOD(Contains);

    S1Interval this_;
};

#endif
