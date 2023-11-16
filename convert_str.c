#include "shell.h"
/**
 * _errors_sti - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _errors_sti(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++; 
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
void print_error(info_type *info, char *estr)
{
	_eput_str(info->fname);
	_eput_str(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_eput_str(": ");
	_eput_str(info->argv[0]);
	_eput_str(": ");
	_eput_str(estr);
}

/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 * Return: number of characters
 */
int print_decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, c = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		c++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 100000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			c++;
		}
		current %= i;
	}
	__putchar('0' + current);
	c++;

	return (c);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *p;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';

	do	{
		*--p = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--p = sign;
	return (p);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
