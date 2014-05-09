#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2latlng.h"
#include "s2cellid.h"
#include "s2cell.h"
#include "s2polygon.h"
#include "s2loop.h"
#include "s2polygonbuilder.h"
#include "s2regioncoverer.h"
#include "latlng.h"
#include "latlngrect.h"
#include "cell.h"
#include "cellid.h"
#include "interval.h"
#include "point.h"
#include "cap.h"
#include "regioncoverer.h"
#include "angle.h"

using namespace v8;

NAN_METHOD(GetCover) {
    NanScope();

    scoped_ptr<S2PolygonBuilder> builder(
            new S2PolygonBuilder(S2PolygonBuilderOptions::DIRECTED_XOR()));

    if (args.Length() < 1 || !args[0]->IsArray()) {
        return NanThrowError("(array, [min, max, mod]) required");
    }
    Handle<Array> array = Handle<Array>::Cast(args[0]);
    for (uint32_t i = 0; i < array->Length(); i++) {
        Local<Object> obj = array->Get(i)->ToObject();
        if (NanHasInstance(LatLng::constructor, obj)) {
            LatLng *a = node::ObjectWrap::Unwrap<LatLng>(array->Get(i)->ToObject());
            LatLng *b = node::ObjectWrap::Unwrap<LatLng>(array->Get((i + 1) % array->Length())->ToObject());
            builder->AddEdge(a->get().ToPoint(), b->get().ToPoint());
        }
    }

    S2Polygon polygon;
    typedef vector<pair<S2Point, S2Point> > EdgeList;
    EdgeList edgeList;
    std::vector<S2CellId> cellids_vector;
    S2RegionCoverer coverer;

    if (args.Length() >= 2) {
        Handle<Object> opt = args[1]->ToObject();
        if (opt->Has(NanSymbol("min"))) {
            coverer.set_min_level(opt->Get(NanSymbol("min"))->ToInteger()->Value());
        }
        if (opt->Has(NanSymbol("max"))) {
            coverer.set_max_level(opt->Get(NanSymbol("max"))->ToInteger()->Value());
        }
        if (opt->Has(NanSymbol("mod"))) {
            coverer.set_level_mod(opt->Get(NanSymbol("mod"))->ToInteger()->Value());
        }
        if (opt->Has(NanSymbol("max_cells"))) {
            coverer.set_max_cells(opt->Get(NanSymbol("max_cells"))->ToInteger()->Value());
        }
    }

    builder->AssemblePolygon(&polygon, &edgeList);
    coverer.GetCovering(polygon, &cellids_vector);

    Local<Array> out = Array::New(cellids_vector.size());

    for (int i = 0; i < cellids_vector.size(); i++) {
        out->Set(i, Cell::New(cellids_vector.at(i)));
    }

    NanReturnValue(out);
}

void RegisterModule(Handle<Object> exports) {
    LatLng::Init(exports);
    LatLngRect::Init(exports);
    Cap::Init(exports);
    Angle::Init(exports);
    Cell::Init(exports);
    CellId::Init(exports);
    Point::Init(exports);
    Interval::Init(exports);
    exports->Set(NanSymbol("getCover"),
            NanNew<FunctionTemplate>(GetCover)->GetFunction());
}

NODE_MODULE(_s2, RegisterModule);
