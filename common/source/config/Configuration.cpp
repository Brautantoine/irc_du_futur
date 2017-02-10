#include "config/Configuration.h"
#include <fstream>
#include <iostream>

Configuration::Configuration(std::string &filename) : m_filename(filename) {
    load();
}

Configuration::~Configuration() {
}

bool Configuration::load() {
    std::fstream file(m_filename);

    try {
        file >> json;

    } catch (const std::exception &e) {
        json.clear();
        std::cout << "Error in Configuration " << m_filename << ": " << e.what() << std::endl;
        return false;
    }

    return true;
}

void Configuration::save() {
    std::ofstream file(m_filename);
    file << json.dump(4) << std::endl;
}
