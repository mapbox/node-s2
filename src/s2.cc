#include <node.h>
#include <nan.h>
#include <vector>
#include "node_object_wrap.h"           // for ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2latlng.h"
#include "s2cellid.h"
#include "s2cell.h"
#include "s2polygon.h"
#include "s2loop.h"
#include "s2polygonbuilder.h"
#include "s2regioncoverer.h"
#include "s2polyline.h"
#include "latlng.h"
#include "latlngrect.h"
#include "cell.h"
#include "cellid.h"
#include "interval.h"
#include "point.h"
#include "cap.h"
#include "regioncoverer.h"
#include "angle.h"

using std::vector;
using namespace v8;

NAN_METHOD(GetCover) {
    NanScope();

    if (args.Length() < 1) {
        return NanThrowError("(array, [min, max, mod]) required");
    }

    typedef vector<pair<S2Point, S2Point> > EdgeList;
    std::vector<S2CellId> cellids_vector;
    S2RegionCoverer coverer;

    std::string type = "polygon";

    if (args.Length() > 1) {
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

    if (args[0]->IsArray()) {
        Handle<Array> array = Handle<Array>::Cast(args[0]);

        if (args.Length() > 1) {
            Handle<Object> opt = args[1]->ToObject();
            size_t count;
            type = NanCString(opt->Get(NanSymbol("type")), &count);
        }

        if (type == "polygon") {
            S2PolygonBuilderOptions polyOptions;
            polyOptions.set_validate(true);
            // Don't silently eliminate duplicate edges.
            polyOptions.set_xor_edges(false);
            S2PolygonBuilder builder(polyOptions);
            S2Polygon polygon;
            std::vector<S2Point> rings;

            for (uint32_t i = 0; i < array->Length(); i++) {
                std::vector<S2Point> points;
                Handle<Array> pointArray = Handle<Array>::Cast(array->Get(i));

                for (uint32_t ii = 0; ii < pointArray->Length(); ii++) {
                    S2LatLng pt = S2LatLng(node::ObjectWrap::Unwrap<Point>(pointArray->Get(ii)->ToObject())->get());
                    Local<Object> obj = pointArray->Get(ii)->ToObject();
                    if (NanHasInstance(Point::constructor, obj)) {
                        S2Point p = node::ObjectWrap::Unwrap<Point>(obj)->get();
                        points.push_back(p);
                    } else {
                        return NanThrowError("array must contain only points");
                    }
                }
                // construct polygon loop
                S2Loop loop(points);
                loop.Normalize();

                // outer ring should not be a hole
                if (i==0 && loop.is_hole()) {
                    loop.Invert();
                }
                // inner rings should be holes
                else if (i==1 && !loop.is_hole()) {
                    loop.Invert();
                }

                if (!loop.IsValid()) {
                    return NanThrowError("invalid loop");
                }

                builder.AddLoop(&loop);
            }
            // get cover
            EdgeList edgeList;
            builder.AssemblePolygon(&polygon, &edgeList);
            coverer.GetCovering(polygon, &cellids_vector);
        } else if (type == "polyline") {
            std::vector<S2Point> points;

            for (uint32_t i = 0; i < array->Length(); i++) {
                Local<Object> obj = array->Get(i)->ToObject();
                if (NanHasInstance(Point::constructor, obj)) {
                    S2Point p = node::ObjectWrap::Unwrap<Point>(array->Get(i)->ToObject())->get();
                    points.push_back(p);
                } else {
                    return NanThrowError("array must contain only points");
                }
            }

            S2Polyline polyline(points);
            coverer.GetCovering(polyline, &cellids_vector);
        }
    } else if (NanHasInstance(LatLngRect::constructor, args[0])) {
        S2LatLngRect rect = node::ObjectWrap::Unwrap<LatLngRect>(args[0]->ToObject())->get();
        coverer.GetCovering(rect, &cellids_vector);
    } else if (NanHasInstance(Cell::constructor, args[0])) {
        S2Cell cell = node::ObjectWrap::Unwrap<Cell>(args[0]->ToObject())->get();
        coverer.GetCovering(cell, &cellids_vector);
    } else if (NanHasInstance(Cap::constructor, args[0])) {
        S2Cap cap = node::ObjectWrap::Unwrap<Cap>(args[0]->ToObject())->get();
        coverer.GetCovering(cap, &cellids_vector);
    } else {
        return NanThrowError("incompatible object to cover");
    }

    Local<Array> out = Array::New(cellids_vector.size());

    for (int i = 0; i < cellids_vector.size(); i++) {
        out->Set(i, Cell::New(cellids_vector.at(i)));
    }
    if(cellids_vector.size() < 1){
        //return NanThrowError("NO CELLS WERE FOUND");
    }
    NanReturnValue(out);
}

void RegisterModule(Handle<Object> exports) {
    LatLng::Init(exports);
    LatLngRect::Init(exports);
    Cap::Init(exports);
    Angle::Init(exports);
    // Polyline::Init(exports);
    Cell::Init(exports);
    CellId::Init(exports);
    Point::Init(exports);
    Interval::Init(exports);
    exports->Set(NanSymbol("getCover"),
            NanNew<FunctionTemplate>(GetCover)->GetFunction());
}

NODE_MODULE(_s2, RegisterModule);

