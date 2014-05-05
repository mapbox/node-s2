#ifndef NODES2_HPP
#define NODES2_HPP

#include <node.h>
#include "s2latlng.h"


// Do not include this line. It's generally frowned upon to use namespaces
// in header files as it may cause issues with other code that includes your
// header file.
// using namespace v8;


class LatLng : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);

protected:
    LatLng();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> New(const S2LatLng ll);
    static v8::Handle<v8::Value> Lat(const v8::Arguments& args);
    static v8::Handle<v8::Value> Lng(const v8::Arguments& args);
    static v8::Handle<v8::Value> IsValid(const v8::Arguments& args);
    static v8::Handle<v8::Value> Normalized(const v8::Arguments& args);

    S2LatLng this_;
};

#endif
