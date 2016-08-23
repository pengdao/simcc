
#include "wcpp/inner_pre.h"
#include "inherited_conf_json.h"
#include "wcpp/file_util.h"

namespace wcpp {
namespace json {

static const std::string kInheritedFrom = "inherited_from";

// @brief 得到该路径的真实路径
// @param[in] - const std::string & inherited_from_file_path
// @return - std::string
static std::string GetRealPath(const std::string& parent_file_path, const std::string& inherited_from_file_path) {
    if (wcpp::FileUtil::IsAbsolutePathName(inherited_from_file_path)) {
        return inherited_from_file_path;
    }

    std::string dir, filename;
    wcpp::FileUtil::SplitFileName(parent_file_path, filename, dir);
    return wcpp::FileUtil::Join(dir, inherited_from_file_path);
}


json::JSONObjectPtr InheritedConfJSONObject::Parse(const std::string& json_file_path) {
    json::ObjectPtr jbase = json::JSONParser::LoadFile(json_file_path);
    if (!jbase || !jbase->IsTypeOf(json::kJSONObject)) {
        return json::JSONObjectPtr();
    }
    assert(jbase && jbase->IsTypeOf(json::kJSONObject));
    json::JSONObjectPtr jconf = static_cast<json::JSONObject*>(jbase.get());
    std::string inherited_from_file = jconf->GetString(kInheritedFrom);
    if (inherited_from_file.empty()) {
        return jconf;
    }
    inherited_from_file = json::GetRealPath(json_file_path, inherited_from_file);
    json::JSONObjectPtr jconf_inherited = Parse(inherited_from_file); // recursively
    jconf->Merge(jconf_inherited.get(), false);
    return jconf;
}
}
}