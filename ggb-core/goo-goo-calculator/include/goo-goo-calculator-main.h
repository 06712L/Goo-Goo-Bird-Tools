#ifndef GOO_GOO_CALCULATOR_MAIN_H
#define GOO_GOO_CALCULATOR_MAIN_H

#include <stdbool.h>

//vvvvvvvvvv    define

#define VERSION_TEXT "V0.1-DEV"

typedef struct
{
	int argc;
	char **argv;
	char **envp;
}CLIarg;

typedef struct
{
    const char short_opt;
    const char *long_opt;
    bool switch_opt;
}options;

typedef struct
{
	bool unknown_switch;
	char *unknown_text;
}unknown_var;

enum
{
	HELP = 0,
	VERSION = 1,
	CALCULATE = 2
};

#endif
