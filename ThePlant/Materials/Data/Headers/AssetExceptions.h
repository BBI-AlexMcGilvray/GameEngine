#pragma once

#include "Core/Headers/Exception.h"

using namespace Core;

namespace Data {
struct AssetException : Exception
{
  using Exception::Exception;

  AssetException(const std::string& message)
  : Exception(message)
  {}
};

struct InvalidAssetOperation : AssetException
{
  using AssetException::AssetException;

  InvalidAssetOperation(const std::string& message)
  : AssetException(message)
  {}
};

struct InvalidAsset : AssetException
{
  using AssetException::AssetException;

  InvalidAsset(const std::string& message)
  : AssetException(message)
  {}
};

struct FailureToLoad : AssetException
{
  using AssetException::AssetException;

  FailureToLoad(const std::string& message)
  : AssetException(message)
  {}
};
}// namespace Data