//
// Created by volodya on 03.06.2021.
//

#include "locale_loader.h"

LocaleLoader::LocaleLoader(const std::filesystem::path &root) {
    boost::property_tree::read_json(root, _tree);
}

LocaleLoader::LocaleLoader() : LocaleLoader(([]() -> std::filesystem::path {
    return std::filesystem::path(__FILE__).parent_path() / "../../../data/locale.json";
})()) {
}

std::string LocaleLoader::get(const std::string &name) {
    return _tree.get<std::string>(name);
}
