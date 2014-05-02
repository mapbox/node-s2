{
  "targets": [
    {
      "target_name": "_s2",
      "sources": [
        "./geometry/strings/*.cc",
        "./geometry/util/coding/*.cc",
        "./geometry/util/math/*.cc",
        "./geometry/s2cap.cc",
        "./geometry/s2cellunion.cc",
        "./geometry/s2loop.cc",
        "./geometry/s2pointregion.cc",
        "./geometry/s2latlng.cc",
        "./geometry/s2edgeutil.cc",
        "./geometry/s2region.cc",
        "./geometry/s2regionunion.cc",
        "./geometry/s2polyline.cc",
        "./geometry/s2edgeindex.cc",
        "./geometry/s1angle.cc",
        "./geometry/s1interval.cc",
      ],
      "include_dirs": [
        "./geometry/",
        "./geometry/base/",
        "./geometry/util/",
        "./geometry/util/math/",
        "./geometry/strings/"
      ],
      "cflags_cc!": [
        "-Wignored-qualifiers"
      ]
    }
  ]
}
