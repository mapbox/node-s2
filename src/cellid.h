#ifndef NODES2CELLID_HPP
#define NODES2CELLID_HPP

#include <node.h>
#include <nan.h>
#include "s2cellid.h"

class CellId : public node::ObjectWrap {
public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    inline S2CellId get() { return this_; }
    static v8::Handle<v8::Value> New(const S2CellId c);

protected:
    CellId();

    static NAN_METHOD(New);
    static NAN_METHOD(Level);
    static NAN_METHOD(ToToken);
    static NAN_METHOD(ToPoint);
    static NAN_METHOD(ToLatLng);
    static NAN_METHOD(ToString);
    static NAN_METHOD(FromToken);
    static NAN_METHOD(Parent);
    static NAN_METHOD(Prev);
    static NAN_METHOD(Next);
    static NAN_METHOD(IsFace);
    static NAN_METHOD(RangeMin);
    static NAN_METHOD(RangeMax);
    static NAN_METHOD(Id);
    static NAN_METHOD(Child);
    static NAN_METHOD(Contains);

    S2CellId this_;
};

#endif
