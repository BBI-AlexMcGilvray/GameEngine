#include "Factory/Headers/Config.h"

namespace Data
{
    Config::Config(Core::IO::File& file)
    {
        buildFromFile(file);
    }

    void Config::buildFromFile(Core::IO::File& file)
    {
        std::string currentKey;
        std::string currentValue;
        char colon;

        while(!file.AtEndOfFile())
        {
            file.Read(currentKey);

            // if the currentKey is empty, skip this line (allow for some formatting)
            if (currentKey.size() == 0)
            {
                continue;
            }

            file.Read(colon);
            file.Read(currentValue);

            setValue(currentKey, currentValue);
        }
    }

    std::string Config::getValue(const std::string& key) const
    {
        if (_data.find(key) != _data.end())
        {
            return _data.at(key);
        }

        return std::string();
    }

    void Config::setValue(const std::string& key, const std::string& value)
    {
        _data.emplace(key, value);
    }
}