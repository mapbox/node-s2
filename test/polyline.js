var test = require('tap').test,
    s2 = require('../');

test('S2Polyline', function(t) {

    // throws on empty c'tor
    t.throws(function() {
        var polyline = new s2.S2Polyline();
    }, 'throws on empty input');

    // throws if parameter to c'tor isn't an array
    t.throws(function() {
        var latLng = new s2.S2LatLng([10, 20]);
        var polyline = new s2.S2Polyline(latLng);
    }, 'throws on non-array input');

    // generates 10 distinct latlngs and passes them to c'tor
    var coordinateArray = [];
    var numberofCoordinates = 10;
    for (var i = 0; i < 10; i++) {
        var ll = new s2.S2LatLng(10*i+1, 5*i+1);
        coordinateArray.push(ll);
    }
    var polyline = new s2.S2Polyline(coordinateArray);

    t.ok(polyline.size() == 10, "cardinality of polyline");
    t.ok(polyline.interpolate(0) instanceof s2.S2Point, "interpolate");
    t.ok(polyline.getCentroid() instanceof s2.S2Point, "getCentroid");
    t.ok(polyline.getSuffix(0) instanceof s2.S2Point, "getSuffix");
    t.end();
});
