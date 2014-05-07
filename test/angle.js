var test = require('tap').test,
    s2 = require('../');

test('Angle', function(t) {

    var ll = new s2.Angle(new s2.Point(0, 0, 0), new s2.Point(0, 0, 0));
    t.ok(ll, 'generates angle object');
    t.equal(ll.normalize(), ll, '.normalize');

    t.throws(function() {
        new s2.Angle(1, 1);
    }, 'invalid constructor');

    t.end();
});
