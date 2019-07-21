workspace(name = "ninja_ob1_snuifw")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@ninja_ob1_snuifw//:snuifw/deps.bzl", "snuifw_deps")


load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")


git_repository(
   name = "com_github_nelhage_rules_boost",
   commit = "eafab11dbd1d4cd1151f8407bd6ed81d1240d122",
   remote = "https://github.com/nelhage/rules_boost",
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()

http_archive(
    name = "h3",
    urls = ["https://github.com/cgrinker/h3/archive/99f6ed5e058db0b50614c2c7f204c468d99a9ab3.zip"],
    strip_prefix = "h3-99f6ed5e058db0b50614c2c7f204c468d99a9ab3",
    sha256 = "b953b53852abc698905074db51a8e76ed53bda8b34d233b687abcaebf1163361",
)




http_archive(
    name = "immer",
    urls = ["https://github.com/cgrinker/immer/archive/5d45c1c24cd5388187855aa1356631ecfe5fbd70.zip"],
    strip_prefix = "immer-5d45c1c24cd5388187855aa1356631ecfe5fbd70",
    sha256 = "b0d27547978ece7a91753cb8873effea6e5fae6398722091af11226f3a97c963"
)



snuifw_deps()
load("@org_cultlang_stdext//stdext:deps.bzl", "stdext_deps")
stdext_deps()


