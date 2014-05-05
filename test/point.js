var test = require('tap').test,
    s2 = require('../');

test('Point', function(t) {

    var point = new s2.Point(0, 0, 0);
    t.ok(point, 'generates cell object');

    t.throws(function() {
        var point = new s2.Point(0, 0);
    }, 'number');

    t.end();
});
