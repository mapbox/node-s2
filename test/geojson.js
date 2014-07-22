var s2 = require('../'),
	test = require('tap').test,
	point = require('test-point'),
	linestring = require('test-linestring'),
	polygon = require('test-polygon')

test('import geojson point', function(t) {
	var ll = s2.fromGeojson(point);

	t.equal(ll.lng(), -87.64789581298828, 'lng');
    t.equal(ll.lat(), 41.88464303825411, 'lat');

	t.end();
})

test('import geojson linestring', function(t) {
	var s2Line = s2.fromGeojson(linestring);

    t.equal(s2Line.length, 19, 'number of vertices')
    t.ok(s2Line[0].x(), 'loaded coordinates');
    t.ok(s2Line[0].y(), 'loaded coordinates');
    t.ok(s2Line[1].x(), 'loaded coordinates');
    t.ok(s2Line[1].y(), 'loaded coordinates');

    t.end();
})

test('import geojson polygon', function(t) {
	var s2Polygon = s2.fromGeojson(polygon);

    t.equal(s2Polygon.length, 30, 'number of vertices');
    t.ok(s2Polygon[0].x(), 'loaded coordinates');
    t.ok(s2Polygon[0].y(), 'loaded coordinates');
    t.ok(s2Polygon[1].x(), 'loaded coordinates');
    t.ok(s2Polygon[1].y(), 'loaded coordinates');

    var cover = s2.getCover(s2Polygon, {
        type: 'polygon',
        min: 1,
        max: 30,
        max_cells: 8
    });

    t.end();
})