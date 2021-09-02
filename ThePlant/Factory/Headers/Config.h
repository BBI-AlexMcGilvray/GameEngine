#pragma once

#include <unordered_map>

#include "Core/IO/Headers/File.h"

// maybe this can be put into core (if it can be made nicer)
namespace Data
{
class Config
{
public:
    Config() = default;
    Config(const Config& other) = default;
    ~Config() = default;

    Config(Core::IO::File& file);

    void buildFromFile(Core::IO::File& file);

    std::string getValue(const std::string& key) const;
    void setValue(const std::string& key, const std::string& value);

private:
    std::unordered_map<std::string, const std::string> _data;
};
}