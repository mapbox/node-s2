{
  "targets": [
    {
      "target_name": "_s2",
      "sources": [
        "./geometry/util/math/mathutil.cc",
        "./geometry/util/math/mathlimits.cc"
      ],
      "include_dirs": [
        "./geometry/",
        "./geometry/base/",
        "./geometry/util/",
        "./geometry/util/math/",
        "./geometry/strings/"
      ],
      "cflags+": [
        "-Wno-deprecated",
        "-DARCH_K8",
        "-O",
        "-DNDEBUG",
        "-DS2_USE_EXACTFLOAT",
        "-fPIC"
      ]
    }
  ]
}
