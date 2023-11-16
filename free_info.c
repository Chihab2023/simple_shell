#include "shell.h"
/**
 * free_info - frees info_type struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_type *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		buf_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_puts_char(BUF_FLUSH);
	}
}