#ifndef NODES2CAP_HPP
#define NODES2CAP_HPP

#include <node.h>
#include <nan.h>
#include "s2cap.h"

class Cap : public node::ObjectWrap {
public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    inline S2Cap get() { return this_; }
    static v8::Handle<v8::Value> New(const S2Cap ll);

protected:
    Cap();

    static NAN_METHOD(New);
    static NAN_METHOD(GetRectBound);
    static NAN_METHOD(Intersects);
    static NAN_METHOD(InteriorIntersects);
    static NAN_METHOD(Contains);
    static NAN_METHOD(Complement);

    S2Cap this_;
};

#endif
