#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Uso: rm archivo...\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (unlink(argv[i]) != 0) {
            perror("antium-rm");
            return 1;
        }
    }

    return 0;
}
