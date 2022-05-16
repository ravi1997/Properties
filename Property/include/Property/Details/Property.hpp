#ifndef __PROPERTY_DETAILS_H__
#define __PROPERTY_DETAILS_H__

#include <Property/Details/PropertyHelperType.hpp>
#include <Property/Details/PropertyContainer.hpp>

namespace Property
{
template <typename t> class Property
{

public:
  using PropertyType = details::UserDefinedHelperType<t>;

private:
  std::string name;
  typename PropertyType::PropertyType defaultValue;

public:
  Property (std::string s, typename PropertyType::PropertyType dv)
      : name{ s }, defaultValue{ dv }
  {
  }

  details::PropertyContainer
  operator= (typename PropertyType::PropertyType property) const
  {
    auto value = PropertyType::serialize (property);
    return {
      name,
      value
    };
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

template<>
class Property<std::string>
{
public:
  using PropertyType = details::StringPropertyHelperType;

private:
  std::string name;
  typename PropertyType::PropertyType defaultValue;

public:
  Property (std::string s, typename PropertyType::PropertyType dv)
      : name{ s }, defaultValue{ dv }
  {
  }

  details::PropertyContainer
  operator= (typename PropertyType::PropertyType value)const
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

template <> class Property<bool>
{
public:
  using PropertyType = details::BooleanPropertyHelperType;

private:
  std::string name;
  typename PropertyType::PropertyType defaultValue;

public:
  Property (std::string s, typename PropertyType::PropertyType dv)
      : name{ s }, defaultValue{ dv }
  {}

  details::PropertyContainer
  operator= (typename PropertyType::PropertyType value)const
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

template<typename t>class Property<std::vector<t>>{
  public:
  using PropertyType = details::VectorPropertyHelperType<t>;

private:
  std::string name;
  typename PropertyType::PropertyType defaultValue;

public:
  Property (std::string s, typename PropertyType::PropertyType dv)
      : name{ s }, defaultValue{ dv }
  {
  }

  details::PropertyContainer
  operator= (typename PropertyType::PropertyType property)const
  {
    auto value = PropertyType::serialize (property);
    return { name, value };
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

template <details::number t> class Property<t>
{
public:
  using PropertyType = details::NumberPropertyHelperType<t>;

private:
  std::string name;
  typename PropertyType::PropertyType defaultValue;

public:
  Property (std::string s, typename PropertyType::PropertyType dv)
      : name{ s }, defaultValue{ dv }
  {
  }

  details::PropertyContainer
  operator= (typename PropertyType::PropertyType value) const
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

#endif // __PROPERTY_DETAILS_H__