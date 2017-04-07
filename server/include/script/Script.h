#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>
#include "events/EventMessage.h"

extern "C" {
    # include <lua.h>
    # include <lauxlib.h>
    # include <lualib.h>
}

class Script
{
    public:
        Script(std::string filename);
        virtual ~Script();

        void onEnable();
        void onDisable();
        bool onMessage(EventMessage *event);
    private:
        std::string m_filename;
};

#endif // SCRIPT_H
