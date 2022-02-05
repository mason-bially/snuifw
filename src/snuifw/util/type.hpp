#pragma once

#include <inttypes.h>
#include <concepts>

/*
 * Another attempt at a simple type reflection library.
 * 
 * Core Insights:
 * - The pointer to the static type header is the "id" integer of the type.
 *   - This is not as fast as monotonically increasing
 *     - But that is hard to make use of anyway, falling back to std::unordered_map is fine
 *   - This can be used in symbol tables that support it
 * - Actual reflection information outside of equality is stored elsewhere.
 *   - e.g. in external "registries".
 * - The type header can store static stuff like names of strings and so on
 * - We can add nice features like reflection builders later, hopefully with syndicate
 */

namespace snuifw::util
{
    struct Type;
    struct TypeHeader;

    struct Type
    {
        uintptr_t value;
    };

    struct TypeHeader
    {
        char const* name;

        operator Type()
        {
            return { reinterpret_cast<uintptr_t>(this) };
        }
    };
}

namespace snuifw::type
{
    template <typename T>
    concept HasCppTypeName = requires(T) {
        Same<std::decay_t<decltype(T::c_cppTypeName)>, char const*>;
    };

    template<typename T>
    constexpr char const* name()
    {
        return "unknown";
    }

    template<HasCppTypeName T>
    constexpr char const* name()
    {
        return T::c_cppTypeName;
    }

    template<> constexpr char const* name<::snuifw::util::Type>() { return "snuifw::util::Type"; }
    template<> constexpr char const* name<::snuifw::util::TypeHeader>() { return "snuifw::util::TypeHeader"; }



    template <typename T>
    concept HasTypeHeader = requires(T) {
        Same<T::s_type, util::TypeHeader>;
    };

    template<typename T>
    constexpr util::Type id()
    {
        return { reinterpret_cast<uintptr_t>(nullptr) };
    }

    template<HasTypeHeader T>
    constexpr util::Type id()
    {
        return T::s_type;
    }
}

/*
 * Usage of the below DeclareType helper:
 * - To actually create one in a class, in the header class use:
 *   `static DeclareType<MyTypeName> s_type;`
 *   and in the code file:
 *   `DeclareType<MyTypeName> MyTypeName::s_type;`
 *   or
 *   `decltype(MyTypeName::s_type) MyTypeName::s_type;`
 * - `c_cppTypeName` to add a runtime name, should be formatted exactly as:
 *   `static constexpr char const c_cppTypeName[] = "snuifw::example::MyTypeName";`
 *   or free function template overload (in namespace `snuifw::type`)
 *   `template<> constexpr char const* name<::snuifw::example::MyTypeName>() { return "snuifw::example::MyTypeName"; }`
 */

namespace snuifw::util
{
    template<typename TClass>
    struct DeclareType
        : public TypeHeader
    {
        DeclareType()
        {
            this->name = snuifw::type::name<TClass>();
        }
    };
}
