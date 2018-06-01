# json
C++ wrapper for RapidJSON
## motivation
- provide API that is similar to standard library
- hide RapidJSON behind opaque std::aligned_storage so client doesn't need to include
  RapidJSON's huge header files in every relevant translation unit.
## requirement
- C++17 compiler
- cmake
- Boost.Test
## usage
1. import into client project
2. build
3. add 'include' directory to client's include path
4. add 'lib' directory to cilent's linker search path
## outermost namespace
json
## headers
### <json/json.hpp>
declare free functions
- value parse(std::string_view);
- std::string stringify(value const&);
- value* find(value&, std::string_view json_pointer);
### <json/value.hpp>
declare class 'value' which represent JSON value
### <json/object.hpp>
declare class 'object' which represent JSON object
### <json/array.hpp>
declare class 'array' which represent JSON array
