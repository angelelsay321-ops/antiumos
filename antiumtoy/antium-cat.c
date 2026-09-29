#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Uso: cat archivo...\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *archivo = fopen(argv[i], "r");

        if (archivo == NULL) {
            perror("antium-cat");
            return 1;
        }

        char buffer[4096];
        size_t bytes;

        while ((bytes = fread(buffer, 1, sizeof(buffer), archivo)) > 0) {
            if (fwrite(buffer, 1, bytes, stdout) != bytes) {
                perror("antium-cat");
                fclose(archivo);
                return 1;
            }
        }

        fclose(archivo);
    }

    return 0;
}
