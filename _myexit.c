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