#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Uso: mv origen destino\n");
        return 1;
    }

    if (rename(argv[1], argv[2]) != 0) {
        perror("antium-mv");
        return 1;
    }

    return 0;
}
