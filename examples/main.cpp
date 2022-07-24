#include <Property/Property.hpp>           
#include <iostream>
#include <string>
constexpr Property::Property<bool> visible{ "visible", "false" };
constexpr Property::Property<int> level{ "level", "0" };



class Button
{
private:
  PROPERTY(visible, level)

  void
  setProperty (Property::Details::PropertyContainer pc)
  {
    property (pc);
  }

public:
  template <typename... t> 
  constexpr Button (t... properties)
  {
    (setProperty (properties), ...);
  }

  void
  draw ()
  {
    bool myvisible = property[visible];

    if (myvisible)
      std::cout << "Visible : True" << std::endl;
    else
      std::cout << "Visible : False" << std::endl;
  }

  auto getVisible()const{
    return property[visible];
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