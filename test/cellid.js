var test = require('tap').test,
    s2 = require('../');

test('S2CellId', function(t) {

    var cell = new s2.S2CellId();
    t.ok(cell, 'generates cellid object');
    t.ok(cell.level(), 'level');
    t.equal(cell.toToken(), 'X', 'toToken');
    t.equal(cell.toString(), "Invalid: 0000000000000000", 'toString');
    t.ok(cell.toPoint() instanceof s2.S2Point, 'toPoint');
    t.ok(cell.parent() instanceof s2.S2CellId, 'parent');
    t.ok(cell.prev() instanceof s2.S2CellId, 'prev');
    t.ok(cell.next() instanceof s2.S2CellId, 'next');
    t.ok(cell.rangeMin() instanceof s2.S2CellId, 'rangeMin');
    t.ok(cell.rangeMax() instanceof s2.S2CellId, 'rangeMax');
    t.ok(cell.child(0) instanceof s2.S2CellId, 'rangeMax');
    t.equal(cell.isFace(), true, 'isFace');
    t.equal((new s2.S2LatLng(cell.toPoint())).toString(), '-35.264390,-45.000000');

    var fromlat = new s2.S2CellId(new s2.S2LatLng(40, 20));
    t.ok(fromlat, 'generates cellid object from latlng');
    t.equal((new s2.S2LatLng(fromlat.toPoint())).toString(), '40.000000,20.000000', 'gets values');
    t.equal(typeof fromlat.id(), 'number', '.id');
    t.equal(fromlat.level(), 30);
    t.equal(fromlat.toString(), '0/212231203032221333101101033102');
    t.equal(fromlat.parent().level(), 29);
    t.equal(fromlat.parent().toString(), '0/21223120303222133310110103310');

    var frompoint = new s2.S2CellId(new s2.S2LatLng(40, 20).toPoint());
    t.ok(frompoint, 'generates cellid object from point');
    t.equal((new s2.S2LatLng(frompoint.toPoint())).toString(), '40.000000,20.000000', 'gets values');

    var fromstr = new s2.S2CellId('21223120303222133310110103310');
    t.ok(fromstr);

    t.end();
});

