var test = require('tap').test,
    s2 = require('../');

var dc = {
  "type": "FeatureCollection",
  "features": [
    {
      "type": "Feature",
      "properties": {},
      "geometry": {
        "type": "Polygon",
        "coordinates": [
          [
            [
              -77.1240234375,
              38.93537787875442
            ],
            [
              -77.03887939453125,
              38.998908579579016
            ],
            [
              -76.90773010253906,
              38.89317057287496
            ],
            [
              -77.1240234375,
              38.93537787875442
            ]
          ]
        ]
      }
    }
  ]
};

test('_getCover', function(t) {

    var points = [
        new s2.LatLng(0, 0),
        new s2.LatLng(10, 0),
        new s2.LatLng(10, 10),
        new s2.LatLng(0, 10),
        new s2.LatLng(0, 0)];

    var cover = s2._getCover(points);

    t.ok(cover[1] instanceof s2.Cell, 'creates cells');

    t.end();
});

test('getCover', function(t) {

    var cover = s2.getCover(dc);

    t.ok(cover[1] instanceof s2.Cell, 'creates cells');

    t.end();
});
