#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "Script.h"
#include <string>
#include <map>

class ScriptManager
{
    public:
        ScriptManager();
        ~ScriptManager();

        void load();
        void unload();

        void callEvent(Event *e);

    private:
        std::map<std::string, Script*> m_scripts;
};

#endif
