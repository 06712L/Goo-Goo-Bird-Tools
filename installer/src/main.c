#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "installer.h"

static inline bool see_text(const char *src_text, const char *need_text)
{
	if(strcasestr(src_text, need_text) != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

static uint8_t switch_language(const char *lang)
{
	if(lang == NULL)
	{
		return EN_US;
	}
	if(see_text(lang, "zh"))
	{
		if(see_text(lang, "TW") || see_text(lang, "HK") || see_text(lang, "MO"))
		{
			return ZH_HANT;
		}
		else
		{
			return ZH_CN;
		}
	}
	else
	{
		return EN_US;
	}
}

int main(int argc, char *envp[])
{
	install_var install_var = {NULL, getenv("PATH"), switch_language(getenv("LANG")), false, false};

	return installer_main(install_var);
}
