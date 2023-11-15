#include "shell.h"

int input_buffer(info_t *info, char **buffer, size_t *length)
{
    ssize_t bytes_read = 0;
    size_t new_length = 0;

    if (!*length) {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, handle_sigint);
#if USE_GETLINE
        bytes_read = getline(buffer, &new_length, stdin);
#else
        bytes_read = custom_getline(info, buffer, &new_length);
#endif
        if (bytes_read > 0) {
            if ((*buffer)[bytes_read - 1] == '\n') {
                (*buffer)[bytes_read - 1] = '\0';
                bytes_read--;
            }
            info->linecount_flag = 1;
            remove_comments(*buffer);
            build_history(info, *buffer, info->histcount++);
            if (*buffer && _strchr(*buffer, ';')) {
                *length = bytes_read;
                info->cmd_buffer = buffer;
            }
        }
    }
    return bytes_read;
}

ssize_t get_input(info_t *info)
{
    static char *buffer;
    static size_t i, j, length;
    ssize_t bytes_read = 0;
    char **buffer_p = &(info->args), *ptr;

    _putchar(BUF_FLUSH);
    bytes_read = input_buffer(info, &buffer, &length);
    if (bytes_read == -1) {
        return -1;
    }

    if (length) {
        j = i;
        ptr = buffer + i;

        check_chain(info, buffer, &j, i, length);
        while (j < length) {
            if (is_chain(info, buffer, &j))
                break;
            j++;
        }

        i = j + 1;
        if (i >= length) {
            i = length = 0;
            info->cmd_buffer_type = CMD_NORM;
        }

        *buffer_p = ptr;
        return _strlen(ptr);
    }

    *buffer_p = buffer;
    return bytes_read;
}

ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
    ssize_t bytes_read = 0;

    if (*i)
        return 0;
    bytes_read = read(info->readfd, buf, READ_BUF_SIZE);
    if (bytes_read >= 0)
        *i = bytes_read;
    return bytes_read;
}

int custom_getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    r = read_buffer(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return -1;

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, s, s ? s + k : k + 1);
    if (!new_p)
        return (p ? free(p), -1 : -1);

    if (s)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return s;
}

void handle_sigint(_attribute_((unused))int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
