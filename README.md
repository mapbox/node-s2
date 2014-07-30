[![Build Status](https://travis-ci.org/mapbox/node-s2.svg?branch=master)](https://travis-ci.org/mapbox/node-s2)

# node-s2

Bindings for the [S2 Geometry Library](https://code.google.com/p/s2-geometry-library/) into
[node.js](http://nodejs.org/).

S2 is a library that does spherical math over the world, and supports a very
fancy Hilbert curve-related indexing scheme. S2 has no documentation besides
source comments and [this presentation](https://cloudup.com/cVR0jOEufLR).
Notably it's used for [MongoDB](https://www.mongodb.org/)'s [2dsphere index](http://docs.mongodb.org/manual/core/2dsphere/),
as well as in [viewfinderco](https://github.com/viewfinderco/viewfinder)'s
[DynamoDB](http://aws.amazon.com/dynamodb/)-powered database. [s2map.com](http://s2map.com/)
also demonstrates one of the killer features of the library, 'coverings', which
are intelligently computed groups of cells that can be used to index geometries.

## Example

```js
var s2 = require('s2');

var ll = new s2.S2LatLng(0, 0);
ll.isValid(); // true
var normalized = ll.normalized(); // true
var pt = ll.toPoint();
```

## Build

    npm install
    npm build . --build-from-source
    npm test

## [Documentation: API.md](API.md)

## Notes

Some of the S2 API is not wrapped because it isn't meant to be exposed in this way,
and is blocked from wrapping by [DISALLOW_COPY_AND_ASSIGN](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml#Copy_Constructors).

* S2CellUnion
* S2Loop
* S2Polyline
* S2Polygon
* S2RegionCoverer
* S2RegionIntersection

## See Also

* [s2-geometry-javascript](https://github.com/jonatkins/s2-geometry-javascript) - an incomplete port of S2 to JavaScript.
* [gos2](https://code.google.com/p/gos2/) - very incomplete port to Go
* [viewfinder built a python wrapper](https://github.com/viewfinderco/third_party/blob/master/python-package/s2-0.2.tar.gz)
* [s2-geometry-php](https://github.com/eelf/s2-geometry-library-php) - another very incomplete port to PHP
* [interview with david blackman](http://www.fastcolabs.com/3007394/open-company/how-foursquare-building-humane-map-framework-rival-googles)
