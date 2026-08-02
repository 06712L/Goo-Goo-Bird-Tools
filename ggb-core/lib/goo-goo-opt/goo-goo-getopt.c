#include <string.h>
#include <stdbool.h>
#include "lib/goo-goo-getopt.h"

enum
{
	DOES_NOT_MATCH = 100,
	CONFROM_TO = 105,
	HYPHEN = 110
};

/**
 * @brief     Check for long options and enable the corresponding flags
 *
 * @param[in]  opt       Options to check
 * @param      opt_list  The option list
 *
 * @return  DOES_NOT_MATCH      Does not match
 * @return  CONFROM_TO      conform to
 * @return  HYPHEN		Double hyphen
 */
static int check_long_opt(const char *opt, OPT_LIST *opt_list[])
{
	size_t len = strlen(opt);
	if(len < 3)
	{
		return HYPHEN;
	}

	for(size_t i = 0; opt_list[i]->long_name != NULL; i++)
	{
		bool flag = true;
		for(size_t j = 2; j < len; j++)
		{
			if(opt[j] != opt_list[i]->long_name[j])
			{
				if(opt_list[i + 1]->long_name == NULL)
				{
					return DOES_NOT_MATCH;
				}
				else
				{
					flag = false;
					break;
				}
			}
		}
		if(flag)
		{
			opt_list[i]->flag = true;
			return CONFROM_TO;
		}
	}
	return DOES_NOT_MATCH;
}

/**
 * @brief      Check for short options and enable the corresponding flags
 *
 * @param[in]  opt       Options to check
 * @param      opt_list  List  of options
 *
 * @return  i      Location of unmatched options
 * @return  CONFROM_TO      conform to
 * @return  HYPHEN		Single hyphen
 */
static int check_short_opt(const char *opt, OPT_LIST *opt_list[])
{
	size_t len = strlen(opt);
	if (len < 2)
	{
		return HYPHEN;
	}
	for(size_t i = 1; i < len; i++)
	{
		for(int j = 0; opt_list[j]->short_name != '\0'; j++)
		{
			if(opt[i] == opt_list[j]->short_name)
			{
				opt_list[j]->flag = true;
				break;
			}
			else
			{
				return i;
			}
		}
	}
	return CONFROM_TO;
}

/**
 * @brief      Parse the command line
 *
 * @param[in]  argc      The count of arguments
 * @param      argv      The arguments array
 * @param      opt_list  List  of options
 *
 * @return  i  Return a parsing error for the long option
 * @return  opt  Return a short option that caused a parsing error
 * @return  NO_OPT_FOUND  No options to parse
 * @return  0  Successfully parsed
 */
int goo_goo_getopt(const int argc, const char *argv[], OPT_LIST opt_list[])
{
	int count = 0;
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			// long opt
			if (argv[i][1] == '-')
			{
				int opt = check_long_opt(argv[i], &opt_list);
				if(opt == DOES_NOT_MATCH)
				{
					return i;
				}
				count += 1;
			}

			// short opt
			else
			{
				int opt = check_short_opt(argv[i], &opt_list);
				if (opt != CONFROM_TO && opt != HYPHEN)
				{
					return opt;
				}
				count += 1;
			}
		}
	}
	if(!count)
	{
		return NO_OPT_FOUND;
	}
	return 0;
}
