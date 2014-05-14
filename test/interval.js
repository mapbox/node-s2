var test = require('tap').test,
    s2 = require('../');

test('S1Interval', function(t) {

    var ll = new s2.S1Interval(0);
    t.ok(ll, 'generates angle object');
    t.equal(ll.hi(), 0, 'hi');
    t.equal(ll.lo(), 0, 'lo');
    t.equal(ll.length(), 0, 'length');
    t.equal(ll.contains(0), true, 'contains');
    t.equal(ll.complementLength(), Math.PI, '.complementLength');

    t.end();
});
