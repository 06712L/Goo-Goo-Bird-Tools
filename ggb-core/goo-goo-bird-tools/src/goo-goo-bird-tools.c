//Enable _GNU_SOURCE
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "cliargs.h"
#include "lang.h"
#include "goo-goo-bird-tools.h"
#include "selectiontool.h"

//VVVVVVVV    goo-goo-bird-tools

//HELP options
typedef struct
{
    const char *what;
    const char *desc;
    const char *usage;
    const char *options;
    const char *opt_help;
    const char *opt_version;
    const char *tools;
    /*Add your tool description! ex: const char *tool_YourToolName;
    添加你的工具說明！ 示範： const char *tool_YourToolName;*/
    const char *goo_goo_calculator;
}HELP_t;

//VERSION options
typedef struct
{
    const char *tools_name;
    const char *tools_version;
}VERSION_t;

const HELP_t help[] =
{
    [EN_US] =
    {
        .what = "There's a fake parameter among us, possibly",
        .desc = "DESC: A toolbox that makes a cooing sound (but actually doesn't)",
        .usage = "USAGE: goo-goo-bird-tools [options] or [tool] [options] [target]",
        .options = "options:",
        .opt_help = "\t-h, --help\t\tShow this help message",
        .opt_version = "\t-v, --version\t\tDisplays the version number",
        .tools = "tools:",
        //Add your tool description! ex: .tool_YourToolName = "\tyour_tool_name\t\tIs a tool";
        .goo_goo_calculator = "\tgoo-goo-calculator\t\tA computer in the CLI"
    },

    [ZH_CN] =
    {
        .what = "在我们之中有冒牌参数,可能是",
        .desc = "描述：一个会咕咕叫的工具箱（实际上不会）",
        .usage = "用法：goo-goo-bird-tools [选择] 或者 [工具] [选择] [目标]",
        .options = "选择:",
        .opt_help = "\t-h, --help\t\t显示此辅助说明",
        .opt_version = "\t-v, --version\t\t显示版本号",
        .tools = "工具:",
        //添加你的工具說明！ 示範： .tool_YourToolName = "\tyour_tool_name\t\t這是個工具";
        .goo_goo_calculator = "\tgoo-goo-calculator\t\t一个在CLI中的计算机"
    }
};

const VERSION_t version[] =
{
    [EN_US] =
    {
        .tools_name = "Goo-Goo-Bird Toolbox (GGB-tools)",
        .tools_version = "GGB Version",
    },

    [ZH_CN] =
    {
        .tools_name = "Goo-Goo-Bird 工具箱 (GGB-tools)",
        .tools_version = "GGB 版本",
    }
};

/**
 * @brief        Display the selection for goo-goo-bird-tools, the tools included in the toolbox, and version information
 *
 * @param[in] lang        Language
 * @param[in] options        options's flags
 * @param[in] var        Variables for goo-goo-bird-tools
 */
void goo_goo_bird_basic(int lang, options_bird options[], bird_var var)
{
    //version
    if(options[VERSION].switch_opt && !var.what_is_that)
    {
        printf("%s\n", version[lang].tools_name);
        printf("%s %s\n\n", version[lang].tools_version, VERSION_text);
    }

    //help
    if(options[HELP].switch_opt)
    {
        if(var.what_is_that) {printf("%s %s\n\n", help[lang].what, var.unknown);}
        printf("%s\n", help[lang].desc);
        printf("%s\n", help[lang].usage);
        printf("%s\n", help[lang].options);
        printf("%s\n", help[lang].opt_help);
        printf("%s\n", help[lang].opt_version);
        printf("%s\n", help[lang].tools);
        //Add your tool description! ex: printf("%s\n\n", help[lang].your_tool_desc);
        //添加你的工具說明！ 示範： printf("%s\n\n", help[lang].your_tool_desc);
        //For the final `printf()`, remember to use `\n\n`, and change the preceding `printf()` to use `\n`

        printf("%s\n\n", help[lang].goo_goo_calculator);
    }

    return;
}

/**
 * @brief        Input the unknown param into var->unknow
 *
 * @param[in, out] var        Variables for goo-goo-bird-tools
 * @param[in] arg        Shell input values
 * @param[in] which_arg_unknow        Location of the unknown parameter
 */
void long_unknow(bird_var** var, const CLIarg arg, const int which_arg_unknow)
{
    (*var)->what_is_that = true;
    (*var)->unknown = malloc(strlen(arg.argv[which_arg_unknow]) + 1); //The reason for adding 1 is to accommodate '\0'
    strcpy((*var)->unknown, arg.argv[which_arg_unknow]);
    return;
}

