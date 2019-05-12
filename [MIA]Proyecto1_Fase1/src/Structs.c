#include <Structs.h>

int limpiar_part(part *actual){
    actual->part_status = '0';
    actual->part_type = '\0';
    actual->part_fit = '\0';
    actual->part_start = 0;
    actual->part_size = 0;
    int index;
    for(index = 0; index < 16; index++) actual->part_name[index] = '\0';
    return 0;
}

int limpiar_mbr(mbr *actual){
    actual->disk_fit = '\0';
    actual->mbr_tamano = 0;
    actual->mbr_fecha_creacion = time(NULL);
    actual->mbr_disk_signature = rand();
    limpiar_part(&(actual->mbr_partition_1));
    limpiar_part(&(actual->mbr_partition_2));
    limpiar_part(&(actual->mbr_partition_3));
    limpiar_part(&(actual->mbr_partition_4));
    return 0;
}

int limpiar_mount(moun *actual){
    int index;
    for(index = 0; index < 5; index++) actual->id[index] = '\0';
    for(index = 0; index < 16; index++) actual->nombre[index] = '\0';
    for(index = 0; index < 300; index++) actual->path[index] = '\0';
    return 0;
}
