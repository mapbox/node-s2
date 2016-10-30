#ifndef NODES2REGIONCOVERER_HPP
#define NODES2REGIONCOVERER_HPP

#include <node.h>
#include <nan.h>
#include "s2regioncoverer.h"

class RegionCoverer : public node::ObjectWrap {
public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    // inline S2RegionCoverer get() { return this_; }
    static v8::Handle<v8::Value> New(const S2RegionCoverer c);

protected:
    RegionCoverer();

    static NAN_METHOD(New);
    // static v8::Handle<v8::Value> ApproxArea(const v8::Arguments& args);
    // static NAN_METHOD(GetCenter);

    S2RegionCoverer this_;
};

#endif
