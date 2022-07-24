#ifndef __PROPERTYHELPER_H__
#define __PROPERTYHELPER_H__

#include <Property/types.hpp>

namespace Property::Details
{
template <typename t> struct UserDefinedTypePropertyHelper
{
  using PropertyType = t;
  using ConverterType = std::string_view;

  static ConverterType
  serialize (PropertyType value)
  {
    return PropertyType::serialize (value);
  }

  static PropertyType
  deserialize (ConverterType value)
  {
    return PropertyType::deserialize (value);
  }

  static std::string_view
  getTypeName ()
  {
    return TypeName<PropertyType> ();
  }
};

struct StringPropertyHelper
{
  using PropertyType = std::string;
  using ConverterType = std::string_view;

  static ConverterType
  serialize (PropertyType const& value)
  {
    return value;
  }

  static PropertyType
  deserialize (ConverterType value)
  {
    return PropertyType{value};
  }

  static std::string_view
  getTypeName ()
  {
    return TypeName<PropertyType> ();
  }
};

template<typename t>
requires (isNumber<t>)
struct NumberPropertyHelper 
{
  using PropertyType = t;
  using ConverterType = std::string_view;

  static ConverterType
  serialize (PropertyType value)
  {  
    return std::to_string(value);
  }

  static PropertyType
  deserialize (ConverterType value)
  {
      std::string s{value};
      if constexpr (std::is_same_v<PropertyType,int>)
        return std::stoi(s);
      else if constexpr (std::is_same_v<PropertyType, long>)
        return std::stol (s);
      else if constexpr (std::is_same_v<PropertyType, long long>)
        return std::stoll (s);
      else if constexpr (std::is_same_v<PropertyType, unsigned int>)
        return std::stol (s);
      else if constexpr (std::is_same_v<PropertyType, unsigned long>)
        return std::stol (s);
      else if constexpr (std::is_same_v<PropertyType, unsigned long long>)
        return std::stol (s);
  }

  static std::string_view
  getTypeName ()
  {
    return TypeName<PropertyType> ();
  }
};

template <typename t>
struct HelperType : public UserDefinedTypePropertyHelper<t>
{
};

template <> struct HelperType<std::string> : public StringPropertyHelper
{
};

template <typename t> requires (isNumber<t>) struct HelperType<t> : public NumberPropertyHelper<t>
{
};
}

#endif // __PROPERTYHELPER_H__