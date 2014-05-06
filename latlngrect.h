#ifndef NODES2LATLNGRECT_HPP
#define NODES2LATLNGRECT_HPP

#include <node.h>
#include <nan.h>
#include "s2latlngrect.h"

class LatLngRect : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    inline S2LatLngRect get() { return this_; }
    static v8::Handle<v8::Value> New(const S2LatLngRect ll);

protected:
    LatLngRect();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> GetCenter(const v8::Arguments& args);
    static v8::Handle<v8::Value> GetSize(const v8::Arguments& args);
    static v8::Handle<v8::Value> GetArea(const v8::Arguments& args);
    static v8::Handle<v8::Value> GetVertex(const v8::Arguments& args);
    static v8::Handle<v8::Value> GetCapBound(const v8::Arguments& args);
    static v8::Handle<v8::Value> Contains(const v8::Arguments& args);

    S2LatLngRect this_;
};

#endif
