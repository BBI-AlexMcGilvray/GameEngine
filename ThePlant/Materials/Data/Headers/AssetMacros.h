#pragma once

#include "Core/Reflection/Reflectable.h"
#include "Data/Headers/AssetName.h"
#include "Data/Headers/AssetType.h"

#define ASSET(type_name, ...)\
struct type_name\
{\
    REFLECTABLE(__VA_ARGS__)\
    type_name() = default;\
    type_name(const type_name& other) = delete;\
    type_name& operator=(const type_name& other) = delete;\
}

// should remove the need for a path in the future and infer everything from the extension (or something)
#define ASSET_TYPE(type_name, path, extension)\
template<>\
struct AssetType<type_name>\
{\
  static Hash ClassHash()\
  {\
    return HashValue(#type_name);\
  }\
  static String GetPath()\
  {\
    return path;\
  }\
  static String GetFileType()\
  {\
    return extension;\
  }\
}