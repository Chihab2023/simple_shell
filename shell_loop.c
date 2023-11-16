#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_type *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
<<<<<<< HEAD
			builtin_ret = find_builtin22(info);
=======
			builtin_ret = find_built(info);
>>>>>>> 963ededd235ebe94b5f4c12bd1b6cfbd89932bca
			if (builtin_ret == -1)
<<<<<<< HEAD
				find_commmd(info);
=======
				find_commd(info);
>>>>>>> 963ededd235ebe94b5f4c12bd1b6cfbd89932bca
		}
		else if (interactive(info))
			_puts_char('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
<<<<<<< HEAD
 * find_builtin22 - finds a builtin command
=======
 * find_built - finds a builtin command
>>>>>>> 963ededd235ebe94b5f4c12bd1b6cfbd89932bca
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
<<<<<<< HEAD
int find_builtin22(info_type *info)
=======
int find_built(info_type *info)
>>>>>>> 963ededd235ebe94b5f4c12bd1b6cfbd89932bca
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhist},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mydir},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_str_cmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}