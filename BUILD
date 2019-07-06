cc_library(
    name = "glad_gl3",
    visibility = ["//visibility:public"],
    hdrs = ["vendor/glad_gl3/glad/glad.h", "vendor/glad_gl3/KHR/khrplatform.h"],
    srcs = ["vendor/glad_gl3/glad.c"],
    includes = [
        "vendor/glad_gl3"
    ]
)
cc_library(
    name = "glad_gl4",
    visibility = ["//visibility:public"],
    hdrs = ["vendor/glad_gl4/glad/glad.h", "vendor/glad_gl4/KHR/khrplatform.h"],
    srcs = ["vendor/glad_gl4/glad.c"],
    includes = [
        "vendor/glad_gl4"
    ]
)
cc_library(
    name = "glad_gles3",
    visibility = ["//visibility:public"],
    hdrs = ["vendor/glad_gles3/glad/glad.h", "vendor/glad_gles3/KHR/khrplatform.h"],
    srcs = ["vendor/glad_gles3/glad.c"],
    includes = [
        "vendor/glad_gles3"
    ]
)



cc_binary(
    name = "example_glfw",
    srcs = ["test/example_glfw.cpp"],
    deps = [
        "@glfw//:glfw",
        ":glad_gl3"
    ],

    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std=c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
)

cc_binary(
    name = "example_skia",
    srcs = ["test/example_skia.cpp"],
    deps = [
        "@glfw//:glfw",
        "@skia//:skia"
    ],

    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std=c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
)
