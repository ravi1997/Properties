#ifndef __PROPERTIESCONTAINER_H__
#define __PROPERTIESCONTAINER_H__

#include "Property/Details/PropertyContainer.hpp"
#include <Property/Details/Property.hpp>

namespace Property
{

template <typename c = std::string> class PropertiesContainer
{
private:
  std::map<std::string, std::string> table;

public:
  using ConverterType = c;

  template <typename... t> PropertiesContainer (t... properties)
  {

    auto setProperty = [&] (auto property) {
      auto key = property.getName ();
      auto value = decltype(property)::PropertyType::serialize (property.getDefaultValue ());

      table[key] = value;
    };

    (setProperty (properties), ...);
  }

  template <typename t>
  typename t::PropertyType::PropertyType
  operator[] (t property)
  {
    return t::PropertyType::deserialize (table[property.getName ()]);
  }

  auto &
  operator[] (std::string s)
  {
    return table[s];
  }


  void
  operator() (details::PropertyContainer<ConverterType> pc)
  {
    table[pc.getName ()] = pc.getValue ();
  }
};

}

#endif // __PROPERTIESCONTAINER_H__