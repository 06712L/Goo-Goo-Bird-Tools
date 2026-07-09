#ifndef SELECTIONTOOL_H
#define SELECTIONTOOL_H

#include "cliargs.h"

enum
{
    NOT_FOUND = 4,
    HOW_MUCH_TOOLS = 1
};

typedef struct
{
    const char *tool_name;
    int (*tool)(int argc, char **argv, char **envp);
}TOOL;

extern const TOOL TOOL_LIST[];

int which_tool_core(const char* tool_name, int (*tool_main)(int argc, char* argv[], char* envp[]), const CLIarg arg, const char* mod);

#endif
