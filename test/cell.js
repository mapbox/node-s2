var test = require('tap').test,
    s2 = require('../');

test('Cell', function(t) {

    var cell = new s2.Cell(new s2.LatLng(10, 20));
    t.ok(cell, 'generates cell object');
    t.equal(typeof cell.approxArea(), 'number');
    t.equal(typeof cell.exactArea(), 'number');
    t.equal(cell.face(), 0, 'face');
    t.equal(cell.level(), 30, 'level');
    t.equal(cell.orientation(), 3, 'level');
    t.equal(typeof cell.averageArea(1), 'number', '.averageArea');
    t.equal(cell.isLeaf(), true, '.isLeaf');
    t.ok(cell.getCapBound() instanceof s2.Cap, '.getCapBound');
    t.ok(cell.getCenter() instanceof s2.Point, '.getCenter');

    t.end();
});
