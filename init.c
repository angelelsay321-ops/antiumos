#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mount.h>

int main(void)
{
    mkdir("/proc", 0555);
    mkdir("/sys", 0555);
    mkdir("/dev", 0755);
    mkdir("/run", 0755);
    mkdir("/tmp", 0777);

    mount("proc", "/proc", "proc", 0, "");
    mount("sysfs", "/sys", "sysfs", 0, "");
    mount("devtmpfs", "/dev", "devtmpfs", 0, "");

    chdir("/");

    printf("\n");
    printf("=========================\n");
    printf("      AntiumOS\n");
    printf("=========================\n\n");

    printf("AntiumOS: entorno del sistema preparado.\n");
    printf("Iniciando AntiumToy...\n\n");

    while (1)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("AntiumOS: fork");
            return 1;
        }

        if (pid == 0)
        {
            execl("/bin/antium-sh",
                  "antium-sh",
                  (char *)NULL);

            perror("AntiumOS: no se pudo iniciar AntiumToy");
            _exit(127);
        }

        int estado;
        waitpid(pid, &estado, 0);

        printf("\nAntiumOS: AntiumToy terminó. Reiniciando shell...\n\n");
    }

    return 0;
}
