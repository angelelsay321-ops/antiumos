#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main(void)
{
    char ruta[PATH_MAX];

    if (getcwd(ruta, sizeof(ruta)) == NULL) {
        perror("antium-pwd");
        return 1;
    }

    printf("%s\n", ruta);

    return 0;
}
