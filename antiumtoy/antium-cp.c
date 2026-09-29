#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Uso: cp origen destino\n");
        return 1;
    }

    FILE *origen = fopen(argv[1], "rb");
    if (origen == NULL) {
        perror("antium-cp");
        return 1;
    }

    FILE *destino = fopen(argv[2], "wb");
    if (destino == NULL) {
        perror("antium-cp");
        fclose(origen);
        return 1;
    }

    char buffer[8192];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), origen)) > 0) {
        if (fwrite(buffer, 1, bytes, destino) != bytes) {
            perror("antium-cp");
            fclose(origen);
            fclose(destino);
            return 1;
        }
    }

    fclose(origen);
    fclose(destino);

    return 0;
}
