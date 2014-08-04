var test = require('tap').test,
    s2 = require('../');

test('S2Cap', function(t) {

    var ll = new s2.S2Cap(new s2.S2Point(0, 0, 0), 1);
    var ll2 = new s2.S2Cap(new s2.S2Point(1, 1, 1), 1);
    t.ok(ll, 'generates cap object');
    t.ok(ll.getRectBound() instanceof s2.S2LatLngRect, '.getRectBound');
    t.equal(ll.intersects(ll2), true, '.intersects');
    t.equal(ll.interiorIntersects(ll2), true, '.interiorIntersects');
    t.ok(ll.complement() instanceof s2.S2Cap, '.complement');

    t.end();
});
