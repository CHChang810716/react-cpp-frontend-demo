#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include "fetch.hpp"
#include "utils.hpp"

namespace reactdom {

constexpr auto import_css = [](const std::string& path) {
    Fetch fetcher;
    // auto pms = fetcher.get<std::string>(path + ".json");
    // document write css
    document.write(
        "<link rel=\"stylesheet\" type=\"text/css\" href=\"" + path + "\">"
    );
    // download json and return
    // return nlohmann::json::parse(pms.await());
    return nlohmann::json();
};

} // namespace reactdom
