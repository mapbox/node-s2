var test = require('tap').test,
    s2 = require('../');

test('LatLngRect', function(t) {

    var ll = new s2.LatLngRect(new s2.LatLng(10, 20));
    t.ok(ll, 'generates latlng object');
    t.ok(ll.center(), '.center');
    t.equal(ll.area(), 0, '.area');
    t.ok(ll.size() instanceof s2.LatLng, '.size');
    t.ok(ll.getCapBound() instanceof s2.Cap, '.getCapBound');
    t.ok(ll.getVertex(0), '.getVertex');
    t.equal(ll.contains(new s2.LatLng(50, 50)), false, '.contains');

    t.end();
});
