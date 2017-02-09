#include "utils/NetworkUtils.h"

namespace NetworkUtils
{
    unsigned int getBytesLength(std::string &str) {
        return (2 + str.size()+1); //See protocol spec (1short + string null terminated)
    }
}

