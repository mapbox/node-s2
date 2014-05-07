#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s2cell.h"
#include "s2cellid.h"
#include "s2latlng.h"
#include "latlng.h"
#include "point.h"
#include "cellid.h"

using namespace v8;

Persistent<FunctionTemplate> CellId::constructor;

void CellId::Init(Handle<Object> target) {
    NanScope();

    constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(CellId::New));
    Local<String> name = String::NewSymbol("CellId");

    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    NODE_SET_PROTOTYPE_METHOD(constructor, "level", Level);
    NODE_SET_PROTOTYPE_METHOD(constructor, "toToken", ToToken);
    NODE_SET_PROTOTYPE_METHOD(constructor, "toPoint", ToPoint);
    NODE_SET_PROTOTYPE_METHOD(constructor, "toString", ToString);


    target->Set(name, constructor->GetFunction());
}

CellId::CellId()
    : ObjectWrap(),
      this_() {}

Handle<Value> CellId::New(const Arguments& args) {
    NanScope();

    if (!args.IsConstructCall()) {
        return NanThrowError("Use the new operator to create instances of this object.");
    }

    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        CellId* cellid = static_cast<CellId*>(ptr);
        cellid->Wrap(args.This());
        return args.This();
    }

    CellId* obj = new CellId();

    obj->Wrap(args.This());

    obj->this_ = S2CellId();

    return args.This();
}

Handle<Value> CellId::New(S2CellId s2cellid) {
    NanScope();
    CellId* obj = new CellId();
    obj->this_ = s2cellid;
    Handle<Value> ext = External::New(obj);
    Handle<Object> handleObject = constructor->GetFunction()->NewInstance(1, &ext);
    return scope.Close(handleObject);
}

NAN_METHOD(CellId::Level) {
    NanScope();
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.This());
    NanReturnValue(NanNew<Number>(obj->this_.level()));
}

NAN_METHOD(CellId::ToToken) {
    NanScope();
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.This());
    NanReturnValue(NanNew<String>(obj->this_.ToToken().c_str()));
}

NAN_METHOD(CellId::ToString) {
    NanScope();
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.This());
    NanReturnValue(NanNew<String>(obj->this_.ToString().c_str()));
}

NAN_METHOD(CellId::ToPoint) {
    NanScope();
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.This());
    NanReturnValue(Point::New(obj->this_.ToPoint()));
}
