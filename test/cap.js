var test = require('tap').test,
    s2 = require('../');

test('Cap', function(t) {

    var ll = new s2.Cap();
    t.ok(ll, 'generates cap object');
    t.ok(ll.getRectBound() instanceof s2.LatLngRect, '.getRectBound');
    t.equal(ll.intersects(new s2.Cap()), false, '.intersects');
    t.equal(ll.intersects(new s2.Cap()), false, '.contains');
    t.ok(ll.complement() instanceof s2.Cap, '.complement');

    t.end();
});
