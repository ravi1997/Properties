#ifndef __PROPERTIESCONTAINER_H__
#define __PROPERTIESCONTAINER_H__

#include <Property/Details/Property.hpp>
#include <Property/Details/PropertyContainer.hpp>
#include <type_traits>

namespace Property
{

template <class, template <class...> class>
inline constexpr bool is_specialization = false;
template <template <class...> class T, class... Args>
inline constexpr bool is_specialization<T<Args...>, T> = true;

template <class T> concept isProperty = is_specialization<T, Property>;

class PropertiesContainer
{
private:
  std::map<std::string, std::string> table;
public:
  void setProperty (isProperty auto property)
  {
    auto key = property.getName ();
    std::cout<<"Properties-Property Name : "<<key<<std::endl;
    auto value = decltype (property)::PropertyType::serialize (
        property.getDefaultValue ());

    table[key] = value;
  }

  using ConverterType = std::string;

  template <isProperty... t> PropertiesContainer (t... properties)
  {
    (setProperty (properties), ...);
  }

  template <isProperty t>
  typename t::PropertyType::PropertyType
  operator[] (t property)
  {
    return t::PropertyType::deserialize (table[property.getName ()]);
  }

  template <typename t>
  typename t::PropertyType::PropertyType
  operator[] (t property) const
  {
    std::cout<<"Property Name : "<<property.getName()<<std::endl;
    return t::PropertyType::deserialize (table.at(property.getName ()));
  }

  auto &
  operator[] (std::string s)
  {
    return table[s];
  }

  auto
  operator[] (std::string s) const
  {
    return table.at(s);
  }

  void
  operator() (details::PropertyContainer pc)
  {
    if(auto iter = table.find(pc.getName());iter==table.end())
      throw "Not A Property of this Module";
    table[pc.getName ()] = pc.getValue ();
  }
};

}

#endif // __PROPERTIESCONTAINER_H__