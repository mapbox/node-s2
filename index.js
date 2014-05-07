var normalize = require('geojson-normalize');
module.exports = require('./build/Release/_s2.node');

module.exports.getCover = function(gj) {
    var featureCollection = normalize(gj);
    if (featureCollection.features.length !== 1) return [];
    if (featureCollection.features[0].geometry.type !== 'Polygon') return [];

    var latLngs = featureCollection.features[0]
        .geometry
        .coordinates[0]
        .map(function(_) {
            return new module.exports.S2LatLng(_[1], _[1]);
        });

    return module.exports._getCover(latLngs);
};
