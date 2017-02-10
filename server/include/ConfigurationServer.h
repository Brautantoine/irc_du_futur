#ifndef CONFIGURATIONSERVER_H
#define CONFIGURATIONSERVER_H

#include "config/Configuration.h"

class ConfigurationServer : public Configuration {
    private:
        std::string m_servername;
        std::string m_motd;
    public:
        ConfigurationServer(std::string &filename);

        virtual void generateDefault();

        void setServerName(std::string servername);
        std::string getServername();

        void setMotd(std::string motd);
        std::string getMotd();
};

#endif
