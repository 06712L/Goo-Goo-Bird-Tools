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



static void goo_goo_bird_basic(bool options[], int lang, bool need_more)
{
    //version
    if(options[VERSION])
    {
        printf("%s\n", version[lang].tools_name);
        printf("%s\n", version[lang].tools_version);
        printf("%s\n", version[lang].tools_developer);
        if(need_more) {putchar('\n');}
    }

    //help
    if(options[HELP])
    {
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

static void argument_analysis(int argc, char *argv[],bool (*options)[], bool *need_more)
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
                    if((strcasestr(argv[i], "version") - argv[i]) > 1) {(*options)[VERSION] = (bool)true; count++;}
                    else if((strcasestr(argv[i], "help") - argv[i]) > 1) {(*options)[HELP] = (bool)true; count++;}
                    else {(*options)[HELP] = (bool)true; return;}
                }
                else
                {
                    int len = strlen(argv[i]);
                    for(int j = 1; j < len; j++)
                    {
                        if (argv[i][j] == 'v') {(*options)[VERSION] = (bool)true; count++;}
                        else if(argv[i][j] == 'h') {(*options)[HELP] = (bool)true; count++;}
                        else {(*options)[HELP] = (bool)true; return;}
                    }
                }
            }
        }
    }
    else {(*options)[HELP] = (bool)true;;} //default

    if(count > 1) {*need_more = (bool)true;}
    return;
}

int main(int argc, char *argv[], char *envp[])
{
    int lang = (getenv("LC_ALL") && strcasestr(getenv("LC_ALL"), "zh") != NULL) ? ZH:EN_US;
    if(!strcmp(argv[0], "goo-goo-bird-tools"))
        {
            bool need_more = false;
            bool options[2];
            for(uint8_t i = 0; i < 2; i++) {options[i] = false;}
            argument_analysis(argc, argv, &options, &need_more);
            goo_goo_bird_basic(options, lang, need_more);
        }
    return 0;
}
