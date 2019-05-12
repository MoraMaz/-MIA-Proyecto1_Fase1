#ifndef CONSOLE_H
#define CONSOLE_H
#include <Structs.h>

int menu();
int comando(char cadena1[300]);
int mkdisk(char path[200], char fit, int tamano);
int rmdisk(char path[200]);
int fdisk(int size, char unit, char path[200], char type, char fit, char del, char name[16], int add);
int mount(char path[300], char name[20]);
int unmount(char id[5]);
int rep(char name[16], char path[200], char id[5]);

#endif // CONSOLE_H
