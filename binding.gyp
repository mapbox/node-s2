{
  "targets": [
    {
      "target_name": "_s2",
      "sources": [
        "./latlng.cc",
        "./geometry/s2.cc",
        "./geometry/s1interval.cc",
        "./geometry/util/math/exactfloat/exactfloat.cc",
	    "./geometry/s2cap.cc",
	    "./geometry/s2cell.cc",
	    "./geometry/s2cellunion.cc",
	    "./geometry/s2cellid.cc",
	    "./geometry/s2edgeindex.cc",
	    "./geometry/s2edgeutil.cc",
	    "./geometry/s2latlngrect.cc",
	    "./geometry/s2loop.cc",
	    "./geometry/s2pointregion.cc",
	    "./geometry/s2latlng.cc",
	    "./geometry/s2polygon.cc",
	    "./geometry/s2polygonbuilder.cc",
	    "./geometry/s2polyline.cc",
	    "./geometry/s2r2rect.cc",
	    "./geometry/s2region.cc",
	    "./geometry/s2regioncoverer.cc",
	    "./geometry/s2regionintersection.cc",
        "./s2.cc",
      ],
      "defines": [
        'NDEBUG'
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "./geometry/",
        "./geometry/base/",
        "./geometry/util/",
        "./geometry/util/math/",
        "./geometry/strings/"
      ],
      "cflags_cc!": [
        "-Wignored-qualifiers"
      ],
      'conditions': [
        ['OS=="win"', {},
        {
            'xcode_settings': {
              'OTHER_CPLUSPLUSFLAGS':[
                '-Wno-deprecated',
                '-DARCH_K8 -DS2_USE_EXACTFLOAT'
              ],
              'OTHER_LDFLAGS':['-bundle -flat_namespace -undefined suppress'],
              'GCC_ENABLE_CPP_RTTI': 'YES',
              'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
            }
        }]
      ]
    }
  ]
}
