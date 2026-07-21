//Enable _GNU_SOURCE
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifdef COMBINATION
#include "goo-goo-calculator.h"
#endif
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "goo-goo-calculator-main.h"

enum
{
	EN_US = 0,
	ZH_CN = 1
};

typedef struct
{
	const char *unknown;
	const char *desc;
	const char *usage;
	const char *options;
	const char *opt_help;
	const char *opt_version;
	const char *opt_calculation;
}HELP_text;

typedef struct
{
	const char *tool_name;
	const char *tool_version;
}VERSION_text;

static const HELP_text help[] =
{
	[EN_US] =
	{
		.unknown = "Unknown parameter",
		.desc = "DESC: A calculator that doesn't go 'goo-goo'",
		.usage = "Usage: goo-goo-calculator [options] [-c <expression>] [--calculation=<expression>]",
		.options = "Options:",
		.opt_help = "\t-h, --help\t\tShow help information",
		.opt_version = "\t-v, --version\t\tShow version information",
		.opt_calculation = "\t-c, --calculation\t\tCalculate the result of the expression"
	},

	[ZH_CN] =
	{
		.unknown = "未知参数",
		.desc = "描述： 一個不會咕咕叫的計算機",
		.usage = "用法： goo-goo-calculator [options] [-c <表达式>] [--calculation=<表达式>]",
		.options = "选项：",
		.opt_help = "\t-h, --help\t\t显示辅助说明",
		.opt_version = "\t-v, --version\t\t显示版本相关讯息",
		.opt_calculation = "\t-c, --calculation\t\t计算表达式的答案"
	}
};

static const VERSION_text version[] =
{
	[EN_US] =
	{
		.tool_name = "GOO-GOO Calculator (GGC)",
		.tool_version = "GGC Version"
	},

	[ZH_CN] =
	{
		.tool_name = "GOO-GOO 计算器 (GGC)",
		.tool_version = "GGC 版本"
	}
};

/**
 * @brief      Output text
 *
 * @param[in]  arg   Shell input values
 * @param[in]  var   Unknown parameter
 * @param[in]  opt   The option's long name, short name, and flags
 * @param[in]  lang  Language
 */
static void show(const CLIarg arg, const unknown_var var, const options opt[], const int lang)
{
    if(opt[VERSION].switch_opt && !(var.unknown_switch))
    {
        printf("%s\n", version[lang].tool_name);
        printf("%s\n\n", version[lang].tool_version);
    }

    if(opt[HELP].switch_opt)
    {
        if(var.unknown_switch)
        {
            fprintf(stderr, "%s %s\n\n", help[lang].unknown, var.unknown_text);
        }
        printf("%s\n", help[lang].desc);
        printf("%s\n", help[lang].usage);
        printf("%s\n", help[lang].options);
        printf("%s\n", help[lang].opt_help);
        printf("%s\n", help[lang].opt_version);
        printf("%s\n\n", help[lang].opt_calculation);
    }

    return;
}

/**
 * @brief        Input the unknown param into var->unknow_text
 *
 * @param[out] var        Unknown parameter
 * @param[in] arg        Shell input values
 * @param[in] which_arg_unknow        Location of the unknown parameter
 */
static void long_unknow(unknown_var** var, const CLIarg arg, const int which_arg_unknow)
{
    (*var)->unknown_switch = true;
    (*var)->unknown_text = malloc(strlen(arg.argv[which_arg_unknow]) + 1); //The reason for adding 1 is to accommodate '\0'
    strcpy((*var)->unknown_text, arg.argv[which_arg_unknow]);
    return;
}

/**
 * @brief        Input the unknown param into var->unknow_text
 *
 * @param[out] var        Unknown parameter
 * @param[in] arg        Shell input values
 * @param[in] which_arg_unknow        Location of the unknown parameter
 * @param[in] which_unknow        The position of the unknown parameter in the position
 * @param[in] len        Parameter string length
 */
static void short_unknow(unknown_var** var, const CLIarg arg, const int which_arg_unknow, const int which_unknow, const size_t len)
{
    (*var)->unknown_switch = true;
    if(len < 2)
    {
        (*var)->unknown_text = malloc(sizeof(char) + 1);
        sprintf((*var)->unknown_text, "-");
    }
    else
    {
        (*var)->unknown_text = malloc(sizeof(char) + 2); //The reason for adding 2 is to accommodate '-' and '\0'
        sprintf((*var)->unknown_text, "-%c", arg.argv[which_arg_unknow][which_unknow]);
    }
    return;
}

/**
 * @brief        Parse the options passed to goo-goo-calculator.
 *
 * @param[in] arg        Shell input values
 * @param[out] var        Unknown parameter
 * @param[in] options        The option's long name, short name, and flags
 *
 * @return 0        Executing normally
 * @return 1        Encountered an unknown option
 */
static int argument_analysis(const CLIarg arg, unknown_var* var, options options[])
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
                    return 1;
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
                    return 1;
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
                        return 1;
                    }
                }
            }
        }

        else
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
                return 1;
            }
        }
    }
    return 0;
}

/**
 * @brief      Prepare the required variables and call the corresponding function.
 *
 * @param[in] argc  Number of incoming parameters
 * @param[in] argv  Input parameter
 * @param[in] envp  Input environment variables
 *
 * @return     0  No errors
 * @return     1  Minor error
 */
int goo_goo_calculator(int argc, char *argv[], char *envp[])
{
	CLIarg arg = {argc, argv, envp};
	int return_v = 0;
	int lang = (getenv("LANG") && strcasestr(getenv("LANG"), "zh") != NULL) ? ZH_CN:EN_US;
	options opt[] =
	{
		[HELP] = {'h', "--help", false},
		[VERSION] = {'v', "--version", false},
		[CALCULATE] = {'c', "--calculation", false},

		{'\0', NULL, false}
	};
	unknown_var unk_var = {false, NULL};

    return_v = argument_analysis(arg, &unk_var, opt);
    show(arg, unk_var, opt, lang);

	if(unk_var.unknown_text)
	{
		free(unk_var.unknown_text);
		unk_var.unknown_text = NULL;
	}
	return return_v;
}
