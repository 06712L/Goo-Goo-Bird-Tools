//#include <stdio.h>

#include "installer.h"

typedef struct
{
	const char *choose_install_path;
	const char *input_install_path;
	const char *want_create_link;
	const char *check;

	//vvvv		path_error

	const char *error_path;
	const char *no_folder_found;
}show_text;

enum
{
	CHOOSE_INSALL_PATH,
	INPUT_INSTALL_PATH,
	WANT_CREATE_LINK,
	CHECK,

	//vvvv		path_error

	ERROR_PATH,
	NOT_FOLDER_FOUND
};

show_text show[] =
{
	[EN_US] =
	{
		.choose_install_path = "Select installation directory:\n\n[1]/usr/local\n[2]/usr/bin\n[3]/bin\n[4]~/.local/bin\n[5]Custom path\n\n",
		.input_install_path = "Enter installation path:\n",
		.want_create_link = "Create a symbolic link for the tool in the installation directory? (y/N)\n",
		.check = "The installation directory is not in your PATH. Add it to PATH? (Y/n)\n",

		.error_path = "Please re-enter the installation path\n",
		.no_folder_found = "Installation directory not found. Create the directory? (Y/n)\n"
	},

	[ZH_CN] =
	{
		.choose_install_path = "选择安装目录：\n\n[1]/usr/local\n[2]/usr/bin\n[3]/bin\n[4]~/.local/bin\n[5]自定义路径\n\n",
		.input_install_path = "输入安装路经：\n",
		.want_create_link = "是否在安装目录创建工具的软连结？(y/N)\n",
		.check = "检测到PATH未包含安装目录，是否添加安装目录至PATH？(Y/n)\n",

		.error_path = "请重新输入安装路径\n",
		.no_folder_found = "未找到安装目录，是否创建目录？(Y/n)\n"
	},

	[ZH_HANT] =
	{
		.choose_install_path = "選擇安裝目錄：\n\n[1]/usr/local\n[2]/usr/bin\n[3]/bin\n[4]~/.local/bin\n[5]自定義路徑\n\n",
		.input_install_path = "輸入安裝路經：\n",
		.want_create_link = "是否在安裝目錄創建工具的軟連結？(y/N)\n",
		.check = "檢測到PATH未包含安裝目錄，是否添加安裝目錄至PATH？(Y/n)\n",

		.error_path = "請重新輸入安裝路徑\n",
		.no_folder_found = "未找到安裝目錄，是否創建目錄？(Y/n)\n"
	}
};

int installer_main(install_var var)
{
	int return_v = 0;

	return return_v;
}
