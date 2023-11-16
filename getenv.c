include "shell.h"

/**
 * get_env - returns the string array copy of our environ
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
char **get_env(info_type *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}