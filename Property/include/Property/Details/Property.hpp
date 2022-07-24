#ifndef __PROPERTY_DETAILS_H__
#define __PROPERTY_DETAILS_H__

#include <Property/Details/PropertyContainer.hpp>
#include <Property/Details/PropertyHelper.hpp>
#include <Property/types.hpp>

namespace Property
{

template <typename t, typename h = Details::HelperType<t> > class Property
{
public:
  using PropertyType = h;
  using ConverterType = typename PropertyType::ConverterType;

private:
  const std::string_view name;
  ConverterType defaultValue;

public:
  constexpr
  Property (const std::string_view n, ConverterType v)
      : name{ n }, defaultValue{ v }
  {
  }

  constexpr auto
  getName () const
  {
    return name;
  }

  constexpr auto
  getDefaultValue () const
  {
    return defaultValue;
  }

  constexpr Details::PropertyContainer
  operator= (typename PropertyType::PropertyType value) const
  {
    return { PropertyType::getTypeName (), getName (),
             PropertyType::serialize (value) };
  }

  constexpr auto
  operator<=> (const Property p) const
  {
    return getName () <=> p.getName ();
  }
};

}

#endif // __PROPERTY_DETAILS_H__