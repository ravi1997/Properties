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

namespace Property
{
extern const std::string version;
namespace details
{
template <typename ConverterType>
ConverterType
convert_to (auto value)
{
  if constexpr (std::is_same_v<decltype (value), ConverterType>)
    return value;
  else if constexpr (std::is_same_v<ConverterType, std::string>)
    return std::to_string (value);
  else
    return {};
}

template <typename t>
concept number = std::is_integral_v<t> || std::is_floating_point_v<t>;

template <number t>
auto
toNumber (std::string s)
{
  if constexpr (std::is_same_v<int, typename std::remove_cv<t>::type>)
    return std::stoi (s);
  else if (std::is_same_v<float, typename std::remove_cv<t> >)
    return std::stof (s);
  else
    return std::stol (s);
}
}

}

#endif // __PROPERTY_TYPES_H__