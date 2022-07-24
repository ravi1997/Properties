#ifndef __PROPERTYCONTAINER_H__
#define __PROPERTYCONTAINER_H__

#include <Property/types.hpp>

namespace Property::Details
{
class PropertyContainer
{
public:
  using ConverterType = std::string_view;

private:
  std::string_view propertyType;
  std::string_view name;
  ConverterType value;

public:
  constexpr
  PropertyContainer (std::string_view p, std::string_view n, ConverterType v)
      : propertyType{ p }, name{ n }, value{ v }
  {
  }

  constexpr auto
  getName () const
  {
    return name;
  }
  constexpr auto
  getValue () const
  {
    return value;
  }

  constexpr auto
  getPropertyType () const
  {
    return propertyType;
  }

  constexpr bool
  operator== (PropertyContainer const& p) const
  {
    return getPropertyType () == p.getPropertyType ()
           && getName () == p.getName () && value == p.getValue ();
  }

  constexpr void setValue(std::string_view v){
    value = v;
  }
};
}

#endif // __PROPERTYCONTAINER_H__