var test = require('tap').test,
    s2 = require('../');

test('LatLng', function(t) {

    var ll = new s2.LatLng(10, 20);
    t.ok(ll, 'generates latlng object');
    t.equal(ll.lat(), 10, 'lat()');
    t.equal(ll.lng(), 20, 'lon()');
    t.equal(ll.isValid(), true, 'is_valid()');
    t.ok(ll.toPoint() instanceof s2.Point, 'toPoint()');
    t.equal(ll.toString(), '10.000000,20.000000', 'toString');

    var invalid = new s2.LatLng(1000, 2000);
    t.equal(invalid.isValid(), false, 'isValid()');
    t.equal(invalid.normalized().lat(), 90, 'normalized()');

    var a = new s2.LatLng(10, 20);
    var b = new s2.LatLng(10, 40);
    t.ok(a.distance(b), '.distance');

    t.end();
});
