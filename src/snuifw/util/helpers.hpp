#pragma once

namespace snuifw {
namespace util
{

    // https://en.cppreference.com/w/cpp/utility/variant/visit
    template<class... Ts> struct visitor : Ts... { using Ts::operator()...; };
    template<class... Ts> visitor(Ts...) -> visitor<Ts...>;

}}
