#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_ARGS 32
#define MAX_INPUT 256

int main(void)
{
    char entrada[MAX_INPUT];

    printf("\n");
    printf("=========================\n");
    printf("      AntiumToy\n");
    printf("=========================\n\n");

    while (1)
    {
        printf("AntiumOS> ");
        fflush(stdout);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL)
            break;

        entrada[strcspn(entrada, "\n")] = '\0';

        if (entrada[0] == '\0')
            continue;

        char *argv[MAX_ARGS];
        int argc = 0;
        char *salida = NULL;

        char *token = strtok(entrada, " \t");

        while (token != NULL && argc < MAX_ARGS - 1)
        {
            if (strcmp(token, ">") == 0)
            {
                token = strtok(NULL, " \t");

                if (token == NULL)
                {
                    fprintf(stderr,
                            "AntiumToy: falta archivo despues de >\n");
                    argc = 0;
                    break;
                }

                salida = token;
            }
            else
            {
                argv[argc++] = token;
            }

            token = strtok(NULL, " \t");
        }

        argv[argc] = NULL;

        if (argc == 0)
            continue;

        /* Comandos internos */

        if (strcmp(argv[0], "exit") == 0)
        {
            printf("Saliendo de AntiumToy...\n");
            break;
        }

        if (strcmp(argv[0], "cd") == 0)
        {
            const char *ruta = argc > 1 ? argv[1] : "/";

            if (chdir(ruta) != 0)
                perror("AntiumToy: cd");

            continue;
        }

        if (strcmp(argv[0], "help") == 0)
        {
            printf("Comandos disponibles:\n");
            printf("  help       Muestra esta ayuda\n");
            printf("  exit       Sale de AntiumToy\n");
            printf("  cd DIR     Cambia de directorio\n");
            printf("\n");
            printf("Los demas comandos son proporcionados por AntiumToy.\n");
            continue;
        }

        char ruta[256];

        /*
         * Primero buscamos un ejecutable normal:
         *
         * /bin/comando
         *
         * Esto permitirá posteriormente usar /bin/blip.
         */
        snprintf(ruta, sizeof(ruta), "/bin/%s", argv[0]);

        /*
         * Si no existe, usamos el nombre AntiumToy:
         *
         * /bin/antium-comando
         */
        if (access(ruta, X_OK) != 0)
        {
            snprintf(ruta,
                     sizeof(ruta),
                     "/bin/antium-%s",
                     argv[0]);
        }

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("AntiumToy: fork");
            continue;
        }

        if (pid == 0)
        {
            if (salida != NULL)
            {
                int fd = open(
                    salida,
                    O_WRONLY | O_CREAT | O_TRUNC,
                    0644
                );

                if (fd < 0)
                {
                    perror("AntiumToy: redireccion");
                    _exit(1);
                }

                if (dup2(fd, STDOUT_FILENO) < 0)
                {
                    perror("AntiumToy: dup2");
                    close(fd);
                    _exit(1);
                }

                close(fd);
            }

            execv(ruta, argv);

            fprintf(
                stderr,
                "AntiumToy: comando no encontrado: %s\n",
                argv[0]
            );

            _exit(127);
        }

        int estado;
        waitpid(pid, &estado, 0);
    }

    return 0;
}
