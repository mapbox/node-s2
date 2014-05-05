var test = require('tap').test,
    s2 = require('../');

test('LatLng', function(t) {

    var ll = new s2.LatLng(10, 20);
    t.ok(ll, 'generates latlng object');
    t.equal(ll.lat(), 10, 'lat()');
    t.equal(ll.lng(), 20, 'lon()');
    t.equal(ll.is_valid(), true, 'is_valid()');

    var invalid = new s2.LatLng(1000, 2000);
    t.equal(invalid.is_valid(), false, 'is_valid()');
    t.equal(invalid.normalized().lat(), 90, 'normalized()');

    t.end();
});
