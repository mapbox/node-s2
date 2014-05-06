[![Build Status](https://travis-ci.org/mapbox/node-s2.svg?branch=master)](https://travis-ci.org/mapbox/node-s2)

# node-s2

Bindings for [S2](https://code.google.com/p/s2-geometry-library/) into [node.js](http://nodejs.org/).

## Example

```js
var s2 = require('s2');

var ll = new s2.LatLng(0, 0);
ll.isValid(); // true
var normalized = ll.normalized(); // true
var pt = ll.toPoint();
```

## Build

    npm install
    npm build .
    npm test

## [Documentation: API.md](API.md)

## See Also

* [s2-geometry-javascript](https://github.com/jonatkins/s2-geometry-javascript) - an incomplete port of S2 to JavaScript.
