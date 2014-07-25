var test = require('tap').test,
    s2 = require('../');

test('getCovering', function(t) {
    var input = [
        [10, 10],
        [30, 20],
        [20, 20]
    ].map(function(p) {
        return (new s2.S2LatLng(p[0], p[1])).normalized().toPoint();
    });

    var cover = s2.getCover([input]);

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
        [3, 30],
        [0, 20],
        [20, 20]
    ].map(function(p) {
        return (new s2.S2LatLng(p[0], p[1])).normalized().toPoint();
    });

    var cover = s2.getCover([input], {
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

test('getCovering - polygon with hole', function(t) {
    var outerRing = [
        [
          15.776367187499998,
          51.67255514839676
        ],
        [
          7.71240234375,
          47.931066347509784
        ],
        [
          17.9296875,
          45.72152152227954
        ]
    ].map(function(p) {
        return (new s2.S2LatLng(p[0], p[1])).normalized().toPoint();
    });

    var holeRing = [
        [
          14.853515625,
          49.75287993415023
        ],
        [
          12.7001953125,
          48.821332549646634
        ],
        [
          15.18310546875,
          47.97521412341618
        ]
    ].map(function(p) {
        return (new s2.S2LatLng(p[0], p[1])).normalized().toPoint();
    });

    var cover = s2.getCover([outerRing, holeRing], {
        type: 'polygon'
    });

    t.ok(cover, 'generates cover object');
    t.equal(cover.length, 8, 'cover.length');
    t.end();
});

test('getCovering - multipolygon', function(t) {
    var ring1 = [
        [
          -2.48565673828125,
          17.32179844407804
        ],
        [
          -2.728729248046875,
          17.180155043474496
        ],
        [
          -2.49114990234375,
          17.106667613984445
        ]
    ].map(function(p) {
        return (new s2.S2LatLng(p[0], p[1])).normalized().toPoint();
    });

    var ring2 = [
        [
          -3.519744873046875,
          17.14603949574698
        ],
        [
          -3.62823486328125,
          16.787449898410646
        ],
        [
          -3.393402099609375,
          16.92807754169301
        ]
    ].map(function(p) {
        return (new s2.S2LatLng(p[0], p[1])).normalized().toPoint();
    });

    var cover = s2.getCover([ring1, ring2], {
        type: 'multipolygon'
    });

    t.ok(cover, 'generates cover object');
    t.equal(cover.length, 8, 'cover.length');
    t.end();
});