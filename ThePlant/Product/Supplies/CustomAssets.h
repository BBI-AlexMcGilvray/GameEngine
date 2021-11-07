#pragma once

#include <string>

#include "Data/Headers/AssetType.h"

/*
This file is auto-generated.

DO NOT MODIFY
*/

namespace Data {
// Test
struct Test
{
  std::string Name;
};

template<>
struct AssetType<Test>
{
  Hash ClassHash() const
  {
    return Core::HashValue("Test");
  }

  std::string GetPath() const
  {
    return "CustomAssets/Test/";
  }

  std::string GetFileType() const
  {
    return ".Tst";
  }
};

// ListTest
struct ListTest
{
  std::string Name;
  AssetName<int> TestList;
};

template<>
struct AssetType<ListTest>
{
  Hash ClassHash() const
  {
    return Core::HashValue("ListTest");
  }

  std::string GetPath() const
  {
    return "CustomAssets/ListTest/";
  }

  std::string GetFileType() const
  {
    return ".Lst";
  }
};

// Test2
struct Test2
{
  std::string Name;
  AssetName<int> TestReference;
};

template<>
struct AssetType<Test2>
{
  Hash ClassHash() const
  {
    return Core::HashValue("Test2");
  }

  std::string GetPath() const
  {
    return "CustomAssets/Test2/";
  }

  std::string GetFileType() const
  {
    return ".Tst";
  }
};

}// namespace Data
