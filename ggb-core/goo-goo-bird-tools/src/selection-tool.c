#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include "cliargs.h"
#include "lang.h"
#include "selectiontool.h"
#include "goo-goo-bird-tools.h"

//VVVVVV   Selection Tool
const TOOL TOOL_LIST[] =
{
    [0] = {"goo-goo-bird-tools", goo_goo_bird_tools}
    /*Add your tool! ex: [1] = {"your_tool_name", your_tool_main}
    添加你的工具！ 示範： [1] = {"your_tool_name", your_tool_main}*/
};

inline int which_tool_core(const char* tool_name, int (*tool_main)(int argc, char* argv[], char* envp[]), const CLIarg arg, const char* mod)
{
    /*
    *   Mod:
    *   search    Iterate until the target is found.
    *   direct    Check only whether the first one is the target.
    */
    char **argv = NULL;
    if(!strcmp(mod, "search") && arg.argc )
    {
        for(int i = 1; i < arg.argc; i++)
        {
            if(!strcmp(arg.argv[i], tool_name))
            {
                argv = &(arg.argv[i]);
                break;
            }
        }
    }
    else
    {
        argv = &(arg.argv[0]);
    }
    if(!strcmp(argv[0], tool_name))
    {
        return (*tool_main)(arg.argc, argv, arg.envp);
    }
    else
    {
    return NOT_FOUND;
    }
}

int main(int argc, char *argv[], char *envp[])
{
    CLIarg arg = {argc, argv, envp};
    int return_v = NOT_FOUND;
    for(int tool = 0; tool < HOW_MUCH_TOOLS; tool++)
    {
        return_v = which_tool_core(TOOL_LIST[tool].tool_name, TOOL_LIST[tool].tool, arg, "direct");
        if(return_v != NOT_FOUND) {break;}
    }

    if(return_v == NOT_FOUND)
    {
        int lang = (getenv("LC_ALL") && strcasestr(getenv("LC_ALL"), "zh") != NULL) ? ZH_CN:EN_US;
        bird_var var = {false, NULL};
        options_bird options[] =
        {
            [VERSION] = {'v', "--version", false}, //version
            [HELP] = {'h', "--help", false} //help
        };
        options[HELP].switch_opt = true;
        goo_goo_bird_basic(lang, options, var);
    }

    return return_v;
}
