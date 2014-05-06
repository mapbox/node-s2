#ifndef NODES2INTERVAL_HPP
#define NODES2INTERVAL_HPP

#include <node.h>
#include <nan.h>
#include "s1interval.h"

class Interval : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    inline S1Interval get() { return this_; }
    static v8::Handle<v8::Value> New(const S1Interval c);

protected:
    Interval();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> GetLength(const v8::Arguments& args);
    static v8::Handle<v8::Value> GetCenter(const v8::Arguments& args);
    static v8::Handle<v8::Value> GetComplementCenter(const v8::Arguments& args);
    static v8::Handle<v8::Value> GetHi(const v8::Arguments& args);
    static v8::Handle<v8::Value> GetLo(const v8::Arguments& args);

    S1Interval this_;
};

#endif
