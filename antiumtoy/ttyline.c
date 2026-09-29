#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char buffer[256];
    int pos = 0;
    char c;

    printf("Escribe una linea y pulsa Enter:\n");
    fflush(stdout);

    while (read(STDIN_FILENO, &c, 1) == 1)
    {
        if (c == '\n')
        {
            buffer[pos] = '\0';

            printf("\nLINEA RECIBIDA: [%s]\n", buffer);
            printf("LONGITUD: %d\n", pos);

            pos = 0;

            printf("\nEscribe otra linea:\n");
            fflush(stdout);
        }
        else if (c == 127)
        {
            if (pos > 0)
            {
                pos--;
                printf("\b \b");
                fflush(stdout);
            }
        }
        else if (pos < 255)
        {
            buffer[pos] = c;
            pos++;

            printf("%c", c);
            fflush(stdout);
        }
    }

    return 0;
}
