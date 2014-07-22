var test = require('tap').test,
    s2 = require('../');

test('getCovering', function(t) {
    var input = [
        [0, 0],
        [0, 20],
        [20, 20]
    ].map(function(p) {
        return (new s2.S2LatLng(p[0], p[1])).normalized().toPoint();
    });

    var cover = s2.getCover(input);

    t.ok(cover, 'generates cover object');
    t.equal(cover.length, 8, 'cover.length');
    t.end();
});

test('getCovering - llrect', function(t) {
    var ll2 = new s2.S2LatLngRect(new s2.S2LatLng(10, 20), new s2.S2LatLng(20, 30));

    var llcover = s2.getCover(ll2, {
        max_cells: 100
    });

    t.equal(llcover.length, 34, 'cover.length');
    t.end();
});

test('getCovering - cell', function(t) {
    var cell = new s2.S2Cell(new s2.S2LatLng(10, 20));

    var llcover = s2.getCover(cell, {
        max_cells: 100
    });

    t.equal(llcover.length, 1, 'cover.length');
    t.end();
});

/*test('getCovering - cap', function(t) {
    var cap = new s2.S2Cap();

    var llcover = s2.getCover(cap, {
        max_cells: 100
    });

    t.equal(llcover.length, 0, 'cover.length');
    t.end();
});*/

test('getCovering - invalid', function(t) {
    t.throws(function() {
        var llcover = s2.getCover(1, {
            max_cells: 100
        });
    });
    t.end();
});

test('invalid - none', function(t) {
    t.throws(function() {
        new s2.getCover();
    }, 'invalid arguments');
    t.end();
});

test('getCovering - polygon', function(t) {
    var input = [
        [0, 0],
        [0, 20],
        [20, 20]
    ].map(function(p) {
        return (new s2.S2LatLng(p[0], p[1])).normalized().toPoint();
    });

    var cover = s2.getCover(input, {
        type: 'polygon',
        min: 1,
        max: 30,
        max_cells: 8
    });

    t.ok(cover, 'generates cover object');
    t.equal(cover.length, 8, 'cover.length');
    t.end();
});

test('getCovering - polyline', function(t) {
    var input = [
        [0, 2],
        [1, 1],
        [0, 0]
    ].map(function(p) {
        return (new s2.S2LatLng(p[0], p[1])).normalized().toPoint();
    });

    var cover = s2.getCover(input, {
        type: 'polyline'
    });

    t.ok(cover, 'generates cover object');
    t.equal(cover.length, 8, 'cover.length');
    t.end();
});