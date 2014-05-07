#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s2cell.h"
#include "s2cellid.h"
#include "s2latlng.h"
#include "latlng.h"
#include "cell.h"
#include "point.h"
#include "cap.h"
#include "cellid.h"

using namespace v8;

Persistent<FunctionTemplate> Cell::constructor;

void Cell::Init(Handle<Object> target) {
    NanScope();

    constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(Cell::New));
    Local<String> name = String::NewSymbol("S2Cell");

    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->SetClassName(name);

    NODE_SET_PROTOTYPE_METHOD(constructor, "approxArea", ApproxArea);
    NODE_SET_PROTOTYPE_METHOD(constructor, "exactArea", ExactArea);
    NODE_SET_PROTOTYPE_METHOD(constructor, "averageArea", AverageArea);
    NODE_SET_PROTOTYPE_METHOD(constructor, "face", Face);
    NODE_SET_PROTOTYPE_METHOD(constructor, "level", Level);
    NODE_SET_PROTOTYPE_METHOD(constructor, "orientation", Orientation);
    NODE_SET_PROTOTYPE_METHOD(constructor, "isLeaf", IsLeaf);
    NODE_SET_PROTOTYPE_METHOD(constructor, "getCapBound", GetCapBound);
    NODE_SET_PROTOTYPE_METHOD(constructor, "getCenter", GetCenter);
    NODE_SET_PROTOTYPE_METHOD(constructor, "id", Id);

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

    Cell* obj = new Cell();

    obj->Wrap(args.This());

    Handle<Object> ll = args[0]->ToObject();

    if (!NanHasInstance(LatLng::constructor, ll)) {
        return NanThrowError("(latlng) required");
    }

    obj->this_ = S2Cell(
        S2CellId::FromLatLng(node::ObjectWrap::Unwrap<LatLng>(ll)->get()));

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

Handle<Value> Cell::New(S2CellId s2cellid) {
    NanScope();
    Cell* obj = new Cell();
    obj->this_ = S2Cell(s2cellid);
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

NAN_METHOD(Cell::Face) {
    NanScope();
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.This());
    NanReturnValue(NanNew<Number>(obj->this_.face()));
}

NAN_METHOD(Cell::Level) {
    NanScope();
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.This());
    NanReturnValue(NanNew<Number>(obj->this_.level()));
}

NAN_METHOD(Cell::Orientation) {
    NanScope();
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.This());
    NanReturnValue(NanNew<Number>(obj->this_.orientation()));
}

NAN_METHOD(Cell::IsLeaf) {
    NanScope();
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.This());
    NanReturnValue(NanNew<Boolean>(obj->this_.is_leaf()));
}

NAN_METHOD(Cell::GetCapBound) {
    NanScope();
    Cell* obj = node::ObjectWrap::Unwrap<Cell>(args.This());
    NanReturnValue(Cap::New(obj->this_.GetCapBound()));
}

NAN_METHOD(Cell::GetCenter) {
    NanScope();
    Cell* obj = node::ObjectWrap::Unwrap<Cell>(args.This());
    NanReturnValue(Point::New(obj->this_.GetCenterRaw()));
}

NAN_METHOD(Cell::Id) {
    NanScope();
    Cell* obj = node::ObjectWrap::Unwrap<Cell>(args.This());
    NanReturnValue(CellId::New(obj->this_.id()));
}
