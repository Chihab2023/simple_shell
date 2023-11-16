#include "shell.h"

/**
 * _myhist - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int _myhist(info_type *info)
{
	print_list(info->history);
	return (0);
}