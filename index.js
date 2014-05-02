var s2 = require('./build/Release/_s2.node');

console.log(s2);

var i = new s2.Interval(1, 2);

console.log(i);

console.log(s2.latLngToPoint(0, 0));
