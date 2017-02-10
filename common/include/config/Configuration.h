#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include "json.hpp"

class Configuration {
    protected:
        std::string m_filename;
        nlohmann::json json;

        virtual void generateDefault() = 0;
    public:
        Configuration(std::string &filename);
        virtual ~Configuration();

        bool load();
        void save();
};

#endif
