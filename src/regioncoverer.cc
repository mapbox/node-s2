#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s2cell.h"
#include "s2cellid.h"
#include "s2latlng.h"
#include "s2regioncoverer.h"
#include "latlng.h"
#include "cell.h"
#include "point.h"
#include "regioncoverer.h"
#include "cap.h"
#include "cellid.h"

using namespace v8;

Nan::Persistent<FunctionTemplate> RegionCoverer::constructor;

void RegionCoverer::Init(Handle<Object> target) {
    Local<FunctionTemplate> tpl =
      Nan::New<FunctionTemplate>(RegionCoverer::New);
    constructor.Reset(tpl);
    Local<String> name = Nan::New("S2RegionCoverer").ToLocalChecked();

    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->SetClassName(name);

    // Nan::SetPrototypeMethod(tpl, "getCenter", GetCenter);

    Nan::Set(target, name, tpl->GetFunction());
}

RegionCoverer::RegionCoverer()
    : ObjectWrap(),
      this_() {}

NAN_METHOD(RegionCoverer::New) {
    if (!info.IsConstructCall()) {
        Nan::ThrowError("Use the new operator to create instances of this object.");
        return;
    }

    if (info[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(info[0]);
        void* ptr = ext->Value();
        RegionCoverer* ll = static_cast<RegionCoverer*>(ptr);
        ll->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
        return;
    }

    RegionCoverer* obj = new RegionCoverer();
    obj->Wrap(info.This());

    Handle<Object> ll = info[0]->ToObject();

    S2RegionCoverer cov;

    obj->this_ = cov;

    info.GetReturnValue().Set(info.This());
}

Handle<Value> RegionCoverer::New(S2RegionCoverer rc) {
    Nan::EscapableHandleScope scope;
    RegionCoverer* obj = new RegionCoverer();
    obj->this_ = rc;
    Handle<Value> ext = Nan::New<External>(obj);
    Local<FunctionTemplate> constructorHandle = Nan::New(constructor);
    Handle<Object> handleObject =
      constructorHandle->GetFunction()->NewInstance(1, &ext);
    return scope.Escape(handleObject);
}
