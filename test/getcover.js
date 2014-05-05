var test = require('tap').test,
    s2 = require('../');

test('getCover', function(t) {

    var points = [
        new s2.LatLng(0, 0),
        new s2.LatLng(10, 0),
        new s2.LatLng(10, 10),
        new s2.LatLng(0, 10),
        new s2.LatLng(0, 0)];

    var cover = s2.getCover(points);

    t.ok(cover[1] instanceof s2.Cell, 'creates cells');

    t.end();
});
