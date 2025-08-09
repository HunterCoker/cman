#include "project.hpp"

#include <filesystem>
#include <spdlog/spdlog.h>

#include "utility/assert.h"

namespace cman
{

static bool isAncestor(const std::filesystem::path& parent, const std::filesystem::path& child)
{
    if (parent.empty() || child.empty() || parent == child)
        return false;

    auto root = child.root_directory();
    auto curr = std::filesystem::weakly_canonical(child).parent_path();
    auto target = std::filesystem::weakly_canonical(parent);

    while (curr != root)
    {
        if (curr == target)
            return true;
        curr = curr.parent_path();
    }

    return false;
}

Project::Project()
    : name_("unnamed")
    , synced_(false)
{
    currDir_ = std::move(std::filesystem::current_path());
    rootDir_ = getRoot(currDir_);
}

void Project::sync()
{
    if (rootDir_.empty())
    {
        spdlog::error("not a cman project (or any of the parent directories)");
        std::exit(EXIT_FAILURE);
    }
    synced_ = true;
}

bool Project::init(const std::string& name, const std::filesystem::path& dir)
{
    name_ = name;
    rootDir_ = dir.is_absolute()
             ? dir.lexically_normal()
             : (currDir_ / dir / name_).lexically_normal();

    if (std::filesystem::exists(rootDir_ / ".cman"))
    {
        spdlog::error("reinitialized existing cman project");
        return false;
    }

    if (!std::filesystem::exists(rootDir_.parent_path()))
    {
        spdlog::error("directory \'{}\' does not exist", rootDir_.string());
        return false;
    }

    auto parProjectRoot = getRoot(rootDir_);
    if (!parProjectRoot.empty())
    {
        spdlog::warn("directory \'{}\' is inside cman project:\n"
                     "  creating nested project in \'{}\'",
                     rootDir_.string(), parProjectRoot.string());
    }

    /* render init file tree */

    spdlog::info("CMake project \'{}\' created in directory \'{}\'", name_, rootDir_.string());

    return true;
}

std::filesystem::path Project::getRoot(const std::filesystem::path& dir)
{
    ASSERT(dir.is_absolute() && dir == dir.lexically_normal(),
        "dir must be absolute and lexically normal");

    auto start = dir;
    auto root = start.root_path();

    while (start != root)
    {
        if (std::filesystem::exists(start / ".cman"))
            return start;
        start = start.parent_path();
    }
    return "";
}

}  // namespace cman