/**
 * @brief        Input the unknown param into var->unknow
 *
 * @param[in, out] var        Variables for goo-goo-bird-tools
 * @param[in] arg        Shell input values
 * @param[in] which_arg_unknow        Location of the unknown parameter
 * @param[in] which_unknow        The position of the unknown parameter in the position
 * @param[in] len        Parameter string length
 */
static void short_unknow(bird_var** var, const CLIarg arg, const int which_arg_unknow, const int which_unknow, const size_t len)
{
    (*var)->what_is_that = true;
    if(len < 2)
    {
        (*var)->unknown = malloc(sizeof(char) + 1);
        sprintf((*var)->unknown, "-");
    }
    else
    {
        (*var)->unknown = malloc(sizeof(char) + 2); //The reason for adding 2 is to accommodate '-' and '\0'
        sprintf((*var)->unknown, "-%c", arg.argv[which_arg_unknow][which_unknow]);
    }
    return;
}

/**
 * @brief        Parse the options and tool name passed to goo-goo-bird-tools
 *
 * @param[in] arg        Shell input values
 * @param[in, out] var        Variables for goo-goo-bird-tools
 * @param[in] options        The option's long name, short name, and flags
 *
 * @return 0        Executing normally
 * @return other        Return value from the called tool
 */
static int argument_analysis(CLIarg arg, bird_var* var, options_bird options[])
{
    if(arg.argc < 2)
    {
        options[HELP].switch_opt = true;
    }
    for(int i = 1; i < arg.argc; i++)
    {
        if(arg.argv[i][0] == '-')
        {
            //long opt
            if(arg.argv[i][1] == '-')
            {
                bool find = false;
                for(int opt = 0; options[opt].short_opt != '\0'; opt++)
                {
                    if(!strcmp(arg.argv[i], options[opt].long_opt))
                    {
                        options[opt].switch_opt = true;
                        find = true;
                    }
                }
                if(!find)
                {
                    options[HELP].switch_opt = true;
                    long_unknow(&var, arg, i);
                    break;
                }
            }

            //short opt
            else
            {
                size_t opt_len = strlen(arg.argv[i]);
                if(opt_len < 2)
                {
                    options[HELP].switch_opt = true;
                    short_unknow(&var, arg, i, 0, opt_len);
                    break;
                }
                for(int j = 1; j < opt_len; j++)
                {
                    bool find = false;
                    for(int opt = 0; options[opt].short_opt != '\0'; opt++)
                    {
                        if(arg.argv[i][j] == options[opt].short_opt)
                        {
                            options[opt].switch_opt = true;
                            find = true;
                        }
                    }
                    //not found
                    if(!find)
                    {
                        options[HELP].switch_opt = true;
                        short_unknow(&var, arg, i, j, opt_len);
                        break;
                    }
                }
            }
        }

        else
        {
            int return_v = NOT_FOUND;
            for(int tool = 1; TOOL_LIST[tool].tool_name != NULL; tool++)
            {
                return_v = which_tool_core(TOOL_LIST[tool], arg, SEARCH_MOD);
                if(return_v != NOT_FOUND)
                {
                    return return_v;
                }
            }
            //no target tool found
            if(return_v == NOT_FOUND)
            {
                options[HELP].switch_opt = true;
                long_unknow(&var, arg, i);
                break;
            }
        }
    }
    return 0;
}

/**
 * @brief         Prepare variables for subsequent parsing and display, and return the return value
 *
 * @param[in] argc         Number of incoming parameters
 * @param[in] argv         Input parameter
 * @param[in] envp         Input environment variables
 *
 * @return 0        Return value from the tool during normal program execution or a tool call
 * @return 4        No tool name matching those in TOOL_LIST was found
 * @return other        Return value from the called tool
 */
int goo_goo_bird_tools(int argc, char *argv[], char *envp[])
{
    CLIarg arg = {argc, argv, envp};
    int lang = (getenv("LANG") && strcasestr(getenv("LANG"), "zh") != NULL) ? ZH_CN:EN_US;
    bird_var var = {false, NULL};
    options_bird options[] =
    {
        [VERSION] = {'v', "--version", false}, //version
        [HELP] = {'h', "--help", false}, //help
        {'\0', NULL, false} //It is used to determine whether the list has been fully traversed, so this item is kept at the very end
    };

    int return_v = 0;

    return_v = argument_analysis(arg, &var, options);
    goo_goo_bird_basic(lang, options, var);
    if(var.unknown)
    {
        free(var.unknown);
        var.unknown = NULL;
    }
    return return_v;
}
