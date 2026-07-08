#ifndef GOO_GOO_BIRD_TOOLS_H
#define GOO_GOO_BIRD_TOOLS_H

#include <stdbool.h>
#include "cliargs.h"

enum
{
    VERSION = 0,
    HELP = 1,
    MAX_OPT = 2 //How much opt
};

typedef struct
{
    const char short_opt;
    const char *long_opt;
    bool switch_opt;
}options_bird;

typedef struct
{
    bool what_is_that;
    char *unknown;
}bird_var;

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

int goo_goo_bird_tools(int argc, char **argv, char **envp);
int argument_analysis(CLIarg arg, bird_var* var, options_bird options[]);

#endif
