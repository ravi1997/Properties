#include <Property/Property.hpp>
#include <iostream>
#include <string>

Property::Property<bool> visible{ "visible", false };
Property::Property<int> level{ "level", 0 };
class Button
{
private:
  Property::PropertiesContainer properties{ visible, level };

  void
  setProperty (Property::details::PropertyContainer pc)
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

  auto getVisible()const{
    return properties[visible];
  }


};

int
main ()
{
try{
  Button b{ visible = false };

  b.draw ();

}catch(const char* s)
{
  std::cout<<s<<std::endl;
}
  return 0;
}