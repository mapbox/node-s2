var test = require('tap').test,
    s2 = require('../');

test('Point', function(t) {

    var point = new s2.Point(0, 1, 2);
    t.ok(point, 'generates cell object');
    t.equal(point.x(), 0, 'x');
    t.equal(point.y(), 1, 'y');
    t.equal(point.z(), 2, 'z');

    t.throws(function() {
        var point = new s2.Point(0, 0);
    }, 'number');

    t.end();
});
