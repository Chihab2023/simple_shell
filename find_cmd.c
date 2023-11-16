#include "shell.h"
/**
<<<<<<< HEAD
 * find_commmd - finds a command in PATH
=======
 * find_commd - finds a command in PATH
>>>>>>> 963ededd235ebe94b5f4c12bd1b6cfbd89932bca
 * @info: the parameter & return info struct
 *
 * Return: void
 */
<<<<<<< HEAD
void find_commmd(info_type *info)
=======
void find_commd(info_type *info)
>>>>>>> 963ededd235ebe94b5f4c12bd1b6cfbd89932bca
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
<<<<<<< HEAD
		fork_commmand(info);
=======
		fork_commd(info);
>>>>>>> 963ededd235ebe94b5f4c12bd1b6cfbd89932bca
	}
	else
	{
		if ((interactive(info) || _get_env(info, "PATH=")
<<<<<<< HEAD
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_commmand(info);
=======
			|| info->argv[0][0] == '/') && is_commd(info, info->argv[0]))
			fork_commd(info);
>>>>>>> 963ededd235ebe94b5f4c12bd1b6cfbd89932bca
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
#include "shell.h"
/**
<<<<<<< HEAD
 * fork_commmand - forks a an exec thread to run cmd
=======
 * fork_commd - forks a an exec thread to run cmd
>>>>>>> 963ededd235ebe94b5f4c12bd1b6cfbd89932bca
 * @info: the parameter & return info struct
 *
 * Return: void
 */
<<<<<<< HEAD
void fork_commmand(info_type *info)
=======
void fork_commd(info_type *info)
>>>>>>> 963ededd235ebe94b5f4c12bd1b6cfbd89932bca
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_env(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}