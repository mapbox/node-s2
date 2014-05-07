var test = require('tap').test,
    s2 = require('../');

test('S2Cap', function(t) {

    var ll = new s2.S2Cap();
    t.ok(ll, 'generates cap object');
    t.ok(ll.getRectBound() instanceof s2.S2LatLngRect, '.getRectBound');
    t.equal(ll.intersects(new s2.S2Cap()), false, '.intersects');
    t.equal(ll.intersects(new s2.S2Cap()), false, '.contains');
    t.ok(ll.complement() instanceof s2.S2Cap, '.complement');

    t.end();
});
