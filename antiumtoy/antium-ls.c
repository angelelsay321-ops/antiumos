#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    const char *ruta = "/";

    if (argc > 1)
        ruta = argv[1];

    DIR *dir = opendir(ruta);

    if (dir == NULL) {
        perror("antium-ls");
        return 1;
    }

    struct dirent *entrada;

    while ((entrada = readdir(dir)) != NULL) {
        if (entrada->d_name[0] == '.')
            continue;

        printf("%s\n", entrada->d_name);
    }

    closedir(dir);
    return 0;
}
