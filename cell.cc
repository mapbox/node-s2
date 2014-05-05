#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s2cell.h"
#include "s2latlng.h"
#include "latlng.h"
#include "cell.h"

using namespace v8;

Persistent<FunctionTemplate> Cell::constructor;

void Cell::Init(Handle<Object> target) {
    NanScope();

    constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(Cell::New));
    Local<String> name = String::NewSymbol("Cell");

    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    NODE_SET_PROTOTYPE_METHOD(constructor, "approxArea", ApproxArea);
    NODE_SET_PROTOTYPE_METHOD(constructor, "exactArea", ExactArea);
    NODE_SET_PROTOTYPE_METHOD(constructor, "averageArea", AverageArea);

    target->Set(name, constructor->GetFunction());
}

Cell::Cell()
    : ObjectWrap(),
      this_() {}

Handle<Value> Cell::New(const Arguments& args) {
    NanScope();

    if (!args.IsConstructCall()) {
        return NanThrowError("Use the new operator to create instances of this object.");
    }

    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        Cell* ll = static_cast<Cell*>(ptr);
        ll->Wrap(args.This());
        return args.This();
    }

    if (args.Length() != 1) {
        return NanThrowError("(latlng) required");
    }

    NODE_SET_PROTOTYPE_METHOD(constructor, "approxArea", ApproxArea);

    Cell* obj = new Cell();

    obj->Wrap(args.This());

    obj->this_ = S2Cell(
        S2CellId::FromLatLng(node::ObjectWrap::Unwrap<LatLng>(args[0]->ToObject())->get()));

    return args.This();
}

Handle<Value> Cell::New(S2Cell s2cell) {
    NanScope();
    Cell* obj = new Cell();
    obj->this_ = s2cell;
    Handle<Value> ext = External::New(obj);
    Handle<Object> handleObject = constructor->GetFunction()->NewInstance(1, &ext);
    return scope.Close(handleObject);
}

NAN_METHOD(Cell::ApproxArea) {
    NanScope();
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.This());
    NanReturnValue(NanNew<Number>(obj->this_.ApproxArea()));
}

NAN_METHOD(Cell::ExactArea) {
    NanScope();
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.This());
    NanReturnValue(NanNew<Number>(obj->this_.ExactArea()));
}

NAN_METHOD(Cell::AverageArea) {
    NanScope();
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.This());
    NanReturnValue(NanNew<Number>(obj->this_.AverageArea(args[0]->ToNumber()->Value())));
}
