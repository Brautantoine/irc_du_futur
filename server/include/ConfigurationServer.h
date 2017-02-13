#ifndef CONFIGURATIONSERVER_H
#define CONFIGURATIONSERVER_H

#include "config/Configuration.h"

class ConfigurationServer : public Configuration {
    public:
        ConfigurationServer(std::string &filename);

        virtual void generateDefault();

        void setServerName(std::string servername);
        std::string getServername();

        void setMotd(std::string motd);
        std::string getMotd();

        void setMaxConnections(int maxconnections);
        int getMaxConnections();
};

#endif
