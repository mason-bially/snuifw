cc_library(
    name = "gl3",
    visibility = ["//visibility:public"],
    hdrs = ["vendor/glad_gl3/glad/glad.h", "vendor/glad_gl3/KHR/khrplatform.h"],
    srcs = ["vendor/glad_gl3/glad.c"],
    includes = [
        "vendor/glad_gl3"
    ]
)
cc_library(
    name = "gl4",
    visibility = ["//visibility:public"],
    hdrs = ["vendor/glad_gl4/glad/glad.h", "vendor/glad_gl4/KHR/khrplatform.h"],
    srcs = ["vendor/glad_gl4/glad.c"],
    includes = [
        "vendor/glad_gl4"
    ]
)

cc_library(
    name = "gles3",
    visibility = ["//visibility:public"],
    hdrs = ["vendor/glad_gles3/glad/glad.h", "vendor/glad_gles3/KHR/khrplatform.h"],
    srcs = ["vendor/glad_gles3/glad.c"],
    includes = [
        "vendor/glad_gles3"
    ]
)

cc_library(
    name = "snuifw",
    visibility = ["//visibility:public"],
    
    deps = [
        "//src/snuifw:full"
    ],

    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
)
