#include <stdio.h>
#include <stdlib.h>
#include <Console.h>

int main()
{
    srand (time(NULL));
    remove("/home/moramaz/Escritorio/mounts.dsk");
    menu();
    printf("Ahi te ves papu!\n");
    return 0;
}
