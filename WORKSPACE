workspace(name = "ninja_ob1_snuifw")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@ninja_ob1_snuifw//:snuifw/deps.bzl", "snuifw_deps")


load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")


git_repository(
   name = "com_github_nelhage_rules_boost",
   commit = "6d6fd834281cb8f8e758dd9ad76df86304bf1869",
   shallow_since = "1543903644 -0800",
   remote = "https://github.com/nelhage/rules_boost",
)

http_archive(
    name = "boost",
    build_file = "@com_github_nelhage_rules_boost//:BUILD.boost",
    sha256 = "882b48708d211a5f48e60b0124cf5863c1534cd544ecd0664bb534a4b5d506e9",
    strip_prefix = "boost_1_70_0",
    urls = [
        "https://%s.dl.sourceforge.net/project/boost/boost/1.70.0/boost_1_70_0.tar.gz" % m
        for m in ["phoenixnap", "newcontinuum", "cfhcable", "superb-sea2", "cytranet", "iweb", "gigenet", "ayera", "astuteinternet", "pilotfiber", "svwh"]
    ],
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()


http_archive(
    name = "immer",
    urls = ["https://github.com/cgrinker/immer/archive/5d45c1c24cd5388187855aa1356631ecfe5fbd70.zip"],
    strip_prefix = "immer-5d45c1c24cd5388187855aa1356631ecfe5fbd70",
    sha256 = "b0d27547978ece7a91753cb8873effea6e5fae6398722091af11226f3a97c963"
)



snuifw_deps()



