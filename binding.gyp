{
  "targets": [
    {
      "target_name": "_s2",
      "sources": [
        "./s2.cc",
        "./geometry/strings/*.cc",
        "./geometry/strings/*.cc",
        "./geometry/util/coding/*.cc",
        "./geometry/util/math/*.cc",
        "./geometry/s1angle.cc",
        "./geometry/s1interval.cc",
        "./geometry/s2cap.cc",
        "./geometry/s2cellunion.cc",
        "./geometry/s2edgeindex.cc",
        "./geometry/s2edgeutil.cc",
        "./geometry/s2latlng.cc",
        "./geometry/s2loop.cc",
        "./geometry/s2pointregion.cc",
        "./geometry/s2polyline.cc",
        "./geometry/s2r2rect.cc",
        "./geometry/s2region.cc",
        "./geometry/s2regionunion.cc",
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
