var test = require('tap').test,
    s2 = require('../');

test('S2Polyline', function(t) {
    var polyline = new s2.S2Polyline();
    t.ok(polyline, 'generates cell object');

    t.end();
});
