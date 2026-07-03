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
}options_s;

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
}VERSION_t;

const HELP_t help[] =
{
    [EN_US] =
    {
        .what = "There's a fake parameter among us, possibly",
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
        .what = "在我们之中有冒牌参数,可能是",
        .desc = "描述：一个会咕咕叫的工具箱（实际上不会）",
        .usage = "用法：goo-goo-bird-tools [选择] / [工具] [选择] ...",
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



static void goo_goo_bird_basic(options_s options, int lang, bool need_more, bool what_is_that, char *unknown)
{
    //version
    if(options.version && !what_is_that)
    {
        printf("%s\n", version[lang].tools_name);
        printf("%s\n", version[lang].tools_version);
        if(need_more) {putchar('\n');}
    }

    //help
    if(options.help)
    {
        if(what_is_that) {printf("%s %s\n\n", help[lang].what, unknown);}
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

static void unknown_parameter(char *target, options_s **options, bool **what_is_that, char ***unknown, char *mod)
{
    if(!strcmp(mod, "long"))
    {
        **unknown = malloc(strlen(target) + 1);
        strcpy(**unknown, target);
    }
    else if(!strcmp(mod, "short"))
    {
        **unknown = malloc(3 * sizeof(char));
        sprintf(**unknown, "-%c", *target);
    }
    **what_is_that = true;
    (*options)->help = true;
    return;
}

static void argument_analysis(int argc, char *argv[], options_s *options, bool *need_more, bool *what_is_that, char **unknown)
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
                    else
                    {
                        unknown_parameter(argv[i], &options, &what_is_that, &unknown, "long");
                        return;
                    }
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
                                unknown_parameter(&argv[i][j], &options, &what_is_that, &unknown, "short");
                                return;
                        };
                    }
                }
            }
            else if(!strcmp(argv[i], "re-entry-remove"))
            {
                puts("I haven't developed it yet.");
                return;
            }
            else
            {
                unknown_parameter(argv[i], &options, &what_is_that, &unknown, "long");
                return;
            }
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
            char *unknown = NULL;
            options_s options;
            options.version = false;
            options.help = false;

            argument_analysis(argc, argv, &options, &need_more, &what_is_that, &unknown);
            goo_goo_bird_basic(options, lang, need_more, what_is_that, unknown);
            if(unknown) {free(unknown);}
        }
    return 0;
}
