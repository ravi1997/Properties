#ifndef __PROPERTYCONTAINER_H__
#define __PROPERTYCONTAINER_H__

#include <Property/Details/PropertyHelperType.hpp>

namespace Property
{
namespace details
{
class PropertyContainer
{
public:
  using ConversionType = std::string;

private:
  std::string propertyName;
  ConversionType value;

public:
  PropertyContainer (std::string s, ConversionType ct)
      : propertyName{ s }, value{ ct }
  {
  }

  auto
  getName ()
  {
    return propertyName;
  }

  auto
  getName () const
  {
    return propertyName;
  }

  auto
  getValue ()
  {
    return value;
  }

  auto
  getValue () const
  {
    return value;
  }
};
}
}

#endif // __PROPERTYCONTAINER_H__