load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def snuifw_deps():
    if "glfw" not in native.existing_rules():
        http_archive(
            name = "glfw",
            urls = ["https://github.com/mason-bially/glfw/archive/52e7f2221fbadeeab89f093e2d25e9f314a8c431.zip"],
            strip_prefix = "glfw-52e7f2221fbadeeab89f093e2d25e9f314a8c431",
            sha256 = "832936e750fc23beaba91106beb9949c1b294ebd386c9962cf6c5da7098c613c",
        )

    if "skia" not in native.existing_rules():
        http_archive(
            name = "skia",
            urls = ["https://github.com/mason-bially/skia-dist/archive/500838b97713b3c1c50d0e9e86d39878e48b0fb3.zip"],
            strip_prefix = "skia-dist-500838b97713b3c1c50d0e9e86d39878e48b0fb3",
            sha256 = "cd1c4e6db93423f07395bc9228e4729a8fc610b887db2aa5c2bf9412533aa6f7",
        )

    if "yoga" not in native.existing_rules():
        http_archive(
            name = "yoga",
            urls = ["https://github.com/cgrinker/yoga/archive/5cd6256843499537f1ae65eaa92c7376be22e99e.zip"],
            strip_prefix = "yoga-5cd6256843499537f1ae65eaa92c7376be22e99e",
            #sha256 = "",
        )

    if "org_cultlang_stdext" not in native.existing_rules():
        http_archive(
                name = "org_cultlang_stdext",
                urls = ["https://github.com/cultlang/stdext/archive/6c067080a7569bb920302c5d5d6e607cbaefca85.zip"],
                strip_prefix = "stdext-6c067080a7569bb920302c5d5d6e607cbaefca85",
                #sha256 = "47bfbcd67de242ed0010e9e35c369adadac1b8e8b4f3d081ba432dc0e88471f7",
        )
    if "lager" not in native.existing_rules():
        http_archive(
            name = "lager",
            urls = ["https://github.com/cgrinker/lager/archive/628b534bf253d905c5db45bcc981ba4f4ef56442.zip"],
            strip_prefix = "lager-628b534bf253d905c5db45bcc981ba4f4ef56442",
            sha256 = "e8cde886b5a87a07c7027d2f12a1cfb387003f7edabf7e083768edd8f811f9f3"
        )