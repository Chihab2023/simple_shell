#include "shell.h"
/**
 * main - entry point
 * @ac: arg count
 * @argv: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **argv)
{
	info_type info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eput_str(argv[0]);
				_eput_str(": 0: Can't open ");
				_eput_str(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	p_env_list(info);
	read_hist(info);
	shell_loop(info, argv);
	return (EXIT_SUCCESS);
}
