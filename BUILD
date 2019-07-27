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

cc_binary(
    name = "example_glfw",
    srcs = ["test/example_glfw.cpp"],
    deps = [
        "@glfw//:glfw",
        ":gl3"
    ],

    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
)


cc_binary(
    name = "example_skia",
    srcs = ["test/example_skia.cpp"],
    deps = [
        "@glfw//:glfw",
        "@skia//:skia",
    ],

    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
)

cc_library(
    name = "snuifw",
    hdrs = glob(["src/**/*.h*"]),
    srcs = glob(["src/**/*.c*"]),
    includes = ["src"],
    deps = [
        "@immer//:immer",
        "@lager//:lager",
        #"@yoga//:yoga",
        "@glfw//:glfw",
        "@skia//:skia",
        #"@h3//:h3"
    ],

    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
)

cc_binary(
    name = "example_dom",
    srcs = glob(["test/example_dom.cpp"]),
    deps = [
        ":snuifw",
    ],

    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
)

cc_binary(
    name = "example_model",
    srcs = glob(["test/example_model.cpp"]),
    deps = [
        ":snuifw",
    ],

    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17", "/experimental"],
        "//conditions:default": ["-std=c++17"],
    }),
)
