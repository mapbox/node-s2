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

    t.equal(cover[1].lat(), 5.040252729758283, 'pt1.lat()');
    t.equal(cover[1].lng(), 5.059868846264116, 'pt1.lng()');

    t.end();
});
