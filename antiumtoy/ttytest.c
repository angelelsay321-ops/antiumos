#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char c;

    printf("Escribe algo y pulsa Enter:\n");
    fflush(stdout);

    while (read(STDIN_FILENO, &c, 1) == 1)
    {
        printf("CARACTER: %d '%c'\n", (unsigned char)c, c);

        if (c == '\n')
            printf("--- ENTER DETECTADO ---\n");

        fflush(stdout);
    }

    return 0;
}
