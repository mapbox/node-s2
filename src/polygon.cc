#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s2cell.h"
#include "s2cellid.h"
#include "s2latlng.h"
#include "s2polygon.h"
#include "latlng.h"
#include "cell.h"
#include "polygon.h"
#include "point.h"
#include "cap.h"
#include "cellid.h"

using namespace v8;

Nan::Persistent<FunctionTemplate> Polygon::constructor;

void Polygon::Init(Handle<Object> target) {
    Local<FunctionTemplate> tpl =
      Nan::New<FunctionTemplate>(Polygon::New);
    constructor.Reset(tpl);
    Local<String> name = Nan::New("S2Polygon").ToLocalChecked();

    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->SetClassName(name);

    // Nan::SetPrototypeMethod(tpl, "approxArea", ApproxArea);

    Nan::Set(target, name, tpl->GetFunction());
}

Polygon::Polygon()
    : ObjectWrap() {}

NAN_METHOD(Polygon::New) {
    if (!info.IsConstructCall()) {
        Nan::ThrowError("Use the new operator to create instances of this object.");
        return;
    }

    if (info[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(info[0]);
        void* ptr = ext->Value();
        Polygon* ll = static_cast<Polygon*>(ptr);
        ll->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
        return;
    }

    if (info.Length() != 1) {
        Nan::ThrowError("(latlng) required");
        return;
    }

    Polygon* obj = new Polygon();
    obj->Wrap(info.This());

    info.GetReturnValue().Set(info.This());
}

// NAN_METHOD(Polygon::ApproxArea) {
//     Polygon* obj = ObjectWrap::Unwrap<Polygon>(info.This());
//     info.GetReturnValue().Set(Nan::New<Number>(obj->this_.ApproxArea()));
// }
