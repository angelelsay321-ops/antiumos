#include <stdio.h>

int main(void)
{
    printf("\033[2J\033[H");
    fflush(stdout);

    return 0;
}
