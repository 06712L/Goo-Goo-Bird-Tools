#ifndef INSTALLER_H
#define INSTALLER_H

#include <stdbool.h>
#include <stdint.h>

//vvvv		define

typedef struct
{
	char *install_path;
	char *user_path;
	uint8_t lang;
	bool envp_path;
	bool link;
}install_var;

enum
{
	EN_US = 0,
	ZH_CN = 1,
	ZH_HANT = 2
};

//vvvv		installer.c

int installer_main(install_var var);

#endif
