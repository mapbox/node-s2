var test = require('tap').test,
    s2 = require('../');

test('Cell', function(t) {

    var cell = new s2.Cell(new s2.LatLng(10, 20));
    t.ok(cell, 'generates cell object');
    t.equal(typeof cell.approxArea(), 'number');
    t.equal(typeof cell.exactArea(), 'number');
    t.equal(typeof cell.averageArea(1), 'number');

    t.end();
});
