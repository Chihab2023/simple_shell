#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int _myenv(info_type *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _get_env - gets the value of an environ variable
 * @info: Structure containing potential arguments
 * @name: env var name
 *
 * Return: the value
 */
char *_get_env(info_type *info, const char *name)
{
	list_t *node = info->env;
	char *x;

	while (node)
	{
		x = starts_with(node->str, name);
		if (x && *x)
			return (x);
		node = node->next;
	}
	return (NULL);
}