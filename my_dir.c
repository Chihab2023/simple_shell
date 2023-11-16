#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments
 *  Return: exits with a given exit status
 */
int _myexit(info_type *info)
{
	int exit_check;

	if (info->argv[1])  
	{
		exit_check = _err_sti(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _err_sti(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mydir - changes the current directory of the process
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int _mydir(info_type *info)
{
	char *s, *dir, buffer[1024];
	int chdir_rt;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _get_env(info, "HOME=");
		if (!dir)
			chdir_rt = 
				chdir((dir = _get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_rt = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_get_env(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_rt = 
			chdir((dir = _get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_rt = chdir(info->argv[1]);
	if (chdir_rt == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _get_env(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int _myhelp(info_type *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
