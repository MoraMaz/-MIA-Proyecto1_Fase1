#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Reports.h>
#include <time.h>
#define true 1
#define false 0

typedef int boolean;
typedef struct p part;
typedef struct m mbr;
typedef struct ou moun;

int limpiar_part(part * actual);
int limpiar_mbr(mbr * actual);
int imprimir_mbr(mbr actual);
int limpiar_mount(moun * actual);

struct p{
    int part_start, part_size;
    char part_status, part_type, part_fit, part_name[16];
};

struct m{
    char disk_fit;
    time_t mbr_fecha_creacion;
    int mbr_tamano, mbr_disk_signature;
    part mbr_partition_1, mbr_partition_2, mbr_partition_3, mbr_partition_4;
};

struct ou{
    char id[5], nombre[16], path[200];
};

#endif // STRUCTS_H
