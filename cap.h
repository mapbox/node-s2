#ifndef NODES2CAP_HPP
#define NODES2CAP_HPP

#include <node.h>
#include <nan.h>
#include "s2cap.h"

class Cap : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    inline S2Cap get() { return this_; }
    static v8::Handle<v8::Value> New(const S2Cap ll);

protected:
    Cap();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> GetRectBound(const v8::Arguments& args);
    static v8::Handle<v8::Value> Intersects(const v8::Arguments& args);
    static v8::Handle<v8::Value> Contains(const v8::Arguments& args);
    static v8::Handle<v8::Value> Complement(const v8::Arguments& args);

    S2Cap this_;
};

#endif
