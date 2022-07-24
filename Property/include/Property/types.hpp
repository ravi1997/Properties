#ifndef __PROPERTY_TYPES_H__
#define __PROPERTY_TYPES_H__

#include <algorithm>
#include <concepts>
#include <cstring>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include <algorithm>
#include <array>
#include <cstddef>
#include <string_view>

#include <functional> // std::invoke
#include <tuple>      // std::tuple

namespace impl
{
template <typename T>
[[nodiscard]] constexpr std::string_view
RawTypeName ()
{
#ifndef _MSC_VER
  return __PRETTY_FUNCTION__;
#else
  return __FUNCSIG__;
#endif
}

struct TypeNameFormat
{
  std::size_t junk_leading = 0;
  std::size_t junk_total = 0;
};

constexpr TypeNameFormat type_name_format = [] {
  TypeNameFormat ret;
  std::string_view sample = RawTypeName<int> ();
  ret.junk_leading = sample.find ("int");
  ret.junk_total = sample.size () - 3;
  return ret;
}();
static_assert (type_name_format.junk_leading != std::size_t (-1),
               "Unable to determine the type name format on this compiler.");

template <typename T>
static constexpr auto type_name_storage = [] {
  std::array<char, RawTypeName<T> ().size () - type_name_format.junk_total + 1>
      ret{};
  std::copy_n (RawTypeName<T> ().data () + type_name_format.junk_leading,
               ret.size () - 1, ret.data ());
  return ret;
}();
}

template <typename T>
[[nodiscard]] constexpr std::string_view
TypeName ()
{
  return { impl::type_name_storage<T>.data (),
           impl::type_name_storage<T>.size () - 1 };
}

template <typename T>
[[nodiscard]] constexpr const char *
TypeNameCstr ()
{
  return impl::type_name_storage<T>.data ();
}

namespace Property::Details
{

template <typename x, typename t = std::remove_cvref_t<x>>
concept isNumber = requires
{
  std::is_same_v<t, int> || std::is_same_v<t, long> || std::is_same_v<t, long long> ||
  std::is_same_v<t, unsigned int> || std::is_same_v<t, unsigned long> || std::is_same_v<t, unsigned long long> ;
};

}



template <size_t Index = 0, // start iteration at 0 index
          typename TTuple,  // the tuple type
          size_t Size
          = std::tuple_size_v<std::remove_reference_t<TTuple> >, // tuple size
          typename TCallable, // the callable to bo invoked for each tuple item
          typename... TArgs   // other arguments to be passed to the callable
          >
void
for_each (TTuple &&tuple, TCallable &&callable, TArgs &&...args)
{
  if constexpr (Index < Size)
    {
      std::invoke (callable, args..., std::get<Index> (tuple));

      if constexpr (Index + 1 < Size)
        for_each<Index + 1> (std::forward<TTuple> (tuple),
                             std::forward<TCallable> (callable),
                             std::forward<TArgs> (args)...);
    }
}

#define EXPAND(...) EXPAND4 (EXPAND4 (EXPAND4 (EXPAND4 (__VA_ARGS__))))
#define EXPAND4(...) EXPAND3 (EXPAND3 (EXPAND3 (EXPAND3 (__VA_ARGS__))))
#define EXPAND3(...) EXPAND2 (EXPAND2 (EXPAND2 (EXPAND2 (__VA_ARGS__))))
#define EXPAND2(...) EXPAND1 (EXPAND1 (EXPAND1 (EXPAND1 (__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define PARENS ()

#define FOR_EACH_AGAIN() FOR_EACH_HELPER
#define FOR_EACH(macro, ...)  __VA_OPT__ (EXPAND (FOR_EACH_HELPER (macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...) macro (a1) __VA_OPT__ (FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))

#define dT(arg) decltype (arg),
struct EMPTY
{
  constexpr std::string
  getName ()
  {
    return "EMPTY";
  }

  constexpr std::string getDefaultValue(){
    return "EMPTY";
  }
};

#endif // __PROPERTY_TYPES_H__