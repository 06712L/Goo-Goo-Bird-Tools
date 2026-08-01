#ifndef GOO_GOO_GETOPT_H
#define GOO_GOO_GETOPT_H

// vvvv 	define

enum
{
	NO_OPT_FOUND = 100
};

typedef struct goo_goo_options_list
{
	const char short_name;
	const char *long_name;
	_Bool flag;
}OPT_LIST;

// vvvv 	function

int goo_goo_getopt(const int argc, const char *argv[], OPT_LIST options[]);

#endif
