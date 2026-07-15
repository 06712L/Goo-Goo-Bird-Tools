//Enable _GNU_SOURCE
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

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

#ifdef COMBINATION
/*vvvvv    在此引入可以與你的工具溝通的標頭檔！ 示範： #include "your-tool-name.h"
* vvvvv    Include the header file here that allows communication with your tool! ex: #include "your-tool-name.h"
*/

#include "goo-goo-calculator.h"
#endif

//VVVVVV   Selection Tool

//Tool names and functions
const TOOL TOOL_LIST[] =
{
    [0] = {"goo-goo-bird-tools", goo_goo_bird_tools},

    #ifdef COMBINATION
    /*Add your tool! ex: [1] = {"your_tool_name", your_tool_main}
    添加你的工具！ 示範： [1] = {"your_tool_name", your_tool_main}*/
    [1] = {"goo-goo-calculator", goo_goo_calculator},
    #endif

    {NULL, NULL} //It is used to determine whether the list has been fully traversed, so this item is kept at the very end
};

/**
*  @brief        Look for a matching target tool name; otherwise return NOT_FOUND
*
*  @param tools        Name of the target tool and the corresponding function
*  @param arg       Shell input values
*  @param mod       Search mode
*
*  @return (*tool_main)(argc, argv, arg.envp)       Return value of the target tool
*  @return NOT_FOUND        No param matching the target tool name found
*/
inline int which_tool_core(const TOOL tools, const CLIarg arg, const int mod)
{
    int argc = arg.argc;
    char **argv = NULL;
    if(mod == SEARCH_MOD && arg.argc > 1)
    {
        for(int i = 1; i < arg.argc; i++)
        {
            if(!strcmp(arg.argv[i], tools.tool_name))
            {
                argv = (arg.argv + i);
                argc -= i;
                break;
            }
        }
    }
    else
    {
        argv = arg.argv;
    }
    if(argv != NULL && !strcmp(argv[0], tools.tool_name))
    {
        return (tools.tool_main)(argc, argv, arg.envp);
    }
    else
    {
    return NOT_FOUND;
    }
}

/**
 * @brief       Invoke the corresponding tool and return its return value
 *
 * @param argc         Number of incoming parameters
 * @param argv         Input parameter
 * @param envp         Input environment variables
 *
 * @return 4        No tool name matching those in TOOL_LIST was found
 * @return return_v        Return value of the target tool
 */
int main(int argc, char *argv[], char *envp[])
{
    //init var
    CLIarg arg = {argc, argv, envp};
    int return_v = NOT_FOUND;

    //Select Target Tool
    for(int tool = 0; TOOL_LIST[tool].tool_name != NULL; tool++)
    {
        return_v = which_tool_core(TOOL_LIST[tool], arg, DIRECT_MOD);
        if(return_v != NOT_FOUND) {break;}
    }
    if(return_v == NOT_FOUND)
    {
        int lang = (getenv("LC_ALL") && strcasestr(getenv("LC_ALL"), "zh") != NULL) ? ZH_CN:EN_US;
        bird_var var = {true, NULL};
        bird_var *var_p = &var;
        options_bird options[] =
        {
            [VERSION] = {'v', "--version", false}, //version
            [HELP] = {'h', "--help", false} //help
        };

        long_unknow(&var_p, arg, 0);
        options[HELP].switch_opt = true;
        goo_goo_bird_basic(lang, options, var);
    }

    return return_v;
}
