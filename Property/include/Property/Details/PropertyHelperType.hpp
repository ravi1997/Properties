#ifndef __PROPERTYHELPERTYPE_H__
#define __PROPERTYHELPERTYPE_H__

#include <Property/types.hpp>

namespace Property {
    namespace details {

        template<typename c>
        struct StringPropertyHelperType{

            using ConverterType = c;
            using PropertyType = std::string;
            
            static std::string getPropertyName(){
                return "std::string";
            }

            static PropertyType deserialize(ConverterType s){
                if constexpr (std::is_same_v<ConverterType,std::string>)
                    return s;
                else
                    return details::convert_to<PropertyType>(s);
            }

            static ConverterType serialize(PropertyType v){
                if constexpr (std::is_same_v<ConverterType,std::string>)
                    return v;
                else
                    return details::convert_to<ConverterType>(v);
            }
        };

        template<typename c>
        struct BooleanPropertyHelperType{
          using ConverterType = c;
          using PropertyType = bool;

          static std::string
          getPropertyName ()
          {
            return "bool";
          }

          static PropertyType
          deserialize (ConverterType s)
          {
            if constexpr (std::is_same_v<ConverterType, std::string>)
              return s == "TRUE";
            else
              return details::convert_to<PropertyType> (s);
          }

          static ConverterType
          serialize (PropertyType v)
          {
            if constexpr (std::is_same_v<ConverterType, std::string>)
              return (v)?"TRUE":"FALSE";
            else
              return details::convert_to<ConverterType> (v);
          }
        };

        template<number t,typename c>
        struct NumberPropertyHelperType{
          using ConverterType = c;
          using PropertyType = t;

          static std::string
          getPropertyName ()
          {
            if constexpr (std::is_same_v<int, typename std::remove_cv<t>::type>)
              return "int";
            else if (std::is_same_v<float,typename std::remove_cv<t>>)
              return "float";
            else if (std::is_same_v<unsigned int,typename std::remove_cv<t>>)
              return "unsigned int";
            
            else
              return "double";
          }

          static PropertyType
          deserialize (ConverterType s)
          {
            if constexpr (std::is_same_v<ConverterType, std::string>)
              return toNumber<PropertyType>(s);
            else
              return details::convert_to<PropertyType> (s);
          }

          static ConverterType
          serialize (PropertyType v)
          {
            if constexpr (std::is_same_v<ConverterType, std::string>)
              return std::to_string(v);
            else
              return details::convert_to<ConverterType> (v);
          }
        };

        template <typename t, typename c> class UserDefinedHelperType
        {
        public:
          using ConverterType = c;
          using PropertyType = t;

          static PropertyType
          deserialize (ConverterType s)
          {
              return details::convert_to<PropertyType> (s);
          }

          static ConverterType
          serialize (PropertyType v)
          {
              return details::convert_to<ConverterType> (v);
          }
        };
    }
}

#endif // __PROPERTYHELPERTYPE_H__