#include <Property/PropertiesContainer.hpp>
#include <Property/Property.hpp>
#include <iostream>
#include <string>

Property::Property<bool> visible{ "visible", false };
Property::Property<int> level{ "level", 0 };

class Button
{
private:
  Property::PropertiesContainer<std::string> properties{ visible, level };

  void
  setProperty (Property::details::PropertyContainer<std::string> pc)
  {
    properties (pc);
  }

public:
  template <typename... t> Button (t... properties)
  {
    (setProperty (properties), ...);
  }

  void
  draw ()
  {
    bool myvisible = properties[visible];

    if (myvisible)
      std::cout << "Visible : True" << std::endl;
    else
      std::cout << "Visible : False" << std::endl;
  }
};

int
main ()
{

  Button b{ visible = false };

  b.draw ();
  return 0;
}