var test = require('tap').test,
    s2 = require('../');

test('S2LatLngRect', function(t) {

    var ll = new s2.S2LatLngRect(new s2.S2LatLng(10, 20));
    t.ok(ll, 'generates latlng object');
    t.ok(ll.center(), '.center');
    t.equal(ll.area(), 0, '.area');
    t.ok(ll.size() instanceof s2.S2LatLng, '.size');
    t.ok(ll.getCapBound() instanceof s2.S2Cap, '.getCapBound');
    t.ok(ll.getVertex(0), '.getVertex');
    t.equal(ll.contains(new s2.S2LatLng(50, 50)), false, '.contains');

    t.throws(function() {
        new s2.S2LatLngRect(1);
    });

    t.end();
});
