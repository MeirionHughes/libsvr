{
  "targets": [
    {
      "target_name": "libsvr",
      "sources": [
        "libsvr.cc",
        "lib/CrossValidation.cpp",
        "lib/File.cpp",
        "lib/Forget.cpp",
        "lib/Kernel.cpp",
        "lib/OnlineSVR.cpp",
        "lib/Show.cpp",
        "lib/Stabilize.cpp",
        "lib/Train.cpp",
        "lib/Variations.cpp"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "cflags": [
        "-std=c++11",
        "-stdlib=libc++",
        "/Zp"
      ]
    }
  ]
}