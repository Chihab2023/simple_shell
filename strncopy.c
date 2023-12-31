#include "shell.h"
/**
 **_strn_copy - copies a string
 *@dest: the destination string to be copied to
 *@str_src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strn_copy(char *dest, char *str_src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (str_src[i] != '\0' && i < n - 1)
	{
		dest[i] = str_src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@str_src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *str_src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (str_src[j] != '\0' && j < n)
	{
		dest[i] = str_src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_str_chr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_str_chr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
