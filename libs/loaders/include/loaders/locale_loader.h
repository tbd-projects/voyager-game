//
// Created by volodya on 03.06.2021.
//

#ifndef VOYAGER_LOCALE_LOADER_H
#define VOYAGER_LOCALE_LOADER_H

#include <string>
#include <boost/property_tree/json_parser.hpp>
#include <filesystem>

class LocaleLoader {
private:
    using ptree = boost::property_tree::ptree;
    ptree _tree;
public:
    LocaleLoader();
    explicit LocaleLoader(const std::filesystem::path& root);
    std::string get(const std::string& name);
};

#endif //VOYAGER_LOCALE_LOADER_H
