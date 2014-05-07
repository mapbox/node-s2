var test = require('tap').test,
    s2 = require('../');

test('getCovering', function(t) {

    var cover = new s2.getCover([
        new s2.S2LatLng(0, 0),
        new s2.S2LatLng(0, 10),
        new s2.S2LatLng(10, 10),
        new s2.S2LatLng(10, 0),
        new s2.S2LatLng(0, 0)
    ]);

    t.ok(cover, 'generates cover object');
    t.equal(cover.length, 3, 'cover.length');

    t.throws(function() {
        new s2.getCover();
    }, 'invalid arguments');

    t.end();
});
