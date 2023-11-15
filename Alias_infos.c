#include "shell.h"

int print_alias_data(data_of_program *data, char *requested_alias) {
    int i, j, alias_length;
    char output_buffer[250] = {'\0'};

    if (data->aliases) {
        alias_length = str_length(requested_alias);
        for (i = 0; data->aliases[i]; i++) {
            if (!requested_alias || (str_compare(data->aliases[i], requested_alias, alias_length)
                && data->aliases[i][alias_length] == '=')) {
                for (j = 0; data->aliases[i][j]; j++) {
                    output_buffer[j] = data->aliases[i][j];
                    if (data->aliases[i][j] == '=')
                        break;
                }
                output_buffer[j + 1] = '\0';
                buffer_add(output_buffer, "'");
                buffer_add(output_buffer, data->aliases[i] + j + 1);
                buffer_add(output_buffer, "'\n");
                _print(output_buffer);
            }
        }
    }

    return 0;
}

char *get_alias_value(data_of_program *data, char *alias_name) {
    int i, alias_length;

    if (alias_name == NULL || data->aliases == NULL)
        return NULL;

    alias_length = str_length(alias_name);

    for (i = 0; data->aliases[i]; i++) {
        if (str_compare(alias_name, data->aliases[i], alias_length) &&
            data->aliases[i][alias_length] == '=') {
            return (data->aliases[i] + alias_length + 1);
        }
    }
    return NULL;
}

int set_alias_value(char *alias_str, data_of_program *data) {
    int i, j;
    char buffer[250] = {'\0'}, *temp = NULL;

    if (alias_str == NULL || data->aliases == NULL)
        return 1;

    for (i = 0; alias_str[i]; i++) {
        if (alias_str[i] != '=') {
            buffer[i] = alias_str[i];
        } else {
            temp = get_alias_value(data, alias_str + i + 1);
            break;
        }
    }

    for (j = 0; data->aliases[j]; j++) {
        if (str_compare(buffer, data->aliases[j], i) &&
            data->aliases[j][i] == '=') {
            free(data->aliases[j]);
            break;
        }
    }

    if (temp) {
        buffer_add(buffer, "=");
        buffer_add(buffer, temp);
        data->aliases[j] = str_duplicate(buffer);
    } else {
        data->aliases[j] = str_duplicate(alias_str);
    }
    return 0;
}
