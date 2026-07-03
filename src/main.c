#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include "lang.h"

enum
{
    VERSION = 0,
    HELP = 1
};

typedef struct
{
    bool version;
    bool help;
}options;

typedef struct
{
    const char *what;
    const char *desc;
    const char *usage;
    const char *options;
    const char *opt_help;
    const char *opt_version;
    const char *tools;
    const char *tool_re_entry_remove;
}HELP_t;

typedef struct
{
    const char *tools_name;
    const char *tools_version;
    const char *tools_developer;
}VERSION_t;

const HELP_t help[] =
{
    [EN_US] =
    {
        .what = "There is an imposter parameter among us.",
        .desc = "DESC: A toolbox that makes a cooing sound (but actually doesn't)",
        .usage = "USAGE: goo-goo-bird-tools [options] / [tool] [options] ...",
        .options = "options:",
        .opt_help = "\t-h, --help\t\tShow this help message",
        .opt_version = "\t-v, --version\t\tDisplays the version number",
        .tools = "tools:",
        .tool_re_entry_remove = "\tre-entry-remove\t\tDeletes your file using re-entry."
    },

    [ZH] =
    {
        .what = "在我们之中有冒牌参数",
        .desc = "描述：一个会咕咕叫的工具箱（实际上不会）",
        .usage = "用法：goo-goo-bird-tools [選項] / [工具] [選項] ...",
        .options = "選項:",
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
        .tools_name = "Goo-Goo-Bird Toolbox (GGB-Tools)",
        .tools_version = "GGB Version V0.1",
        .tools_developer = "GGB Developer: 06712L (A penguin)"
    },

    [ZH] =
    {
        .tools_name = "Goo-Goo-Bird 工具箱 (GGB-Tools)",
        .tools_version = "GGB 版本 V0.1",
        .tools_developer = "GGB 开发者: 06712L (A penguin)"//I use sublime text 4, btw; hehe
    }
};



static void goo_goo_bird_basic(options options, int lang, bool need_more, bool what_is_that)
{
    //version
    if(options.version && !what_is_that)
    {
        printf("%s\n", version[lang].tools_name);
        printf("%s\n", version[lang].tools_version);
        printf("%s\n", version[lang].tools_developer);
        if(need_more) {putchar('\n');}
    }

    //help
    if(options.help)
    {
        if(what_is_that) {printf("%s\n\n", help[lang].what);}
        printf("%s\n", help[lang].desc);
        printf("%s\n", help[lang].usage);
        printf("%s\n", help[lang].options);
        printf("%s\n", help[lang].opt_help);
        printf("%s\n", help[lang].opt_version);
        printf("%s\n", help[lang].tools);
        printf("%s\n", help[lang].tool_re_entry_remove);
    }

    return;
}

static void argument_analysis(int argc, char *argv[], options *options, bool *need_more, bool *what_is_that)
{
    int count = 0;
    if(argc > 1)
    {
        for(int i = 1; i < argc; i++)
        {
            if(argv[i][0] == '-')
            {
                if(argv[i][1] == '-')
                {
                    if(!strcmp(argv[i], "--version")) {options->version = true; count++;}
                    else if(!strcmp(argv[i], "--help")) {options->help = true; count++;}
                    else {*what_is_that = true;options->help = true; return;}
                }
                else
                {
                    int len = strlen(argv[i]);
                    for(int j = 1; j < len; j++)
                    {
                        switch (argv[i][j])
                        {
                            case 'v':
                                options->version = true;
                                count++;
                                break;
                            case 'h':
                                options->help = true;
                                count++;
                                break;
                            default:
                                *what_is_that = true;
                                options->help = true;
                                return;
                        };
                    }
                }
            }
            else if(!strcmp(argv[i], "re-entry-remove")) {puts("I haven't developed it yet.");return;}
            else if(!strcmp(argv[i], "why")) {puts("No reason.");return;}
            else {*what_is_that = true;options->help = true; return;}
        }
    }
    else {options->help = true;} //default

    if(count > 1) {*need_more = true;}
    return;
}

int main(int argc, char *argv[], char *envp[])
{
    int lang = (getenv("LC_ALL") && strcasestr(getenv("LC_ALL"), "zh") != NULL) ? ZH:EN_US;
    if(!strcmp(argv[0], "goo-goo-bird-tools"))
        {
            bool need_more = false, what_is_that = false;
            options options;
            options.version = false;
            options.help = false;

            argument_analysis(argc, argv, &options, &need_more, &what_is_that);
            goo_goo_bird_basic(options, lang, need_more, what_is_that);
        }
    return 0;
}
