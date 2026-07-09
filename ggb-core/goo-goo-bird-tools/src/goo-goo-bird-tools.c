#include <iso646.h>
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
    添加你的工具說明！ 示範：.const char *tool_YourToolName;*/
}HELP_t;

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
        .tools = "tools:"
        //Add your tool description! ex: .tool_YourToolName = "\tyour_tool_name\t\tIs a tool";
    },

    [ZH_CN] =
    {
        .what = "在我们之中有冒牌参数,可能是",
        .desc = "描述：一个会咕咕叫的工具箱（实际上不会）",
        .usage = "用法：goo-goo-bird-tools [选择] 或者 [工具] [选择] [目标]",
        .options = "选择:",
        .opt_help = "\t-h, --help\t\t显示此辅助说明",
        .opt_version = "\t-v, --version\t\t显示版本号",
        .tools = "工具:"
        //添加你的工具說明！ 示範：.tool_YourToolName = "\tyour_tool_name\t\t這是個工具";
    }
};

const VERSION_t version[] =
{
    [EN_US] =
    {
        .tools_name = "Goo-Goo-Bird Toolbox (GGB-tools)",
        .tools_version = "GGB Version V0.1",
    },

    [ZH_CN] =
    {
        .tools_name = "Goo-Goo-Bird 工具箱 (GGB-tools)",
        .tools_version = "GGB 版本 V0.1",
    }
};

void goo_goo_bird_basic(int lang, options_bird options[], bird_var var)
{
    //version
    if(options[VERSION].switch_opt && !var.what_is_that)
    {
        printf("%s\n", version[lang].tools_name);
        printf("%s\n\n", version[lang].tools_version);
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
        printf("%s\n", "\tNothing");
    }

    return;
}

static void long_unknow(bird_var** var, const CLIarg arg, const int which_arg_unknow)
{
    (*var)->what_is_that = true;
    (*var)->unknown = malloc(strlen(arg.argv[which_arg_unknow]) + 1);
    strcpy((*var)->unknown, arg.argv[which_arg_unknow]);
    return;
}

static void short_unknow(bird_var** var, const CLIarg arg, const int which_arg_unknow, const int which_unknow, const int len)
{
    (*var)->what_is_that = true;
    if(len < 2)
    {
        (*var)->unknown = malloc(sizeof(char));
        sprintf((*var)->unknown, "-");
    }
    else
    {
        (*var)->unknown = calloc((sizeof(arg.argv[which_arg_unknow][which_unknow]) + 1), sizeof(char));
        sprintf((*var)->unknown, "-%c", arg.argv[which_arg_unknow][which_unknow]);
    }
    return;
}

static int argument_analysis(CLIarg arg, bird_var* var, options_bird options[])
{
    for(int i = 1; i < arg.argc; i++)
    {
        if(arg.argv[i][0] == '-')
        {
            //long opt
            if(arg.argv[i][1] == '-')
            {
                bool find = false;
                for(int opt = 0; opt < MAX_OPT; opt++)
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

                int opt_len = strlen(arg.argv[i]);
                if(opt_len < 2)
                {
                    options[HELP].switch_opt = true;
                    short_unknow(&var, arg, i, 0, opt_len);
                    break;
                }

                for(int j = 1; j < opt_len; j++)
                {
                    bool find = false;
                    for(int opt = 0; opt < MAX_OPT; opt++)
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
        else if(arg.argc > 1)
        {
            int return_v = NOT_FOUND;
            for(int tool = 1; tool < HOW_MUCH_TOOLS; tool++)
            {
                return_v = which_tool_core(TOOL_LIST[tool].tool_name, TOOL_LIST[tool].tool, arg, "search");
                if(return_v != NOT_FOUND)
                {
                    break;
                }
            }

            if(return_v == NOT_FOUND)
            {
                options[HELP].switch_opt = true;
                long_unknow(&var, arg, i);
                break;
            }
        }
        else
        {
            options[HELP].switch_opt = true;
        }
    }
    return 0;
}

int goo_goo_bird_tools(int argc, char *argv[], char *envp[])
{
    sleep(1);
    CLIarg arg = {argc, argv, envp};
    int lang = (getenv("LC_ALL") && strcasestr(getenv("LC_ALL"), "zh") != NULL) ? ZH_CN:EN_US;
    bird_var var = {false, NULL};
    options_bird options[] =
    {
        [VERSION] = {'v', "--version", false}, //version
        [HELP] = {'h', "--help", false} //help
    };

    int return_v = 1;

    return_v = argument_analysis(arg, &var, options);
    goo_goo_bird_basic(lang, options, var);
    return return_v;
}
