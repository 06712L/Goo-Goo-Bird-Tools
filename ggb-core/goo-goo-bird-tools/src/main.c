#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "cliargs.h"
#include "lang.h"
#include "goo-goo-bird-tools.h"

//VVVVVV   Selection Tool
static inline int which_tool_core(const char* tool_name, int (*tool_main)(int argc, char* argv[], char* envp[]), CLIarg* arg, char* mod)
{
    /*
    *   Mod:
    *   search    Iterate until the target is found.
    *   direct    Check only whether the first one is the target.
    */
    char **argv = NULL;
    if(!strcmp(mod, "search"))
    {
        for(int i = 0; i < arg->argc; i++)
        {
            if(!strcmp(arg->argv[i], tool_name))
            {
                argv = &(arg->argv[i]);
                break;
            }
        }
    }
    else
    {
        argv = &(arg->argv[0]);
    }
    if(!strcmp(argv[0], tool_name))
    {
        return (*tool_main)(arg->argc, argv, arg->envp);
    }
    return 0;
}

typedef struct
{
    const char *tool_name;
    int (*tool)(int argc, char **argv, char **envp);
}TOOL;

const TOOL TOOL_LIST[] =
{
    [0] = {"goo-goo-bird-tools", goo_goo_bird_tools}
};

int main(int argc, char *argv[], char *envp[])
{
    CLIarg arg = {argc, argv, envp};
    int return_v = 0;
    for(int tool = 0; tool < 1; tool++)
    {
        return which_tool_core(TOOL_LIST[tool].tool_name, TOOL_LIST[tool].tool, &arg, "direct");
    }

    return return_v;
}

//VVVVVVVV    goo-goo-bird-tools
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
        .tool_re_entry_remove = "\tre-entry-remove\t\tDeletes your file using re-entry."
    },

    [ZH] =
    {
        .what = "在我们之中有冒牌参数,可能是",
        .desc = "描述：一个会咕咕叫的工具箱（实际上不会）",
        .usage = "用法：goo-goo-bird-tools [选择] 或者 [工具] [选择] [目标]",
        .options = "选择:",
        .opt_help = "\t-h, --help\t\t显示此辅助说明",
        .opt_version = "\t-v, --version\t\t显示版本号",
        .tools = "工具:",
        .tool_re_entry_remove = "\tre-entry-remove\t\t使用再入大气层的方式删除您的档案"
    }
};

const VERSION_t version[] =
{
    [EN_US] =
    {
        .tools_name = "Goo-Goo-Bird Toolbox (GGB-tools)",
        .tools_version = "GGB Version V0.1",
    },

    [ZH] =
    {
        .tools_name = "Goo-Goo-Bird 工具箱 (GGB-tools)",
        .tools_version = "GGB 版本 V0.1",
    }
};

static void goo_goo_bird_basic(int lang, options_bird options[], bird_var var)
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
        printf("%s\n\n", help[lang].tool_re_entry_remove);
    }

    return;
}

int argument_analysis(CLIarg arg, bird_var* var, options_bird options[])
{
    for(int i = 1; i < arg.argc; i++)
    {
        if(arg.argv[i][0] == '-')
        {
            //long opt
            if(arg.argv[i][1] == '-')
            {
                for(int j = 1; j < MAX_OPT; j++)
                {
                    for(int opt = 0; opt < MAX_OPT; opt++)
                    {
                        if(!strcmp(arg.argv[j], options[opt].long_opt))
                        {
                            options[opt].switch_opt = true;
                        }
                    }
                }
            }
            //short opt
            else
            {
                int opt_len = strlen(arg.argv[i]);
                if(opt_len < 2)
                {
                    return 0;
                }

                for(int j = 1; j < opt_len; j++)
                {
                    for(int opt = 0; opt < MAX_OPT; opt++)
                    {
                        if(arg.argv[i][j] == options[opt].short_opt)
                        {
                            options[opt].switch_opt = true;
                        }
                    }
                }
            }
        }
        else
        {
            for(int tool = 0; tool < 1; tool++)
            {
                return which_tool_core(TOOL_LIST[tool].tool_name, TOOL_LIST[tool].tool, &arg, "direct");
            }
        }
    }
    return 0;
}

int goo_goo_bird_tools(int argc, char *argv[], char *envp[])
{
    CLIarg arg = {argc, argv, envp};
    int lang = (getenv("LC_ALL") && strcasestr(getenv("LC_ALL"), "zh") != NULL) ? ZH:EN_US;
    bird_var var = {false, NULL};
    options_bird options[] =
    {
        [VERSION] = {'v', "--version", false}, //version
        [HELP] = {'h', "--help", false} //help
    };

    argument_analysis(arg, &var, options);
    goo_goo_bird_basic(lang, options, var);
    return 0;
}
