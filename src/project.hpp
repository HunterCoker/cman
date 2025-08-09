#pragma once

#include "utility/assert.h"
#include <filesystem>

namespace cman
{

class Project
{
public:
    Project();
    Project(const Project&) = delete;
    ~Project() = default;

    void sync();

    bool init(const std::string& name, const std::filesystem::path& dir);

private:
    static std::filesystem::path getRoot(const std::filesystem::path& dir);

private:
    std::string name_;
    std::filesystem::path rootDir_, currDir_;
    bool synced_;
};

}  // namespace cman