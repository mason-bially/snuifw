load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def snuifw_deps():
    if "glfw" not in native.existing_rules():
        http_archive(
            name = "glfw",
            urls = ["https://github.com/mason-bially/glfw/archive/3ba1ccd78136ac76c21ca8ae1481b667617a05e3.zip"],
            strip_prefix = "glfw-3ba1ccd78136ac76c21ca8ae1481b667617a05e3",
            sha256 = "726f0dfa033a4aabd4ca14a9349053a8a97b8197a732cbcbfac5bf57a19ac859",
        )

    if "skia" not in native.existing_rules():
        http_archive(
            name = "skia",
            urls = ["https://github.com/mason-bially/skia-dist/archive/3be66c7cf310b81000845f1887ddc8708743cbb5.zip"],
            strip_prefix = "skia-dist-3be66c7cf310b81000845f1887ddc8708743cbb5",
            sha256 = "e593565a4ae24dcca6a0b9bf67f1736c081bf21b824d85df2d919142bb552546",
        )
