var s2 = require('./build/Release/_s2.node');
module.exports = s2;

s2.S2LatLng.prototype.toGeoJSON = function() {
    return {
        type: 'Point',
        coordinates: [this.lng(), this.lat()]
    };
};

s2.S2Cell.prototype.toGeoJSON = function() {
    var vs = [];
    for (var i = 0; i < 4; i++) {
        vs.push(new s2.S2LatLng(this.getVertex(i)));
    }
    vs.push(new s2.S2LatLng(this.getVertex(0)));
    return {
        type: 'Polygon',
        coordinates: [
            vs.map(function(v) {
                return [v.lng(), v.lat()];
            })
        ]
    };
};

s2.S2LatLngRect.prototype.toGeoJSON = function() {
    var vs = [];
    for (var i = 0; i < 4; i++) {
        vs.push(this.getVertex(i));
    }
    vs.push(this.getVertex(0));
    return {
        type: 'Polygon',
        coordinates: [
            [
                vs.map(function(v) {
                    return [v.lng(), v.lat()];
                })
            ]
        ]
    };
};

s2.S2Point.prototype.toArray = function() {
    return [this.x(), this.y(), this.z()];
};

s2.S2Point.prototype.toString = function() {
    return this.toArray().toString();
};

s2.fromGeojson = function(geojson){
    if(geojson.type === 'Feature'){
        geojson = geojson.geometry;
    }

    if (geojson.type === 'Point') {
        var ll = new s2.S2LatLng(geojson.coordinates[1],
                        geojson.coordinates[0]);
        return ll;
    } else if(geojson.type === 'LineString') {
        return geojson.coordinates.map(coordinateToPoint);
    } else if (geojson.type === 'Polygon') {
        geojson.coordinates = deloop(geojson.coordinates);
        return geojson.coordinates[0].map(coordinateToPoint);
    }
}

function coordinateToPoint(p) {
    return (new s2.S2LatLng(p[1], p[0])).normalized().toPoint();
}

function deloop(coordinates) {
    if (coordinates[0][0] === coordinates[0][coordinates.length - 1]) {
        coordinates[0].pop();
    }
    return coordinates;
}
