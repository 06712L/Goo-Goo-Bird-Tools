#ifndef GOO_GOO_BIRD_TOOLS_H
#define GOO_GOO_BIRD_TOOLS_H

#define bool _Bool

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

int goo_goo_bird_tools(int argc, char *argv[], char *envp[]);
void goo_goo_bird_basic(int lang, options_bird options[], bird_var var);

#endif
