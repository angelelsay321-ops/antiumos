#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Uso: touch archivo...\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *archivo = fopen(argv[i], "a");

        if (archivo == NULL) {
            perror("antium-touch");
            return 1;
        }

        fclose(archivo);
    }

    return 0;
}
