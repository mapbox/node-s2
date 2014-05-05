var test = require('tap').test,
    s2 = require('../');

test('getCover', function(t) {

    var cover = new s2.getCover([]);
    t.ok(cover);

    t.end();
});
