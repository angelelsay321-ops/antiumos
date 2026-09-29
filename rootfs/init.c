#include <stdio.h>
#include <unistd.h>

int main() {

    printf("\n");
    printf("=========================\n");
    printf("      AntiumOS\n");
    printf("=========================\n");
    printf("\n");

    int contador = 0;

    while (1) {
        printf("Sistema activo: %d\n", contador++);
        sleep(1);
    }

    return 0;
}
