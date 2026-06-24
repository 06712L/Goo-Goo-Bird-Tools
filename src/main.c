#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include "lang.h"

typedef struct
{
    const char *desc;
    const char *opt_version;
    const char *opt_re_entry_remove;
}HELP;

typedef struct
{
    const char *tools_name;
    const char *tools_version;
    const char *tools_developer;
}VERSION;

const HELP help[] =
{
    [EN_US] =
    {
        .desc = "A toolbox that makes a cooing sound (but actually doesn't)",
        .opt_version = "-v, --version\t\tDisplays the version number",
        .opt_re_entry_remove = "re-entry-remove\t\tDeletes your file using re-entry."
    },

    [ZH] =
    {
        .desc = "一个会咕咕叫的工具箱（实际上不会）",
        .opt_version = "-v, --version\t\t显示版本号",
        .opt_re_entry_remove = "re-entry-remove\t\t使用再入大气层的方式删除您的档案"
    }
};

const VERSION version[] =
{
    [EN_US] =
    {
        .tools_name = "Goo-Goo-Bird Toolbox (GGB-Tools)",
        .tools_version = "GGB Version V0.1",
        .tools_developer = "GGB Developer: 06712L (Blue cat)"
    },

    [ZH] =
    {
        .tools_name = "Goo-Goo-Bird 工具箱 (GGB-Tools)",
        .tools_version = "GGB 版本 V0.1",
        .tools_developer = "GGB 开发者: 06712L(Blue cat)"
    }
};

int main(int avgc, char *avgv[])
{
    char *lang_t = getenv("LC_ALL");
    uint8_t lang = (lang_t && strcasestr(lang_t, "zh") != NULL) ? ZH:EN_US;
    if(!(strcmp(avgv[0], "goo-goo-bird-tools")))
    {
        if(avgc == 1)
        {
            //help
            printf("%s\n\n", help[lang].desc);
            printf("%s\n", help[lang].opt_version);
            printf("%s\n", help[lang].opt_re_entry_remove);
        }
        else if(avgc > 1)
        {
            if(!strcmp(avgv[1], "-v") || !strcmp(avgv[1], "--version"))
            {
                //version
                printf("%s\n", version[lang].tools_name);
                printf("%s\n", version[lang].tools_version);
                printf("%s\n", version[lang].tools_developer);
            }
        }
    }
    return 0;
}
