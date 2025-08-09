#include <CLI/CLI.hpp>

#include "project.hpp"

int main(int argc, const char* argv[])
{    
    cman::Project proj;

    CLI::App app("app description", "cman");
    app.require_subcommand(/* min */ 0, /* max */ 1);

    int exitCode = EXIT_SUCCESS;

    /* init subcommand */

    auto init = app.add_subcommand("init", "creates a new cmake project");
    
    {
        std::string name = "unnamed";
        std::string dir = "";
        bool isLib = false;
        
        init->add_option("name", name, "name of project");
        init->add_option("dir", dir, "directory where new project is created");
        init->add_flag("--lib", isLib, "initializes a new library project");
        init->callback([&]()
            {
                bool res = proj.init(name, dir);
                if (!res)
                    exitCode = EXIT_FAILURE;
            });
    }
    /* exe subcommand */

    auto exe = app.add_subcommand("exe", "manage project executables");

    /* package subcommand */

    auto package = app.add_subcommand("package", "manage project dependencies (packages)");

    CLI11_PARSE(app, argc, argv);

    return exitCode;
}