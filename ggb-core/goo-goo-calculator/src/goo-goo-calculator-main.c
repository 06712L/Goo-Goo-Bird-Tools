#ifdef COMBINATION
#include "goo-goo-calculator.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
	EN_US = 0,
	ZH_CN = 1
};

typedef struct
{
	const char *text;
}Placeholder_text;

const Placeholder_text a_text[] =
{
	[EN_US] =
	{
		.text = "This tool is currently under development; stay tuned"
	},
	[ZH_CN] =
	{
		.text = "此工具正在开发，敬请期待"
	}
};

int goo_goo_calculator(int argc, char *argv[], char *envp[])
{
	int lang = (getenv("LC_ALL") && strcasestr(getenv("LC_ALL"), "zh") != NULL) ? ZH_CN:EN_US;

	printf("%s\n", a_text[lang].text);

	return 0;
}
