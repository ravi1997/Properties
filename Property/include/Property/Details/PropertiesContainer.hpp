#ifndef __PROPERTIESCONTAINER_H__
#define __PROPERTIESCONTAINER_H__

#include <Property/Details/Property.hpp>
#include <Property/Details/PropertyContainer.hpp>

namespace Property{
template <typename... Properties> class PropertiesContainer
{
private:
    std::tuple<std::pair<Properties,std::string_view>...> properties;
    //std::map<std::string, std::string> table;

public:
  PropertiesContainer (Properties... ps):properties{{ps,ps.getDefaultValue()}...}
  {}

  auto
  operator() (Details::PropertyContainer const& pc){
    for_each (properties, [&] (auto &item) {
      auto [property, value] = item;
      if (property.getName() == pc.getName())
        item.second = pc.getValue();
      else
        return;
    });
  }

  template<typename t>
  auto
  operator[] (const Property<t>& pc)const{
    std::string_view sv;
    for_each (properties, [&] (auto &item) {
      auto [property, value] = item;
      if (property.getName () == pc.getName ())
        sv = item.second;
      else
        return;
    });
    return Property<t>::PropertyType::deserialize(sv);
  }
};
}

#define PROPERTY(...)                                                                \
  Property::PropertiesContainer<FOR_EACH (dT, __VA_ARGS__) EMPTY> property{             \
    __VA_ARGS__, EMPTY{}                                             \
  };

#endif // __PROPERTIESCONTAINER_H__