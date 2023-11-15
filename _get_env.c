#include "shell.h"

char **retrieve_environment(info_t *info)
{
    if (!info->environ || info->env_change)
    {
        info->environ = list_to_array(info->env);
        info->env_change = 0;
    }

    return (info->environ);
}

int delete_environment_variable(info_t *info, char *variable)
{
    list_t *data = info->env;
    size_t ind = 0;
    char *ppt;

    if (!data || !variable)
        return (0);

    while (data)
    {
        ppt = starts_with(data->str, variable);
        if (ppt && *ppt == '=')
        {
            info->env_change = delete_node_at_index(&(info->env), ind);
            ind = 0;
            data = info->env;
            continue;
        }
        data = data->next;
        ind++;
    }
    return (info->env_change);
}

int set_environment_variable(info_t *info, char *variable, char *value)
{
    char *buffer = NULL;
    list_t *data;
    char *ppt;

    if (!variable || !value)
        return (0);

    buffer = malloc(_strlen(variable) + _strlen(value) + 2);
    if (!buffer)
        return (1);
    _strcpy(buffer, variable);
    _strcat(buffer, "=");
    _strcat(buffer, value);
    data = info->env;
    while (data)
    {
        ppt = starts_with(data->str, variable);
        if (ppt && *ppt == '=')
        {
            free(data->str);
            data->str = buffer;
            info->env_change = 1;
            return (0);
        }
        data = data->next;
    }
    add_node_end(&(info->env), buffer, 0);
    free(buffer);
    info->env_change = 1;
    return (0);
}
