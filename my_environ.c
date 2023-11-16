#include "shell.h"
/**
 * _myenvir - prints the current environment
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int _myenvir(info_type *info)
{
	prt_list_str(info->env);
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

/**
 * _mysetenv - Initialize a new environment variable
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int _mysetenv(info_type *info)
{
	if (info->argc != 3)
	{
		_eput_str("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenviro(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _my_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int _my_unsetenv(info_type *info)
{
	int i;

	if (info->argc == 1)
	{
		_eput_str("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * p_env_list - populates env linked list
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int p_env_list(info_type *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
