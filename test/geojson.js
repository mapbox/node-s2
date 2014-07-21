var s2 = require('../'),
	test = require('tap').test,
	point = require('test-point'),
	linestring = require('test-linestring'),
	polygon = require('test-polygon')

test('import geojson point', function(t) {
	var ll = s2.fromGeojson(point);

	t.equal(ll.lat(), -87.64789581298828, 'lat');
    t.equal(ll.lng(), 41.88464303825411, 'lng');

	t.end();
})