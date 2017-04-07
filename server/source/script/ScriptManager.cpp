#include "script/ScriptManager.h"
#include <iostream>
#include <dirent.h>
#include <string>
#include "utils/StringUtils.h"

ScriptManager::ScriptManager() {
}

ScriptManager::~ScriptManager() {
}

void ScriptManager::load()
{
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir("scripts/")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == S_IFDIR)
                continue;

            std::string filename(ent->d_name);

            if (!StringUtils::has_suffix(filename, std::string(".lua")))
                continue;

            filename = filename.substr(0, filename.size() - 4); //remove ".lua" name extension

            Script *script = new Script(filename);

            m_scripts.insert(std::pair<std::string, Script*>(filename, script));
        }
        closedir(dir);
    }
    else {
        std::cerr << "could not open script directory" << std::endl;
    }

    for(auto const &entry : m_scripts) {
        Script *script = entry.second;
        script->onEnable();
    }
}

void ScriptManager::unload() {
    for(auto const &entry : m_scripts) {
        Script *script = entry.second;
        script->onDisable();
        delete script;
    }
    m_scripts.clear();
}

void ScriptManager::callEvent(Event *e) {
    for(auto const &entry : m_scripts) {
        Script *script = entry.second;

        if (dynamic_cast<EventMessage*>(e)) {
            EventMessage *eventMessage = (EventMessage*) e;
            script->onMessage(eventMessage);
        }
    }
}
