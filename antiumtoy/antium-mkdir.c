#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Uso: mkdir directorio...\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (mkdir(argv[i], 0755) != 0) {
            perror("antium-mkdir");
            return 1;
        }
    }

    return 0;
}
