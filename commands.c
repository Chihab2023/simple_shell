#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_PROMPT_LENGTH 20

void run_shell(void) {
    char command[MAX_COMMAND_LENGTH];
    char prompt[MAX_PROMPT_LENGTH] = "#cisfun$ ";
    pid_t pid;

    while (1) {
        printf("%s", prompt);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            if (feof(stdin)) {
                printf("\n");
                break;
            }
        }

        command[strcspn(command, "\n")] = '\0';

        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            if (execlp(command, command, (char *)NULL) == -1) {
                fprintf(stderr, "%s: command not found\n", command);
                exit(EXIT_FAILURE);
            }
        } else {
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            if (WIFSIGNALED(status)) {
                printf("\nTerminated by signal %d\n", WTERMSIG(status));
            } else if (WIFEXITED(status)) {
                printf("Child exited with status %d\n", WEXITSTATUS(status));
            }
        }
    }
}

int main(void) {
    run_shell();
    return 0;
}

