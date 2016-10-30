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

Nan::Persistent<FunctionTemplate> Cell::constructor;

void Cell::Init(Handle<Object> target) {
    Local<FunctionTemplate> tpl =
      Nan::New<FunctionTemplate>(Cell::New);
    constructor.Reset(tpl);
    Local<String> name = Nan::New("S2Cell").ToLocalChecked();

    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->SetClassName(name);

    Nan::SetPrototypeMethod(tpl, "approxArea", ApproxArea);
    Nan::SetPrototypeMethod(tpl, "exactArea", ExactArea);
    Nan::SetPrototypeMethod(tpl, "averageArea", AverageArea);
    Nan::SetPrototypeMethod(tpl, "face", Face);
    Nan::SetPrototypeMethod(tpl, "level", Level);
    Nan::SetPrototypeMethod(tpl, "orientation", Orientation);
    Nan::SetPrototypeMethod(tpl, "isLeaf", IsLeaf);
    Nan::SetPrototypeMethod(tpl, "getCapBound", GetCapBound);
    Nan::SetPrototypeMethod(tpl, "getVertex", GetVertex);
    Nan::SetPrototypeMethod(tpl, "getCenter", GetCenter);
    Nan::SetPrototypeMethod(tpl, "id", Id);
    Nan::SetPrototypeMethod(tpl, "toString", ToString);

    Nan::Set(target, name, tpl->GetFunction());
}

Cell::Cell()
    : ObjectWrap(),
      this_() {}

NAN_METHOD(Cell::New) {
    if (!info.IsConstructCall()) {
        Nan::ThrowError("Use the new operator to create instances of this object.");
        return;
    }

    if (info[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(info[0]);
        void* ptr = ext->Value();
        Cell* ll = static_cast<Cell*>(ptr);
        ll->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
        return;
    }

    if (info.Length() != 1) {
        Nan::ThrowError("(latlng) required");
        return;
    }

    Cell* obj = new Cell();

    obj->Wrap(info.This());

    Handle<Object> ll = info[0]->ToObject();

    Local<FunctionTemplate> constructorHandle =
      Nan::New(LatLng::constructor);
    Local<FunctionTemplate> constructorHandle2 =
      Nan::New(CellId::constructor);
    if (constructorHandle->HasInstance(ll)) {
        obj->this_ = S2Cell(
            S2CellId::FromLatLng(node::ObjectWrap::Unwrap<LatLng>(ll)->get()));
    } else if (constructorHandle2->HasInstance(ll)) {
        obj->this_ = S2Cell(node::ObjectWrap::Unwrap<CellId>(ll)->get());
    } else {
        Nan::ThrowError("(latlng) or (cellid) required");
        return;
    }

    info.GetReturnValue().Set(info.This());
}

Handle<Value> Cell::New(S2Cell s2cell) {
    Nan::EscapableHandleScope scope;
    Cell* obj = new Cell();
    obj->this_ = s2cell;
    Handle<Value> ext = Nan::New<External>(obj);
    Local<FunctionTemplate> constructorHandle = Nan::New(constructor);
    Handle<Object> handleObject =
      constructorHandle->GetFunction()->NewInstance(1, &ext);
    return scope.Escape(handleObject);
}

Handle<Value> Cell::New(S2CellId s2cellid) {
    Nan::EscapableHandleScope scope;
    Cell* obj = new Cell();
    obj->this_ = S2Cell(s2cellid);
    Handle<Value> ext = Nan::New<External>(obj);
    Local<FunctionTemplate> constructorHandle = Nan::New(constructor);
    Handle<Object> handleObject =
      constructorHandle->GetFunction()->NewInstance(1, &ext);
    return scope.Escape(handleObject);
}

NAN_METHOD(Cell::ApproxArea) {
    Cell* obj = ObjectWrap::Unwrap<Cell>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.ApproxArea()));
}

NAN_METHOD(Cell::ExactArea) {
    Cell* obj = ObjectWrap::Unwrap<Cell>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.ExactArea()));
}

NAN_METHOD(Cell::AverageArea) {
    Cell* obj = ObjectWrap::Unwrap<Cell>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.AverageArea(info[0]->ToNumber()->Value())));
}

NAN_METHOD(Cell::Face) {
    Cell* obj = ObjectWrap::Unwrap<Cell>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.face()));
}

NAN_METHOD(Cell::Level) {
    Cell* obj = ObjectWrap::Unwrap<Cell>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.level()));
}

NAN_METHOD(Cell::Orientation) {
    Cell* obj = ObjectWrap::Unwrap<Cell>(info.This());
    info.GetReturnValue().Set(Nan::New<Number>(obj->this_.orientation()));
}

NAN_METHOD(Cell::IsLeaf) {
    Cell* obj = ObjectWrap::Unwrap<Cell>(info.This());
    info.GetReturnValue().Set(Nan::New<Boolean>(obj->this_.is_leaf()));
}

NAN_METHOD(Cell::GetCapBound) {
    Cell* obj = node::ObjectWrap::Unwrap<Cell>(info.This());
    info.GetReturnValue().Set(Cap::New(obj->this_.GetCapBound()));
}

NAN_METHOD(Cell::GetCenter) {
    Cell* obj = node::ObjectWrap::Unwrap<Cell>(info.This());
    info.GetReturnValue().Set(Point::New(obj->this_.GetCenterRaw()));
}

NAN_METHOD(Cell::Id) {
    Cell* obj = node::ObjectWrap::Unwrap<Cell>(info.This());
    info.GetReturnValue().Set(CellId::New(obj->this_.id()));
}

NAN_METHOD(Cell::ToString) {
    Cell* obj = node::ObjectWrap::Unwrap<Cell>(info.This());
    info.GetReturnValue().Set(
      Nan::New(obj->this_.id().ToString().c_str()).ToLocalChecked());
}

NAN_METHOD(Cell::GetVertex) {
    Cell* cell = node::ObjectWrap::Unwrap<Cell>(info.This());
    info.GetReturnValue().Set(Point::New(cell->this_.GetVertex(info[0]->ToNumber()->Value())));
}
