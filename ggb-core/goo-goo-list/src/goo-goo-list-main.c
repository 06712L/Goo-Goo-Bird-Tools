// Enable _GNU_SOURCE
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "goo-goo-list-main.h"
#include "ggb-basic/goo-goo-language.h"
#include "ggb-basic/goo-goo-version.h"
#include "lib/goo-goo-getopt.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef COMBINATION
#include "goo-goo-list.h"
#endif

enum
{
	VERSION,
	HELP
};

typedef struct
{
	const char *desc;
	const char *usage;
	const char *options;
	const char *opt_help;
	const char *opt_version;
} HELP_TEXT;

typedef struct
{
	const char *tool_name;
	const char *tool_version;
} VERSION_TEXT;

static const HELP_TEXT help[] = {
    [EN_US] = {.desc = "Description: A tool that doesn't 'goo-goo', used to list files in a specified directory",
               .usage = "Usage: goo-goo-list [OPTION]... [DIRECTORY]",
               .options = "Options:",
               .opt_help = "\t-h, --help\t\tShow help information",
               .opt_version = "\t-v, --version\t\tShow version information"},

    [ZH_CN] = {.desc = "描述： 一个不会咕咕叫的工具，用于列出指定目录的档案",
               .usage = "用法： goo-goo-list [选项]... [目录]",
               .options = "选项：",
               .opt_help = "\t-h, --help\t\t显示帮助信息",
               .opt_version = "\t-v, --version\t\t显示版本信息"}};

static const VERSION_TEXT version[] = {[EN_US] = {.tool_name = "GGL (Goo-Goo-List)", .tool_version = "GGL Version: "},

                                       [ZH_CN] = {.tool_name = "GGL (Goo-Goo-List)", .tool_version = "GGL 版本： "}};

static void show(const int lang, const OPT_LIST opt[])
{
	if (opt[VERSION].flag)
	{
		printf("%s\n", version[lang].tool_name);
		printf("%s%s\n", version[lang].tool_version, GOO_GOO_VERSION);
	}
	if (opt[HELP].flag)
	{
		printf("%s\n", help[lang].desc);
		printf("%s\n", help[lang].usage);
		printf("%s\n", help[lang].options);
		printf("%s\n", help[lang].opt_help);
		printf("%s\n", help[lang].opt_version);
	}
	return;
}

int goo_goo_list_main(int argc, char *argv[], char *envp[])
{
	int lang = (getenv("LANG") && strcasestr(getenv("LANG"), "zh") != NULL) ? ZH_CN : EN_US;
	OPT_LIST opt[] = {[VERSION] = {'v', "version", false}, [HELP] = {'h', "help", false}, {'\0', NULL, NULL}};
	int opt_var = goo_goo_getopt(argc, (const char **)argv, opt);
	if (opt_var == NO_OPT_FOUND)
	{
		opt[HELP].flag = true;
	}
	show(lang, opt);
	return 0;
}
