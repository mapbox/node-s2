var test = require('tap').test,
    s2 = require('../');

test('S2Cell', function(t) {

    var cell = new s2.S2Cell(new s2.S2LatLng(10, 20));
    t.ok(cell, 'generates cell object');
    t.equal(typeof cell.approxArea(), 'number');
    t.equal(typeof cell.exactArea(), 'number');
    t.equal(cell.face(), 0, 'face');
    t.equal(cell.level(), 30, 'level');
    t.equal(cell.orientation(), 3, 'level');
    t.equal(typeof cell.averageArea(1), 'number', '.averageArea');
    t.equal(cell.isLeaf(), true, '.isLeaf');
    t.ok(cell.getCapBound() instanceof s2.S2Cap, '.getCapBound');
    t.ok(cell.getCenter() instanceof s2.S2Point, '.getCenter');
    t.ok(cell.id() instanceof s2.S2CellId, '.id');
    t.equal(cell.toString(), '0/202110010010032001303303333203', '.id');

    t.deepEqual(cell.toGeoJSON(), {
        type: 'Polygon',
        coordinates: [
            [
            [19.99999996053861,9.999999997863615],
            [20.000000051405298,9.999999992207837],
            [20.000000051405298,10.000000073270334],
            [19.99999996053861,10.000000078926108],
            [19.99999996053861,9.999999997863615]
        ]
        ]
    }, '.toGeoJSON');

    t.throws(function() {
        new s2.S2Cell('foo');
    });

    var cellFromId = new s2.S2Cell(new s2.S2CellId());
    t.ok(cellFromId, 'generates cell from id');

    t.end();
});
