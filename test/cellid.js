var test = require('tap').test,
    s2 = require('../');

test('CellId', function(t) {

    var cell = new s2.CellId();
    t.ok(cell, 'generates cellid object');
    t.ok(cell.level(), 'level');
    t.equal(cell.toToken(), 'X', 'toToken');
    t.equal(cell.toString(), "Invalid: 0000000000000000", 'toString');
    t.ok(cell.toPoint() instanceof s2.Point, 'toPoint');
    t.ok(cell.parent() instanceof s2.CellId, 'parent');
    t.ok(cell.prev() instanceof s2.CellId, 'prev');
    t.ok(cell.next() instanceof s2.CellId, 'next');
    t.equal(cell.isFace(), true, 'isFace');
    t.equal((new s2.LatLng(cell.toPoint())).toString(), '-35.264390,-45.000000');

    var fromlat = new s2.CellId(new s2.LatLng(40, 20));
    t.ok(fromlat, 'generates cellid object from latlng');
    t.equal((new s2.LatLng(fromlat.toPoint())).toString(), '40.000000,20.000000', 'gets values');


    var frompoint = new s2.CellId(new s2.LatLng(40, 20).toPoint());
    t.ok(frompoint, 'generates cellid object from point');
    t.equal((new s2.LatLng(frompoint.toPoint())).toString(), '40.000000,20.000000', 'gets values');

    t.end();
});

