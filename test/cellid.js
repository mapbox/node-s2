var test = require('tap').test,
    s2 = require('../');

test('CellId', function(t) {

    var cell = new s2.CellId();
    t.ok(cell, 'generates cellid object');
    t.ok(cell.level(), 'level');
    t.equal(cell.toToken(), 'X', 'toToken');
    t.equal(cell.toString(), "Invalid: 0000000000000000", 'toString');
    t.ok(cell.toPoint() instanceof s2.Point, 'toPoint');

    t.end();
});

