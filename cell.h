#ifndef NODES2CELL_HPP
#define NODES2CELL_HPP

#include <node.h>
#include <nan.h>
#include "s2cell.h"
#include "s2cellid.h"

class Cell : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    inline S2Cell get() { return this_; }
    static v8::Handle<v8::Value> New(const S2Cell c);
    static v8::Handle<v8::Value> New(const S2CellId c);

protected:
    Cell();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> ApproxArea(const v8::Arguments& args);
    static v8::Handle<v8::Value> ExactArea(const v8::Arguments& args);
    static v8::Handle<v8::Value> Face(const v8::Arguments& args);
    static v8::Handle<v8::Value> Level(const v8::Arguments& args);
    static v8::Handle<v8::Value> AverageArea(const v8::Arguments& args);
    static v8::Handle<v8::Value> Orientation(const v8::Arguments& args);
    static v8::Handle<v8::Value> IsLeaf(const v8::Arguments& args);

    S2Cell this_;
};

#endif
