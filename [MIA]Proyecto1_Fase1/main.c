#include <stdio.h>
#include <stdlib.h>
#include <Console.h>

int main()
{
    srand (time(NULL));
    FILE * disco;
    disco = fopen("/home/moramaz/Escritorio/mounts.dsk", "wb+");
    fclose(disco);
    menu();
    remove("/home/moramaz/Escritorio/mounts.dsk");
    printf("Ahi te ves papu!\n");
    return 0;
}
