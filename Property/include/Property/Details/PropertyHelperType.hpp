#ifndef __PROPERTYHELPERTYPE_H__
#define __PROPERTYHELPERTYPE_H__

#include <Property/types.hpp>

namespace Property {
    namespace details {

        struct StringPropertyHelperType{

            using ConverterType = std::string;
            using PropertyType = std::string;
            
            static std::string getPropertyName(){
                return "std::string";
            }

            static PropertyType deserialize(ConverterType s){
              return s;
            }

            static ConverterType serialize(PropertyType v){
                return v;
            }
        };

        struct BooleanPropertyHelperType{
          using ConverterType = std::string;
          using PropertyType = bool;

          static std::string
          getPropertyName ()
          {
            return "bool";
          }

          static PropertyType
          deserialize (ConverterType s)
          {
            return s == "TRUE";
          }

          static ConverterType
          serialize (PropertyType v)
          {
            return (v)?"TRUE":"FALSE";
          }
        };

        template<number t>
        struct NumberPropertyHelperType{
          using ConverterType = std::string;
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
            return toNumber<PropertyType>(s);
          }

          static ConverterType
          serialize (PropertyType v)
          {
            return std::to_string(v);
          }
        };

        template <typename t> class UserDefinedHelperType
        {
        public:
          using ConverterType = std::string;
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

        template <typename t> class VectorPropertyHelperType
        {
        public:
          using ConverterType = std::string;
          using PropertyType = std::vector<t>;

          static PropertyType
          deserialize (ConverterType s)
          {
            using namespace std;
            auto split = [] (string s, string delimiter) {
              size_t pos_start = 0, pos_end, delim_len = delimiter.length ();
              string token;
              vector<string> res;

              while ((pos_end = s.find (delimiter, pos_start)) != string::npos)
                {
                  token = s.substr (pos_start, pos_end - pos_start);
                  pos_start = pos_end + delim_len;
                  res.push_back (token);
                }

              res.push_back (s.substr (pos_start));
              return res;
            };
            PropertyType result;
            s = s.substr(1,s.length()-2);
            for(auto e:split(s,","))
              result.push_back(details::convert_to<t>(e));
            std::cout<<"Result size : "<<result.size()<<endl;
            return  result;
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