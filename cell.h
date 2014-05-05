#ifndef NODES2CELL_HPP
#define NODES2CELL_HPP

#include <node.h>
#include <nan.h>
#include "s2cell.h"

class Cell : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    inline S2Cell get() { return this_; }
    static v8::Handle<v8::Value> New(const S2Cell c);

protected:
    Cell();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> ApproxArea(const v8::Arguments& args);
    static v8::Handle<v8::Value> ExactArea(const v8::Arguments& args);
    static v8::Handle<v8::Value> AverageArea(const v8::Arguments& args);

    S2Cell this_;
};

#endif
