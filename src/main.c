#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include "lang.h"

typedef struct
{
    const char *desc;
    const char *opt_version;
    const char *opt_re_entry_remove;
}Messages;

const Messages help[] =
{
    [EN_US] =
    {
        .dect = "A toolbox that makes a cooing sound (but actually doesn't)",
        .opt_version = "-v, --version\t\tDisplays the version number",
        .opt_re_entry_remove = "re-entry-remove\t\tDeletes your file using re-entry."
    },

    [ZH] =
    {
        .dect = "一个会咕咕叫的工具箱（实际上不会）",
        .opt_version = "-v, --version\t\t显示版本号",
        .opt_re_entry_remove = "re-entry-remove\t\t使用再入大气层的方式删除您的档案"
    }
}

int main(int avgc, char *avgv[])
{
    char *lang = getenv("LC_ALL");
    if(!(strcmp(avgv[0], "goo-goo-bird-tools")))
    {

    }
}
