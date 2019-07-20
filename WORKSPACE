workspace(name = "ninja_ob1_snuifw")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@ninja_ob1_snuifw//snuifw:deps.bzl", "snuifw_deps")
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
    name = "lager",
    urls = ["https://github.com/cgrinker/lager/archive/628b534bf253d905c5db45bcc981ba4f4ef56442.zip"],
    strip_prefix = "lager-628b534bf253d905c5db45bcc981ba4f4ef56442",
    sha256 = "e8cde886b5a87a07c7027d2f12a1cfb387003f7edabf7e083768edd8f811f9f3"
)
snuifw_deps()
