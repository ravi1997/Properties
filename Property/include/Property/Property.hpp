#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include "Property/PropertyHelperType.hpp"
#include <Property/PropertyContainer.hpp>

namespace Property
{
template <typename t, typename c = std::string> class Property
{
};

template <typename c> class Property<std::string, c>
{
public:
  using PropertyType = details::StringPropertyHelperType<c>;

private:
  std::string name;
  typename PropertyType::PropertyType defaultValue;

public:
  Property (std::string s, typename PropertyType::PropertyType dv)
      : name{ s }, defaultValue{ dv }
  {
  }

  details::PropertyContainer<c>
  operator= (typename PropertyType::PropertyType value)
  {
    return { name, PropertyType::serialize (value) };
  }
  auto
  getDefaultValue () const
  {
    return defaultValue;
  }
  auto
  getName () const
  {
    return name;
  }
};

template <typename c> class Property<bool, c>
{
public:
  using PropertyType = details::BooleanPropertyHelperType<c>;

private:
  std::string name;
  typename PropertyType::PropertyType defaultValue;

public:
  Property (std::string s, typename PropertyType::PropertyType dv)
      : name{ s }, defaultValue{ dv }
  {
  }

  details::PropertyContainer<c>
  operator= (typename PropertyType::PropertyType value)
  {
    return { name, PropertyType::serialize (value) };
  }
  auto
  getDefaultValue () const
  {
    return defaultValue;
  }
  auto
  getName () const
  {
    return name;
  }
};

template <details::number t, typename c> class Property<t, c>
{
public:
  using PropertyType = details::NumberPropertyHelperType<t, c>;

private:
  std::string name;
  typename PropertyType::PropertyType defaultValue;

public:
  Property (std::string s, typename PropertyType::PropertyType dv)
      : name{ s }, defaultValue{ dv }
  {
  }

  details::PropertyContainer<c>
  operator= (typename PropertyType::PropertyType value)
  {
    return { name, PropertyType::serialize (value) };
  }
  auto
  getDefaultValue () const
  {
    return defaultValue;
  }

  auto
  getName () const
  {
    return name;
  }
};
}

#endif // __PROPERTY_H__