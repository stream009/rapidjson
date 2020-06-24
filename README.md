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
stream9::json

## headers
### stream9/json.hpp
### stream9/json/json.hpp
convenient all encompasing header

### stream9/json/value.hpp
declare class 'value' which represent JSON value and its related free functions

### stream9/json/object.hpp
declare class 'object' which represent JSON object and its related free functions

### stream9/json/array.hpp
declare class 'array' which represent JSON array and its related free functions
