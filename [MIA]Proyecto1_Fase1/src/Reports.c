#include <Reports.h>

int rep_disk(char id[5], char path[200]) {
    int posicion = 0, iterador = 0, contador = 0;
    double inicio = 0, porcentaje = 0, unidades[5];
    char xtncn[5], cadena[10000], aidi = '1', reporte[42] = "/home/moramaz/Escritorio/re.dot";
    for(posicion = 0; posicion < 10000; posicion++) cadena[posicion] = '\0';
    posicion = 0;
    FILE *mounts, *disco, *dot;
    moun lector, limpio;
    mbr mbr_;
    limpiar_mount(&lector);
    limpiar_mount(&limpio);
    mounts = fopen("/home/moramaz/Escritorio/mounts.dsk", "rb+");
    if(mounts == NULL){
        printf("No se ha encontrado ninguna particion montada.\n");
        return -1;
    }
    fseek(mounts, 0, SEEK_SET);
    fread(&lector, sizeof(moun), 1, mounts);
    int count, condicion = 0;
    while(1){
        for(count = 0; count < 5; count++){
            if(lector.id[count] == id[count])
                condicion = 1;
            else{
                condicion = 0;
                break;
            }
        }
        if(condicion || lector.id[0] == '\0')
            break;
        limpiar_mount(&lector);
        fread(&lector, sizeof(moun), 1, mounts);
    }
    fclose(mounts);
    if(condicion){
        disco = fopen(lector.path, "rb+");
        if(disco == NULL){
            printf("No se ha encontrado el disco de la particion montada.\n");
            return -1;
        }
        fseek(disco, 0, SEEK_SET);
        fread(&mbr_, sizeof(mbr), 1, disco);
        strcpy(cadena, "digraph DISK{\n\trankdir = UD;\n\tgraph [ratio = fill];\n\tnode [shape = plaintext]\n\t");
        strcat(cadena, "NODO [label=<\n\t\t<TABLE ALIGN = \"LEFT\">\n\t\t\t<TR>\n");
        strcat(cadena, "\t\t\t\t<TD> ");
        strcat(cadena, "MBR");
        strcat(cadena, " \t\t\t\t</TD>\n");
        if(mbr_.mbr_partition_1.part_status == '1'){
            inicio = mbr_.mbr_partition_1.part_start;
            if(sizeof(mbr) + 1 != inicio){
                strcat(cadena, "\t\t\t\t<TD> ");
                strcat(cadena, "Libre <br></br><br></br>");
                posicion = 0;
                porcentaje = ((double) (mbr_.mbr_partition_1.part_start - sizeof(mbr)) / mbr_.mbr_tamano) * 100;
                while(porcentaje){
                    if(porcentaje > 10){
                        unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                        porcentaje = porcentaje / 10;
                    }else{
                        unidades[posicion] = porcentaje;
                        posicion++;
                        break;
                    }
                    posicion++;
                    inicio = 0;
                    for(iterador = 0; iterador < posicion; iterador++){
                        inicio = inicio * 10 + unidades[iterador];
                    }
                    if(inicio == porcentaje)
                        break;
                }
                for(iterador = 0; iterador < 10000; iterador++){
                    if(cadena[iterador] == '\0'){
                        contador = iterador;
                        break;
                    }
                }
                for(iterador = posicion - 1; iterador >= 0; iterador--){
                    cadena[contador++] = unidades[iterador] + '0';
                }
                strcat(cadena, "% del disco ");
                strcat(cadena, " \t\t\t\t</TD>\n");
                strcat(cadena, "\t\t\t\t<TD> ");
                strcat(cadena, mbr_.mbr_partition_1.part_name);
                if(mbr_.mbr_partition_1.part_type == 'P' || mbr_.mbr_partition_1.part_type == 'p')
                    strcat(cadena, "<br></br>PRIMARIA<br></br>");
                else if(mbr_.mbr_partition_1.part_type == 'E' || mbr_.mbr_partition_1.part_type == 'e')
                    strcat(cadena, "<br></br>EXTENDIDA<br></br>");
                else
                    strcat(cadena, "<br></br>LOGICA<br></br>");
                posicion = 0;
                porcentaje = ((double) mbr_.mbr_partition_1.part_size / mbr_.mbr_tamano) * 100;
                while(porcentaje){
                    if(porcentaje > 10){
                        unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                        porcentaje = porcentaje / 10;
                    }else{
                        unidades[posicion] = porcentaje;
                        posicion++;
                        break;
                    }
                    posicion++;
                    inicio = 0;
                    for(iterador = 0; iterador < posicion; iterador++){
                        inicio = inicio * 10 + unidades[iterador];
                    }
                    if(inicio == porcentaje)
                        break;
                }
                for(iterador = 0; iterador < 10000; iterador++){
                    if(cadena[iterador] == '\0'){
                        contador = iterador;
                        break;
                    }
                }
                for(iterador = posicion - 1; iterador >= 0; iterador--){
                    cadena[contador++] = unidades[iterador] + '0';
                }
                strcat(cadena, "% del disco ");
                strcat(cadena, " \t\t\t\t</TD>\n");
                if(mbr_.mbr_partition_2.part_status == '1'){
                    inicio = mbr_.mbr_partition_2.part_start;
                    if(mbr_.mbr_partition_1.part_start + mbr_.mbr_partition_1.part_size + 1 != inicio){
                        strcat(cadena, "\t\t\t\t<TD> ");
                        strcat(cadena, "Libre <br></br><br></br>");
                        posicion = 0;
                        porcentaje = ((double) (mbr_.mbr_partition_2.part_start - (mbr_.mbr_partition_1.part_start + mbr_.mbr_partition_1.part_size + 1)) / mbr_.mbr_tamano) * 100;
                        while(porcentaje){
                            if(porcentaje > 10){
                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                porcentaje = porcentaje / 10;
                            }else{
                                unidades[posicion] = porcentaje;
                                posicion++;
                                break;
                            }
                            posicion++;
                            inicio = 0;
                            for(iterador = 0; iterador < posicion; iterador++){
                                inicio = inicio * 10 + unidades[iterador];
                            }
                            if(inicio == porcentaje)
                                break;
                        }
                        for(iterador = 0; iterador < 10000; iterador++){
                            if(cadena[iterador] == '\0'){
                                contador = iterador;
                                break;
                            }
                        }
                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                            cadena[contador++] = unidades[iterador] + '0';
                        }
                        strcat(cadena, "% del disco ");
                        strcat(cadena, " \t\t\t\t</TD>\n");
                        strcat(cadena, "\t\t\t\t<TD> ");
                        strcat(cadena, mbr_.mbr_partition_2.part_name);
                        if(mbr_.mbr_partition_2.part_type == 'P' || mbr_.mbr_partition_2.part_type == 'p')
                            strcat(cadena, "<br></br>PRIMARIA<br></br>");
                        else if(mbr_.mbr_partition_2.part_type == 'E' || mbr_.mbr_partition_2.part_type == 'e')
                            strcat(cadena, "<br></br>EXTENDIDA<br></br>");
                        else
                            strcat(cadena, "<br></br>LOGICA<br></br>");
                        posicion = 0;
                        porcentaje = ((double) mbr_.mbr_partition_2.part_size / mbr_.mbr_tamano) * 100;
                        while(porcentaje){
                            if(porcentaje > 10){
                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                porcentaje = porcentaje / 10;
                            }else{
                                unidades[posicion] = porcentaje;
                                posicion++;
                                break;
                            }
                            posicion++;
                            inicio = 0;
                            for(iterador = 0; iterador < posicion; iterador++){
                                inicio = inicio * 10 + unidades[iterador];
                            }
                            if(inicio == porcentaje)
                                break;
                        }
                        for(iterador = 0; iterador < 10000; iterador++){
                            if(cadena[iterador] == '\0'){
                                contador = iterador;
                                break;
                            }
                        }
                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                            cadena[contador++] = unidades[iterador] + '0';
                        }
                        strcat(cadena, "% del disco ");
                        strcat(cadena, " \t\t\t\t</TD>\n");
                        if(mbr_.mbr_partition_3.part_status == '1'){
                            inicio = mbr_.mbr_partition_3.part_start;
                            if(mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1 != inicio){
                                strcat(cadena, "\t\t\t\t<TD> ");
                                strcat(cadena, "Libre <br></br><br></br>");
                                posicion = 0;
                                porcentaje = ((double) (mbr_.mbr_partition_3.part_start - (mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                while(porcentaje){
                                    if(porcentaje > 10){
                                        unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                        porcentaje = porcentaje / 10;
                                    }else{
                                        unidades[posicion] = porcentaje;
                                        posicion++;
                                        break;
                                    }
                                    posicion++;
                                    inicio = 0;
                                    for(iterador = 0; iterador < posicion; iterador++){
                                        inicio = inicio * 10 + unidades[iterador];
                                    }
                                    if(inicio == porcentaje)
                                        break;
                                }
                                for(iterador = 0; iterador < 10000; iterador++){
                                    if(cadena[iterador] == '\0'){
                                        contador = iterador;
                                        break;
                                    }
                                }
                                for(iterador = posicion - 1; iterador >= 0; iterador--){
                                    cadena[contador++] = unidades[iterador] + '0';
                                }
                                strcat(cadena, "% del disco ");
                                strcat(cadena, " \t\t\t\t</TD>\n");
                                strcat(cadena, "\t\t\t\t<TD> ");
                                strcat(cadena, mbr_.mbr_partition_3.part_name);
                                if(mbr_.mbr_partition_3.part_type == 'P' || mbr_.mbr_partition_3.part_type == 'p')
                                    strcat(cadena, "<br></br>PRIMARIA<br></br>");
                                else if(mbr_.mbr_partition_3.part_type == 'E' || mbr_.mbr_partition_3.part_type == 'e')
                                    strcat(cadena, "<br></br>EXTENDIDA<br></br>");
                                else
                                    strcat(cadena, "<br></br>LOGICA<br></br>");
                                posicion = 0;
                                porcentaje = ((double) mbr_.mbr_partition_3.part_size / mbr_.mbr_tamano) * 100;
                                while(porcentaje){
                                    if(porcentaje > 10){
                                        unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                        porcentaje = porcentaje / 10;
                                    }else{
                                        unidades[posicion] = porcentaje;
                                        posicion++;
                                        break;
                                    }
                                    posicion++;
                                    inicio = 0;
                                    for(iterador = 0; iterador < posicion; iterador++){
                                        inicio = inicio * 10 + unidades[iterador];
                                    }
                                    if(inicio == porcentaje)
                                        break;
                                }
                                for(iterador = 0; iterador < 10000; iterador++){
                                    if(cadena[iterador] == '\0'){
                                        contador = iterador;
                                        break;
                                    }
                                }
                                for(iterador = posicion - 1; iterador >= 0; iterador--){
                                    cadena[contador++] = unidades[iterador] + '0';
                                }
                                strcat(cadena, "% del disco ");
                                strcat(cadena, " \t\t\t\t</TD>\n");
                                if(mbr_.mbr_partition_4.part_status == '1'){
                                    inicio = mbr_.mbr_partition_4.part_start;
                                    if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != inicio){
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, "Libre <br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) (mbr_.mbr_partition_4.part_start - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }else{
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }
                                }else if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != mbr_.mbr_tamano){
                                    strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                    posicion = 0;
                                    porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                    while(porcentaje){
                                        if(porcentaje > 10){
                                            unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                            porcentaje = porcentaje / 10;
                                        }else{
                                            unidades[posicion] = porcentaje;
                                            posicion++;
                                            break;
                                        }
                                        posicion++;
                                        inicio = 0;
                                        for(iterador = 0; iterador < posicion; iterador++){
                                            inicio = inicio * 10 + unidades[iterador];
                                        }
                                        if(inicio == porcentaje)
                                            break;
                                    }
                                    for(iterador = 0; iterador < 10000; iterador++){
                                        if(cadena[iterador] == '\0'){
                                            contador = iterador;
                                            break;
                                        }
                                    }
                                    for(iterador = posicion - 1; iterador >= 0; iterador--){
                                        cadena[contador++] = unidades[iterador] + '0';
                                    }
                                    strcat(cadena, "% del disco ");
                                    strcat(cadena, " \t\t\t\t</TD>\n");
                                }
                            }else{
                                strcat(cadena, "\t\t\t\t<TD> ");
                                strcat(cadena, mbr_.mbr_partition_3.part_name);
                                if(mbr_.mbr_partition_3.part_type == 'P' || mbr_.mbr_partition_3.part_type == 'p')
                                    strcat(cadena, "<br></br>PRIMARIA<br></br>");
                                else if(mbr_.mbr_partition_3.part_type == 'E' || mbr_.mbr_partition_3.part_type == 'e')
                                    strcat(cadena, "<br></br>EXTENDIDA<br></br>");
                                else
                                    strcat(cadena, "<br></br>LOGICA<br></br>");
                                posicion = 0;
                                porcentaje = ((double) mbr_.mbr_partition_3.part_size / mbr_.mbr_tamano) * 100;
                                while(porcentaje){
                                    if(porcentaje > 10){
                                        unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                        porcentaje = porcentaje / 10;
                                    }else{
                                        unidades[posicion] = porcentaje;
                                        posicion++;
                                        break;
                                    }
                                    posicion++;
                                    inicio = 0;
                                    for(iterador = 0; iterador < posicion; iterador++){
                                        inicio = inicio * 10 + unidades[iterador];
                                    }
                                    if(inicio == porcentaje)
                                        break;
                                }
                                for(iterador = 0; iterador < 10000; iterador++){
                                    if(cadena[iterador] == '\0'){
                                        contador = iterador;
                                        break;
                                    }
                                }
                                for(iterador = posicion - 1; iterador >= 0; iterador--){
                                    cadena[contador++] = unidades[iterador] + '0';
                                }
                                strcat(cadena, "% del disco ");
                                strcat(cadena, " \t\t\t\t</TD>\n");
                                if(mbr_.mbr_partition_4.part_status == '1'){
                                    inicio = mbr_.mbr_partition_4.part_start;
                                    if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != inicio){
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, "Libre <br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) (mbr_.mbr_partition_4.part_start - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }else{
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }
                                }else if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != mbr_.mbr_tamano){
                                    strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                    posicion = 0;
                                    porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                    while(porcentaje){
                                        if(porcentaje > 10){
                                            unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                            porcentaje = porcentaje / 10;
                                        }else{
                                            unidades[posicion] = porcentaje;
                                            posicion++;
                                            break;
                                        }
                                        posicion++;
                                        inicio = 0;
                                        for(iterador = 0; iterador < posicion; iterador++){
                                            inicio = inicio * 10 + unidades[iterador];
                                        }
                                        if(inicio == porcentaje)
                                            break;
                                    }
                                    for(iterador = 0; iterador < 10000; iterador++){
                                        if(cadena[iterador] == '\0'){
                                            contador = iterador;
                                            break;
                                        }
                                    }
                                    for(iterador = posicion - 1; iterador >= 0; iterador--){
                                        cadena[contador++] = unidades[iterador] + '0';
                                    }
                                    strcat(cadena, "% del disco ");
                                    strcat(cadena, " \t\t\t\t</TD>\n");
                                }
                            }
                        }else if(mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1 != mbr_.mbr_tamano){
                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                            posicion = 0;
                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1)) / mbr_.mbr_tamano) * 100;
                            while(porcentaje){
                                if(porcentaje > 10){
                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                    porcentaje = porcentaje / 10;
                                }else{
                                    unidades[posicion] = porcentaje;
                                    posicion++;
                                    break;
                                }
                                posicion++;
                                inicio = 0;
                                for(iterador = 0; iterador < posicion; iterador++){
                                    inicio = inicio * 10 + unidades[iterador];
                                }
                                if(inicio == porcentaje)
                                    break;
                            }
                            for(iterador = 0; iterador < 10000; iterador++){
                                if(cadena[iterador] == '\0'){
                                    contador = iterador;
                                    break;
                                }
                            }
                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                cadena[contador++] = unidades[iterador] + '0';
                            }
                            strcat(cadena, "% del disco ");
                            strcat(cadena, " \t\t\t\t</TD>\n");
                        }
                    }else{
                        strcat(cadena, "\t\t\t\t<TD> ");
                        strcat(cadena, mbr_.mbr_partition_2.part_name);
                        if(mbr_.mbr_partition_2.part_type == 'P' || mbr_.mbr_partition_2.part_type == 'p')
                            strcat(cadena, "<br></br>PRIMARIA<br></br>");
                        else if(mbr_.mbr_partition_2.part_type == 'E' || mbr_.mbr_partition_2.part_type == 'e')
                            strcat(cadena, "<br></br>EXTENDIDA<br></br>");
                        else
                            strcat(cadena, "<br></br>LOGICA<br></br>");
                        posicion = 0;
                        porcentaje = ((double) mbr_.mbr_partition_2.part_size / mbr_.mbr_tamano) * 100;
                        while(porcentaje){
                            if(porcentaje > 10){
                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                porcentaje = porcentaje / 10;
                            }else{
                                unidades[posicion] = porcentaje;
                                posicion++;
                                break;
                            }
                            posicion++;
                            inicio = 0;
                            for(iterador = 0; iterador < posicion; iterador++){
                                inicio = inicio * 10 + unidades[iterador];
                            }
                            if(inicio == porcentaje)
                                break;
                        }
                        for(iterador = 0; iterador < 10000; iterador++){
                            if(cadena[iterador] == '\0'){
                                contador = iterador;
                                break;
                            }
                        }
                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                            cadena[contador++] = unidades[iterador] + '0';
                        }
                        strcat(cadena, "% del disco ");
                        strcat(cadena, " \t\t\t\t</TD>\n");
                        if(mbr_.mbr_partition_3.part_status == '1'){
                            inicio = mbr_.mbr_partition_3.part_start;
                            if(mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1 != inicio){
                                strcat(cadena, "\t\t\t\t<TD> ");
                                strcat(cadena, "Libre <br></br><br></br>");
                                posicion = 0;
                                porcentaje = ((double) (mbr_.mbr_partition_3.part_start - (mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                while(porcentaje){
                                    if(porcentaje > 10){
                                        unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                        porcentaje = porcentaje / 10;
                                    }else{
                                        unidades[posicion] = porcentaje;
                                        posicion++;
                                        break;
                                    }
                                    posicion++;
                                    inicio = 0;
                                    for(iterador = 0; iterador < posicion; iterador++){
                                        inicio = inicio * 10 + unidades[iterador];
                                    }
                                    if(inicio == porcentaje)
                                        break;
                                }
                                for(iterador = 0; iterador < 10000; iterador++){
                                    if(cadena[iterador] == '\0'){
                                        contador = iterador;
                                        break;
                                    }
                                }
                                for(iterador = posicion - 1; iterador >= 0; iterador--){
                                    cadena[contador++] = unidades[iterador] + '0';
                                }
                                strcat(cadena, "% del disco ");
                                strcat(cadena, " \t\t\t\t</TD>\n");
                                strcat(cadena, "\t\t\t\t<TD> ");
                                strcat(cadena, mbr_.mbr_partition_3.part_name);
                                if(mbr_.mbr_partition_3.part_type == 'P' || mbr_.mbr_partition_3.part_type == 'p')
                                    strcat(cadena, "<br></br>PRIMARIA<br></br>");
                                else if(mbr_.mbr_partition_3.part_type == 'E' || mbr_.mbr_partition_3.part_type == 'e')
                                    strcat(cadena, "<br></br>EXTENDIDA<br></br>");
                                else
                                    strcat(cadena, "<br></br>LOGICA<br></br>");
                                posicion = 0;
                                porcentaje = ((double) mbr_.mbr_partition_3.part_size / mbr_.mbr_tamano) * 100;
                                while(porcentaje){
                                    if(porcentaje > 10){
                                        unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                        porcentaje = porcentaje / 10;
                                    }else{
                                        unidades[posicion] = porcentaje;
                                        posicion++;
                                        break;
                                    }
                                    posicion++;
                                    inicio = 0;
                                    for(iterador = 0; iterador < posicion; iterador++){
                                        inicio = inicio * 10 + unidades[iterador];
                                    }
                                    if(inicio == porcentaje)
                                        break;
                                }
                                for(iterador = 0; iterador < 10000; iterador++){
                                    if(cadena[iterador] == '\0'){
                                        contador = iterador;
                                        break;
                                    }
                                }
                                for(iterador = posicion - 1; iterador >= 0; iterador--){
                                    cadena[contador++] = unidades[iterador] + '0';
                                }
                                strcat(cadena, "% del disco ");
                                strcat(cadena, " \t\t\t\t</TD>\n");
                                if(mbr_.mbr_partition_4.part_status == '1'){
                                    inicio = mbr_.mbr_partition_4.part_start;
                                    if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != inicio){
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, "Libre <br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) (mbr_.mbr_partition_4.part_start - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }else{
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }
                                }else if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != mbr_.mbr_tamano){
                                    strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                    posicion = 0;
                                    porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                    while(porcentaje){
                                        if(porcentaje > 10){
                                            unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                            porcentaje = porcentaje / 10;
                                        }else{
                                            unidades[posicion] = porcentaje;
                                            posicion++;
                                            break;
                                        }
                                        posicion++;
                                        inicio = 0;
                                        for(iterador = 0; iterador < posicion; iterador++){
                                            inicio = inicio * 10 + unidades[iterador];
                                        }
                                        if(inicio == porcentaje)
                                            break;
                                    }
                                    for(iterador = 0; iterador < 10000; iterador++){
                                        if(cadena[iterador] == '\0'){
                                            contador = iterador;
                                            break;
                                        }
                                    }
                                    for(iterador = posicion - 1; iterador >= 0; iterador--){
                                        cadena[contador++] = unidades[iterador] + '0';
                                    }
                                    strcat(cadena, "% del disco ");
                                    strcat(cadena, " \t\t\t\t</TD>\n");
                                }
                            }else{
                                strcat(cadena, "\t\t\t\t<TD> ");
                                strcat(cadena, mbr_.mbr_partition_3.part_name);
                                if(mbr_.mbr_partition_3.part_type == 'P' || mbr_.mbr_partition_3.part_type == 'p')
                                    strcat(cadena, "<br></br>PRIMARIA<br></br>");
                                else if(mbr_.mbr_partition_3.part_type == 'E' || mbr_.mbr_partition_3.part_type == 'e')
                                    strcat(cadena, "<br></br>EXTENDIDA<br></br>");
                                else
                                    strcat(cadena, "<br></br>LOGICA<br></br>");
                                posicion = 0;
                                porcentaje = ((double) mbr_.mbr_partition_3.part_size / mbr_.mbr_tamano) * 100;
                                while(porcentaje){
                                    if(porcentaje > 10){
                                        unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                        porcentaje = porcentaje / 10;
                                    }else{
                                        unidades[posicion] = porcentaje;
                                        posicion++;
                                        break;
                                    }
                                    posicion++;
                                    inicio = 0;
                                    for(iterador = 0; iterador < posicion; iterador++){
                                        inicio = inicio * 10 + unidades[iterador];
                                    }
                                    if(inicio == porcentaje)
                                        break;
                                }
                                for(iterador = 0; iterador < 10000; iterador++){
                                    if(cadena[iterador] == '\0'){
                                        contador = iterador;
                                        break;
                                    }
                                }
                                for(iterador = posicion - 1; iterador >= 0; iterador--){
                                    cadena[contador++] = unidades[iterador] + '0';
                                }
                                strcat(cadena, "% del disco ");
                                strcat(cadena, " \t\t\t\t</TD>\n");
                                if(mbr_.mbr_partition_4.part_status == '1'){
                                    inicio = mbr_.mbr_partition_4.part_start;
                                    if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != inicio){
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, "Libre <br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) (mbr_.mbr_partition_4.part_start - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }else{
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }
                                }else if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != mbr_.mbr_tamano){
                                    strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                    posicion = 0;
                                    porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                    while(porcentaje){
                                        if(porcentaje > 10){
                                            unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                            porcentaje = porcentaje / 10;
                                        }else{
                                            unidades[posicion] = porcentaje;
                                            posicion++;
                                            break;
                                        }
                                        posicion++;
                                        inicio = 0;
                                        for(iterador = 0; iterador < posicion; iterador++){
                                            inicio = inicio * 10 + unidades[iterador];
                                        }
                                        if(inicio == porcentaje)
                                            break;
                                    }
                                    for(iterador = 0; iterador < 10000; iterador++){
                                        if(cadena[iterador] == '\0'){
                                            contador = iterador;
                                            break;
                                        }
                                    }
                                    for(iterador = posicion - 1; iterador >= 0; iterador--){
                                        cadena[contador++] = unidades[iterador] + '0';
                                    }
                                    strcat(cadena, "% del disco ");
                                    strcat(cadena, " \t\t\t\t</TD>\n");
                                }
                            }
                        }else if(mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1 != mbr_.mbr_tamano){
                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                            posicion = 0;
                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1)) / mbr_.mbr_tamano) * 100;
                            while(porcentaje){
                                if(porcentaje > 10){
                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                    porcentaje = porcentaje / 10;
                                }else{
                                    unidades[posicion] = porcentaje;
                                    posicion++;
                                    break;
                                }
                                posicion++;
                                inicio = 0;
                                for(iterador = 0; iterador < posicion; iterador++){
                                    inicio = inicio * 10 + unidades[iterador];
                                }
                                if(inicio == porcentaje)
                                    break;
                            }
                            for(iterador = 0; iterador < 10000; iterador++){
                                if(cadena[iterador] == '\0'){
                                    contador = iterador;
                                    break;
                                }
                            }
                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                cadena[contador++] = unidades[iterador] + '0';
                            }
                            strcat(cadena, "% del disco ");
                            strcat(cadena, " \t\t\t\t</TD>\n");
                        }
                    }
                }else if(mbr_.mbr_partition_1.part_start + mbr_.mbr_partition_1.part_size + 1 != mbr_.mbr_tamano){
                    strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                    posicion = 0;
                    porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_1.part_start + mbr_.mbr_partition_1.part_size + 1)) / mbr_.mbr_tamano) * 100;
                    while(porcentaje){
                        if(porcentaje > 10){
                            unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                            porcentaje = porcentaje / 10;
                        }else{
                            unidades[posicion] = porcentaje;
                            posicion++;
                            break;
                        }
                        posicion++;
                        inicio = 0;
                        for(iterador = 0; iterador < posicion; iterador++){
                            inicio = inicio * 10 + unidades[iterador];
                        }
                        if(inicio == porcentaje)
                            break;
                    }
                    for(iterador = 0; iterador < 10000; iterador++){
                        if(cadena[iterador] == '\0'){
                            contador = iterador;
                            break;
                        }
                    }
                    for(iterador = posicion - 1; iterador >= 0; iterador--){
                        cadena[contador++] = unidades[iterador] + '0';
                    }
                    strcat(cadena, "% del disco ");
                    strcat(cadena, " \t\t\t\t</TD>\n");
                }
            }else{
                strcat(cadena, "\t\t\t\t<TD> ");
                strcat(cadena, mbr_.mbr_partition_1.part_name);
                if(mbr_.mbr_partition_1.part_type == 'P' || mbr_.mbr_partition_1.part_type == 'p')
                    strcat(cadena, "<br></br>PRIMARIA<br></br>");
                else if(mbr_.mbr_partition_1.part_type == 'E' || mbr_.mbr_partition_1.part_type == 'e')
                    strcat(cadena, "<br></br>EXTENDIDA<br></br>");
                else
                    strcat(cadena, "<br></br>LOGICA<br></br>");
                posicion = 0;
                porcentaje = ((double) mbr_.mbr_partition_1.part_size / mbr_.mbr_tamano) * 100;
                while(porcentaje){
                    if(porcentaje > 10){
                        unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                        porcentaje = porcentaje / 10;
                    }else{
                        unidades[posicion] = porcentaje;
                        posicion++;
                        break;
                    }
                    posicion++;
                    inicio = 0;
                    for(iterador = 0; iterador < posicion; iterador++){
                        inicio = inicio * 10 + unidades[iterador];
                    }
                    if(inicio == porcentaje)
                        break;
                }
                for(iterador = 0; iterador < 10000; iterador++){
                    if(cadena[iterador] == '\0'){
                        contador = iterador;
                        break;
                    }
                }
                for(iterador = posicion - 1; iterador >= 0; iterador--){
                    cadena[contador++] = unidades[iterador] + '0';
                }
                strcat(cadena, "% del disco ");
                strcat(cadena, " \t\t\t\t</TD>\n");
                if(mbr_.mbr_partition_2.part_status == '1'){
                    inicio = mbr_.mbr_partition_2.part_start;
                    if(mbr_.mbr_partition_1.part_start + mbr_.mbr_partition_1.part_size + 1 != inicio){
                        strcat(cadena, "\t\t\t\t<TD> ");
                        strcat(cadena, "Libre <br></br><br></br>");
                        posicion = 0;
                        porcentaje = ((double) (mbr_.mbr_partition_2.part_start - (mbr_.mbr_partition_1.part_start + mbr_.mbr_partition_1.part_size + 1)) / mbr_.mbr_tamano) * 100;
                        while(porcentaje){
                            if(porcentaje > 10){
                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                porcentaje = porcentaje / 10;
                            }else{
                                unidades[posicion] = porcentaje;
                                posicion++;
                                break;
                            }
                            posicion++;
                            inicio = 0;
                            for(iterador = 0; iterador < posicion; iterador++){
                                inicio = inicio * 10 + unidades[iterador];
                            }
                            if(inicio == porcentaje)
                                break;
                        }
                        for(iterador = 0; iterador < 10000; iterador++){
                            if(cadena[iterador] == '\0'){
                                contador = iterador;
                                break;
                            }
                        }
                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                            cadena[contador++] = unidades[iterador] + '0';
                        }
                        strcat(cadena, "% del disco ");
                        strcat(cadena, " \t\t\t\t</TD>\n");
                        strcat(cadena, "\t\t\t\t<TD> ");
                        strcat(cadena, mbr_.mbr_partition_2.part_name);
                        if(mbr_.mbr_partition_2.part_type == 'P' || mbr_.mbr_partition_2.part_type == 'p')
                            strcat(cadena, "<br></br>PRIMARIA<br></br>");
                        else if(mbr_.mbr_partition_2.part_type == 'E' || mbr_.mbr_partition_2.part_type == 'e')
                            strcat(cadena, "<br></br>EXTENDIDA<br></br>");
                        else
                            strcat(cadena, "<br></br>LOGICA<br></br>");
                        posicion = 0;
                        porcentaje = ((double) mbr_.mbr_partition_2.part_size / mbr_.mbr_tamano) * 100;
                        while(porcentaje){
                            if(porcentaje > 10){
                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                porcentaje = porcentaje / 10;
                            }else{
                                unidades[posicion] = porcentaje;
                                posicion++;
                                break;
                            }
                            posicion++;
                            inicio = 0;
                            for(iterador = 0; iterador < posicion; iterador++){
                                inicio = inicio * 10 + unidades[iterador];
                            }
                            if(inicio == porcentaje)
                                break;
                        }
                        for(iterador = 0; iterador < 10000; iterador++){
                            if(cadena[iterador] == '\0'){
                                contador = iterador;
                                break;
                            }
                        }
                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                            cadena[contador++] = unidades[iterador] + '0';
                        }
                        strcat(cadena, "% del disco ");
                        strcat(cadena, " \t\t\t\t</TD>\n");
                        if(mbr_.mbr_partition_3.part_status == '1'){
                            inicio = mbr_.mbr_partition_3.part_start;
                            if(mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1 != inicio){
                                strcat(cadena, "\t\t\t\t<TD> ");
                                strcat(cadena, "Libre <br></br><br></br>");
                                posicion = 0;
                                porcentaje = ((double) (mbr_.mbr_partition_3.part_start - (mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                while(porcentaje){
                                    if(porcentaje > 10){
                                        unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                        porcentaje = porcentaje / 10;
                                    }else{
                                        unidades[posicion] = porcentaje;
                                        posicion++;
                                        break;
                                    }
                                    posicion++;
                                    inicio = 0;
                                    for(iterador = 0; iterador < posicion; iterador++){
                                        inicio = inicio * 10 + unidades[iterador];
                                    }
                                    if(inicio == porcentaje)
                                        break;
                                }
                                for(iterador = 0; iterador < 10000; iterador++){
                                    if(cadena[iterador] == '\0'){
                                        contador = iterador;
                                        break;
                                    }
                                }
                                for(iterador = posicion - 1; iterador >= 0; iterador--){
                                    cadena[contador++] = unidades[iterador] + '0';
                                }
                                strcat(cadena, "% del disco ");
                                strcat(cadena, " \t\t\t\t</TD>\n");
                                strcat(cadena, "\t\t\t\t<TD> ");
                                strcat(cadena, mbr_.mbr_partition_3.part_name);
                                if(mbr_.mbr_partition_3.part_type == 'P' || mbr_.mbr_partition_3.part_type == 'p')
                                    strcat(cadena, "<br></br>PRIMARIA<br></br>");
                                else if(mbr_.mbr_partition_3.part_type == 'E' || mbr_.mbr_partition_3.part_type == 'e')
                                    strcat(cadena, "<br></br>EXTENDIDA<br></br>");
                                else
                                    strcat(cadena, "<br></br>LOGICA<br></br>");
                                posicion = 0;
                                porcentaje = ((double) mbr_.mbr_partition_3.part_size / mbr_.mbr_tamano) * 100;
                                while(porcentaje){
                                    if(porcentaje > 10){
                                        unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                        porcentaje = porcentaje / 10;
                                    }else{
                                        unidades[posicion] = porcentaje;
                                        posicion++;
                                        break;
                                    }
                                    posicion++;
                                    inicio = 0;
                                    for(iterador = 0; iterador < posicion; iterador++){
                                        inicio = inicio * 10 + unidades[iterador];
                                    }
                                    if(inicio == porcentaje)
                                        break;
                                }
                                for(iterador = 0; iterador < 10000; iterador++){
                                    if(cadena[iterador] == '\0'){
                                        contador = iterador;
                                        break;
                                    }
                                }
                                for(iterador = posicion - 1; iterador >= 0; iterador--){
                                    cadena[contador++] = unidades[iterador] + '0';
                                }
                                strcat(cadena, "% del disco ");
                                strcat(cadena, " \t\t\t\t</TD>\n");
                                if(mbr_.mbr_partition_4.part_status == '1'){
                                    inicio = mbr_.mbr_partition_4.part_start;
                                    if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != inicio){
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, "Libre <br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) (mbr_.mbr_partition_4.part_start - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }else{
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }
                                }else if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != mbr_.mbr_tamano){
                                    strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                    posicion = 0;
                                    porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                    while(porcentaje){
                                        if(porcentaje > 10){
                                            unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                            porcentaje = porcentaje / 10;
                                        }else{
                                            unidades[posicion] = porcentaje;
                                            posicion++;
                                            break;
                                        }
                                        posicion++;
                                        inicio = 0;
                                        for(iterador = 0; iterador < posicion; iterador++){
                                            inicio = inicio * 10 + unidades[iterador];
                                        }
                                        if(inicio == porcentaje)
                                            break;
                                    }
                                    for(iterador = 0; iterador < 10000; iterador++){
                                        if(cadena[iterador] == '\0'){
                                            contador = iterador;
                                            break;
                                        }
                                    }
                                    for(iterador = posicion - 1; iterador >= 0; iterador--){
                                        cadena[contador++] = unidades[iterador] + '0';
                                    }
                                    strcat(cadena, "% del disco ");
                                    strcat(cadena, " \t\t\t\t</TD>\n");
                                }
                            }else{
                                strcat(cadena, "\t\t\t\t<TD> ");
                                strcat(cadena, mbr_.mbr_partition_3.part_name);
                                if(mbr_.mbr_partition_3.part_type == 'P' || mbr_.mbr_partition_3.part_type == 'p')
                                    strcat(cadena, "<br></br>PRIMARIA<br></br>");
                                else if(mbr_.mbr_partition_3.part_type == 'E' || mbr_.mbr_partition_3.part_type == 'e')
                                    strcat(cadena, "<br></br>EXTENDIDA<br></br>");
                                else
                                    strcat(cadena, "<br></br>LOGICA<br></br>");
                                posicion = 0;
                                porcentaje = ((double) mbr_.mbr_partition_3.part_size / mbr_.mbr_tamano) * 100;
                                while(porcentaje){
                                    if(porcentaje > 10){
                                        unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                        porcentaje = porcentaje / 10;
                                    }else{
                                        unidades[posicion] = porcentaje;
                                        posicion++;
                                        break;
                                    }
                                    posicion++;
                                    inicio = 0;
                                    for(iterador = 0; iterador < posicion; iterador++){
                                        inicio = inicio * 10 + unidades[iterador];
                                    }
                                    if(inicio == porcentaje)
                                        break;
                                }
                                for(iterador = 0; iterador < 10000; iterador++){
                                    if(cadena[iterador] == '\0'){
                                        contador = iterador;
                                        break;
                                    }
                                }
                                for(iterador = posicion - 1; iterador >= 0; iterador--){
                                    cadena[contador++] = unidades[iterador] + '0';
                                }
                                strcat(cadena, "% del disco ");
                                strcat(cadena, " \t\t\t\t</TD>\n");
                                if(mbr_.mbr_partition_4.part_status == '1'){
                                    inicio = mbr_.mbr_partition_4.part_start;
                                    if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != inicio){
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, "Libre <br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) (mbr_.mbr_partition_4.part_start - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }else{
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }
                                }else if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != mbr_.mbr_tamano){
                                    strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                    posicion = 0;
                                    porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                    while(porcentaje){
                                        if(porcentaje > 10){
                                            unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                            porcentaje = porcentaje / 10;
                                        }else{
                                            unidades[posicion] = porcentaje;
                                            posicion++;
                                            break;
                                        }
                                        posicion++;
                                        inicio = 0;
                                        for(iterador = 0; iterador < posicion; iterador++){
                                            inicio = inicio * 10 + unidades[iterador];
                                        }
                                        if(inicio == porcentaje)
                                            break;
                                    }
                                    for(iterador = 0; iterador < 10000; iterador++){
                                        if(cadena[iterador] == '\0'){
                                            contador = iterador;
                                            break;
                                        }
                                    }
                                    for(iterador = posicion - 1; iterador >= 0; iterador--){
                                        cadena[contador++] = unidades[iterador] + '0';
                                    }
                                    strcat(cadena, "% del disco ");
                                    strcat(cadena, " \t\t\t\t</TD>\n");
                                }
                            }
                        }else if(mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1 != mbr_.mbr_tamano){
                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                            posicion = 0;
                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1)) / mbr_.mbr_tamano) * 100;
                            while(porcentaje){
                                if(porcentaje > 10){
                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                    porcentaje = porcentaje / 10;
                                }else{
                                    unidades[posicion] = porcentaje;
                                    posicion++;
                                    break;
                                }
                                posicion++;
                                inicio = 0;
                                for(iterador = 0; iterador < posicion; iterador++){
                                    inicio = inicio * 10 + unidades[iterador];
                                }
                                if(inicio == porcentaje)
                                    break;
                            }
                            for(iterador = 0; iterador < 10000; iterador++){
                                if(cadena[iterador] == '\0'){
                                    contador = iterador;
                                    break;
                                }
                            }
                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                cadena[contador++] = unidades[iterador] + '0';
                            }
                            strcat(cadena, "% del disco ");
                            strcat(cadena, " \t\t\t\t</TD>\n");
                        }
                    }else{
                        strcat(cadena, "\t\t\t\t<TD> ");
                        strcat(cadena, mbr_.mbr_partition_2.part_name);
                        if(mbr_.mbr_partition_2.part_type == 'P' || mbr_.mbr_partition_2.part_type == 'p')
                            strcat(cadena, "<br></br>PRIMARIA<br></br>");
                        else if(mbr_.mbr_partition_2.part_type == 'E' || mbr_.mbr_partition_2.part_type == 'e')
                            strcat(cadena, "<br></br>EXTENDIDA<br></br>");
                        else
                            strcat(cadena, "<br></br>LOGICA<br></br>");
                        posicion = 0;
                        porcentaje = ((double) mbr_.mbr_partition_2.part_size / mbr_.mbr_tamano) * 100;
                        while(porcentaje){
                            if(porcentaje > 10){
                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                porcentaje = porcentaje / 10;
                            }else{
                                unidades[posicion] = porcentaje;
                                posicion++;
                                break;
                            }
                            posicion++;
                            inicio = 0;
                            for(iterador = 0; iterador < posicion; iterador++){
                                inicio = inicio * 10 + unidades[iterador];
                            }
                            if(inicio == porcentaje)
                                break;
                        }
                        for(iterador = 0; iterador < 10000; iterador++){
                            if(cadena[iterador] == '\0'){
                                contador = iterador;
                                break;
                            }
                        }
                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                            cadena[contador++] = unidades[iterador] + '0';
                        }
                        strcat(cadena, "% del disco ");
                        strcat(cadena, " \t\t\t\t</TD>\n");
                        if(mbr_.mbr_partition_3.part_status == '1'){
                            inicio = mbr_.mbr_partition_3.part_start;
                            if(mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1 != inicio){
                                strcat(cadena, "\t\t\t\t<TD> ");
                                strcat(cadena, "Libre <br></br><br></br>");
                                posicion = 0;
                                porcentaje = ((double) (mbr_.mbr_partition_3.part_start - (mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                while(porcentaje){
                                    if(porcentaje > 10){
                                        unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                        porcentaje = porcentaje / 10;
                                    }else{
                                        unidades[posicion] = porcentaje;
                                        posicion++;
                                        break;
                                    }
                                    posicion++;
                                    inicio = 0;
                                    for(iterador = 0; iterador < posicion; iterador++){
                                        inicio = inicio * 10 + unidades[iterador];
                                    }
                                    if(inicio == porcentaje)
                                        break;
                                }
                                for(iterador = 0; iterador < 10000; iterador++){
                                    if(cadena[iterador] == '\0'){
                                        contador = iterador;
                                        break;
                                    }
                                }
                                for(iterador = posicion - 1; iterador >= 0; iterador--){
                                    cadena[contador++] = unidades[iterador] + '0';
                                }
                                strcat(cadena, "% del disco ");
                                strcat(cadena, " \t\t\t\t</TD>\n");
                                strcat(cadena, "\t\t\t\t<TD> ");
                                strcat(cadena, mbr_.mbr_partition_3.part_name);
                                if(mbr_.mbr_partition_3.part_type == 'P' || mbr_.mbr_partition_3.part_type == 'p')
                                    strcat(cadena, "<br></br>PRIMARIA<br></br>");
                                else if(mbr_.mbr_partition_3.part_type == 'E' || mbr_.mbr_partition_3.part_type == 'e')
                                    strcat(cadena, "<br></br>EXTENDIDA<br></br>");
                                else
                                    strcat(cadena, "<br></br>LOGICA<br></br>");
                                posicion = 0;
                                porcentaje = ((double) mbr_.mbr_partition_3.part_size / mbr_.mbr_tamano) * 100;
                                while(porcentaje){
                                    if(porcentaje > 10){
                                        unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                        porcentaje = porcentaje / 10;
                                    }else{
                                        unidades[posicion] = porcentaje;
                                        posicion++;
                                        break;
                                    }
                                    posicion++;
                                    inicio = 0;
                                    for(iterador = 0; iterador < posicion; iterador++){
                                        inicio = inicio * 10 + unidades[iterador];
                                    }
                                    if(inicio == porcentaje)
                                        break;
                                }
                                for(iterador = 0; iterador < 10000; iterador++){
                                    if(cadena[iterador] == '\0'){
                                        contador = iterador;
                                        break;
                                    }
                                }
                                for(iterador = posicion - 1; iterador >= 0; iterador--){
                                    cadena[contador++] = unidades[iterador] + '0';
                                }
                                strcat(cadena, "% del disco ");
                                strcat(cadena, " \t\t\t\t</TD>\n");
                                if(mbr_.mbr_partition_4.part_status == '1'){
                                    inicio = mbr_.mbr_partition_4.part_start;
                                    if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != inicio){
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, "Libre <br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) (mbr_.mbr_partition_4.part_start - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }else{
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }
                                }else if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != mbr_.mbr_tamano){
                                    strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                    posicion = 0;
                                    porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                    while(porcentaje){
                                        if(porcentaje > 10){
                                            unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                            porcentaje = porcentaje / 10;
                                        }else{
                                            unidades[posicion] = porcentaje;
                                            posicion++;
                                            break;
                                        }
                                        posicion++;
                                        inicio = 0;
                                        for(iterador = 0; iterador < posicion; iterador++){
                                            inicio = inicio * 10 + unidades[iterador];
                                        }
                                        if(inicio == porcentaje)
                                            break;
                                    }
                                    for(iterador = 0; iterador < 10000; iterador++){
                                        if(cadena[iterador] == '\0'){
                                            contador = iterador;
                                            break;
                                        }
                                    }
                                    for(iterador = posicion - 1; iterador >= 0; iterador--){
                                        cadena[contador++] = unidades[iterador] + '0';
                                    }
                                    strcat(cadena, "% del disco ");
                                    strcat(cadena, " \t\t\t\t</TD>\n");
                                }
                            }else{
                                strcat(cadena, "\t\t\t\t<TD> ");
                                strcat(cadena, mbr_.mbr_partition_3.part_name);
                                if(mbr_.mbr_partition_3.part_type == 'P' || mbr_.mbr_partition_3.part_type == 'p')
                                    strcat(cadena, "<br></br>PRIMARIA<br></br>");
                                else if(mbr_.mbr_partition_3.part_type == 'E' || mbr_.mbr_partition_3.part_type == 'e')
                                    strcat(cadena, "<br></br>EXTENDIDA<br></br>");
                                else
                                    strcat(cadena, "<br></br>LOGICA<br></br>");
                                posicion = 0;
                                porcentaje = ((double) mbr_.mbr_partition_3.part_size / mbr_.mbr_tamano) * 100;
                                while(porcentaje){
                                    if(porcentaje > 10){
                                        unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                        porcentaje = porcentaje / 10;
                                    }else{
                                        unidades[posicion] = porcentaje;
                                        posicion++;
                                        break;
                                    }
                                    posicion++;
                                    inicio = 0;
                                    for(iterador = 0; iterador < posicion; iterador++){
                                        inicio = inicio * 10 + unidades[iterador];
                                    }
                                    if(inicio == porcentaje)
                                        break;
                                }
                                for(iterador = 0; iterador < 10000; iterador++){
                                    if(cadena[iterador] == '\0'){
                                        contador = iterador;
                                        break;
                                    }
                                }
                                for(iterador = posicion - 1; iterador >= 0; iterador--){
                                    cadena[contador++] = unidades[iterador] + '0';
                                }
                                strcat(cadena, "% del disco ");
                                strcat(cadena, " \t\t\t\t</TD>\n");
                                if(mbr_.mbr_partition_4.part_status == '1'){
                                    inicio = mbr_.mbr_partition_4.part_start;
                                    if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != inicio){
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, "Libre <br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) (mbr_.mbr_partition_4.part_start - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }else{
                                        strcat(cadena, "\t\t\t\t<TD> ");
                                        strcat(cadena, mbr_.mbr_partition_4.part_name);
                                        strcat(cadena, "<br></br><br></br>");
                                        posicion = 0;
                                        porcentaje = ((double) mbr_.mbr_partition_4.part_size / mbr_.mbr_tamano) * 100;
                                        while(porcentaje){
                                            if(porcentaje > 10){
                                                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                porcentaje = porcentaje / 10;
                                            }else{
                                                unidades[posicion] = porcentaje;
                                                posicion++;
                                                break;
                                            }
                                            posicion++;
                                            inicio = 0;
                                            for(iterador = 0; iterador < posicion; iterador++){
                                                inicio = inicio * 10 + unidades[iterador];
                                            }
                                            if(inicio == porcentaje)
                                                break;
                                        }
                                        for(iterador = 0; iterador < 10000; iterador++){
                                            if(cadena[iterador] == '\0'){
                                                contador = iterador;
                                                break;
                                            }
                                        }
                                        for(iterador = posicion - 1; iterador >= 0; iterador--){
                                            cadena[contador++] = unidades[iterador] + '0';
                                        }
                                        strcat(cadena, "% del disco ");
                                        strcat(cadena, " \t\t\t\t</TD>\n");
                                        if(mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1 != mbr_.mbr_tamano){
                                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                            posicion = 0;
                                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                            while(porcentaje){
                                                if(porcentaje > 10){
                                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                                    porcentaje = porcentaje / 10;
                                                }else{
                                                    unidades[posicion] = porcentaje;
                                                    posicion++;
                                                    break;
                                                }
                                                posicion++;
                                                inicio = 0;
                                                for(iterador = 0; iterador < posicion; iterador++){
                                                    inicio = inicio * 10 + unidades[iterador];
                                                }
                                                if(inicio == porcentaje)
                                                    break;
                                            }
                                            for(iterador = 0; iterador < 10000; iterador++){
                                                if(cadena[iterador] == '\0'){
                                                    contador = iterador;
                                                    break;
                                                }
                                            }
                                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                                cadena[contador++] = unidades[iterador] + '0';
                                            }
                                            strcat(cadena, "% del disco ");
                                            strcat(cadena, " \t\t\t\t</TD>\n");
                                        }
                                    }
                                }else if(mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1 != mbr_.mbr_tamano){
                                    strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                                    posicion = 0;
                                    porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1)) / mbr_.mbr_tamano) * 100;
                                    while(porcentaje){
                                        if(porcentaje > 10){
                                            unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                            porcentaje = porcentaje / 10;
                                        }else{
                                            unidades[posicion] = porcentaje;
                                            posicion++;
                                            break;
                                        }
                                        posicion++;
                                        inicio = 0;
                                        for(iterador = 0; iterador < posicion; iterador++){
                                            inicio = inicio * 10 + unidades[iterador];
                                        }
                                        if(inicio == porcentaje)
                                            break;
                                    }
                                    for(iterador = 0; iterador < 10000; iterador++){
                                        if(cadena[iterador] == '\0'){
                                            contador = iterador;
                                            break;
                                        }
                                    }
                                    for(iterador = posicion - 1; iterador >= 0; iterador--){
                                        cadena[contador++] = unidades[iterador] + '0';
                                    }
                                    strcat(cadena, "% del disco ");
                                    strcat(cadena, " \t\t\t\t</TD>\n");
                                }
                            }
                        }else if(mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1 != mbr_.mbr_tamano){
                            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                            posicion = 0;
                            porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1)) / mbr_.mbr_tamano) * 100;
                            while(porcentaje){
                                if(porcentaje > 10){
                                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                                    porcentaje = porcentaje / 10;
                                }else{
                                    unidades[posicion] = porcentaje;
                                    posicion++;
                                    break;
                                }
                                posicion++;
                                inicio = 0;
                                for(iterador = 0; iterador < posicion; iterador++){
                                    inicio = inicio * 10 + unidades[iterador];
                                }
                                if(inicio == porcentaje)
                                    break;
                            }
                            for(iterador = 0; iterador < 10000; iterador++){
                                if(cadena[iterador] == '\0'){
                                    contador = iterador;
                                    break;
                                }
                            }
                            for(iterador = posicion - 1; iterador >= 0; iterador--){
                                cadena[contador++] = unidades[iterador] + '0';
                            }
                            strcat(cadena, "% del disco ");
                            strcat(cadena, " \t\t\t\t</TD>\n");
                        }
                    }
                }else if(mbr_.mbr_partition_1.part_start + mbr_.mbr_partition_1.part_size + 1 != mbr_.mbr_tamano){
                    strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
                    posicion = 0;
                    porcentaje = ((double) (mbr_.mbr_tamano - (mbr_.mbr_partition_1.part_start + mbr_.mbr_partition_1.part_size + 1)) / mbr_.mbr_tamano) * 100;
                    while(porcentaje){
                        if(porcentaje > 10){
                            unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                            porcentaje = porcentaje / 10;
                        }else{
                            unidades[posicion] = porcentaje;
                            posicion++;
                            break;
                        }
                        posicion++;
                        inicio = 0;
                        for(iterador = 0; iterador < posicion; iterador++){
                            inicio = inicio * 10 + unidades[iterador];
                        }
                        if(inicio == porcentaje)
                            break;
                    }
                    for(iterador = 0; iterador < 10000; iterador++){
                        if(cadena[iterador] == '\0'){
                            contador = iterador;
                            break;
                        }
                    }
                    for(iterador = posicion - 1; iterador >= 0; iterador--){
                        cadena[contador++] = unidades[iterador] + '0';
                    }
                    strcat(cadena, "% del disco ");
                    strcat(cadena, " \t\t\t\t</TD>\n");
                }
            }
        }else {
            strcat(cadena, "\t\t\t\t<TD> Libre <br></br><br></br>");
            posicion = 0;
            porcentaje = ((double) (mbr_.mbr_tamano - sizeof(mbr)) / mbr_.mbr_tamano) * 100;
            while(porcentaje){
                if(porcentaje > 10){
                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                    porcentaje = porcentaje / 10;
                }else{
                    unidades[posicion] = porcentaje;
                    posicion++;
                    break;
                }
                posicion++;
                inicio = 0;
                for(iterador = 0; iterador < posicion; iterador++){
                    inicio = inicio * 10 + unidades[iterador];
                }
                if(inicio == porcentaje)
                    break;
            }
            for(iterador = 0; iterador < 10000; iterador++){
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            }
            for(iterador = posicion - 1; iterador >= 0; iterador--){
                cadena[contador++] = unidades[iterador] + '0';
            }
            strcat(cadena, "% del disco ");
            strcat(cadena, " \t\t\t\t</TD>\n");
        }
        strcat(cadena, "\t\t\t</TR>\n\t\t</TABLE>\n\t>, ];\n\t");
        strcat(cadena, "\n}");
        remove("/home/moramaz/Escritorio/re.dot");
        dot = fopen(reporte, "w");
        fclose(dot);
        dot = fopen(reporte, "a+t");
        int index = 0;
        char c = cadena[0];
        while(c != '}'){
            fputc(c, dot);
            index++;
            c = cadena[index];
        }/**/
        fputc(c, dot);
        fclose(dot);
        int j = 0, k = 0, l = 0;
        for(index = 0; index < 5; index++) xtncn[index] = '\0';
        for(l = 0; l < 199; l++) if(path[l] == '\0') break;
        for(index = l; index >= 0; index--){
            if(path[index] != '\0'){
                if(path[index] == '.'){
                    k = index + 1;
                    break;
                }
                j++;
            }
        }
        l = 0;
        while(j < 5 && j > 0) {
            xtncn[l++] = path[k++];
            j--;
        }
        strcpy(cadena, "dot ");
        strcat(cadena, reporte);
        strcat(cadena, " -o ");
        strcat(cadena, path);
        strcat(cadena, " -T");
        strcat(cadena, xtncn);
        strcat(cadena, " -Gcharset=utf8\0");
        system(cadena);
        fclose(disco);
        return 0;
    }else{
        printf("No se ha encontrado el id ingresado.\n");
        return -1;
    }
    return 0;
}

int rep_mbr(char id[5], char path[200]) {
    int posicion = 0, iterador = 0, contador = 0, condicion = 0, count;
    double inicio = 0, porcentaje = 0, unidades[20];
    char cadena[10000], xtncn[5], aidi = '1', reporte[42] = "/home/moramaz/Escritorio/re.dot";
    for(posicion = 0; posicion < 10000; posicion++) cadena[posicion] = '\0';
    posicion = 0;
    FILE *mounts, *disco, *dot;
    moun lector;
    mbr mbr_;
    limpiar_mount(&lector);
    mounts = fopen("/home/moramaz/Escritorio/mounts.dsk", "rb+");
    if(mounts == NULL){
        printf("No se ha encontrado ninguna particion montada.\n");
        return -1;
    }
    fseek(mounts, 0, SEEK_SET);
    fread(&lector, sizeof(moun), 1, mounts);
    while(1){
        for(count = 0; count < 5; count++){
            if(lector.id[count] == id[count])
                condicion = 1;
            else{
                condicion = 0;
                break;
            }
        }
        if(condicion || lector.id[0] == '\0')
            break;
        limpiar_mount(&lector);
        fread(&lector, sizeof(moun), 1, mounts);
    }
    fclose(mounts);
    if(condicion){
        disco = fopen(lector.path, "rb+");
        if(disco == NULL){
            printf("No se ha encontrado el disco de la particion montada.\n");
            return -1;
        }
        fseek(disco, 0, SEEK_SET);
        fread(&mbr_, sizeof(mbr), 1, disco);
        strcpy(cadena, "digraph SB{\n\trankdir = UD;\n\tgraph [ratio = fill];\n\tnode [shape = plaintext]\n\t");
        strcat(cadena, "NODO [label=<\n\t\t<TABLE ALIGN = \"LEFT\">\n");
        strcat(cadena, "\t\t\t<TR>\n");
        strcat(cadena, "\t\t\t\t<TD> ");
        strcat(cadena, "NOMBRE");
        strcat(cadena, " \t\t\t\t</TD>\n");
        strcat(cadena, "\t\t\t\t<TD> ");
        strcat(cadena, "VALOR");
        strcat(cadena, " \t\t\t\t</TD>\n");
        strcat(cadena, "\t\t\t</TR>\n");

        strcat(cadena, "\t\t\t<TR>\n");
        strcat(cadena, "\t\t\t\t<TD> ");
        strcat(cadena, "mbr_tamano");
        strcat(cadena, " \t\t\t\t</TD>\n");
        strcat(cadena, "\t\t\t\t<TD> ");
        porcentaje = mbr_.mbr_tamano;
        while(porcentaje){
            if(porcentaje > 10){
                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                porcentaje = porcentaje / 10;
            }else{
                unidades[posicion] = porcentaje;
                posicion++;
                break;
            }
            posicion++;
            inicio = 0;
            for(iterador = 0; iterador < posicion; iterador++){
                inicio = inicio * 10 + unidades[iterador];
            }
            if(inicio == porcentaje)
                break;
        }
        for(iterador = 0; iterador < 10000; iterador++)
            if(cadena[iterador] == '\0'){
                contador = iterador;
                break;
            }
        for(iterador = posicion - 1; iterador >= 0; iterador--)
            cadena[contador++] = unidades[iterador] + '0';
        posicion = 0;
        strcat(cadena, " \t\t\t\t</TD>\n");
        strcat(cadena, "\t\t\t</TR>\n");
        strcat(cadena, "\t\t\t<TR>\n");
        strcat(cadena, "\t\t\t\t<TD> ");
        strcat(cadena, "mbr_fecha_creacion");
        strcat(cadena, " \t\t\t\t</TD>\n");
        strcat(cadena, "\t\t\t\t<TD> ");
        if(mbr_.mbr_fecha_creacion) strcat(cadena, ctime(&mbr_.mbr_fecha_creacion));
        else strcat(cadena, " ");
        strcat(cadena, " \t\t\t\t</TD>\n");
        strcat(cadena, "\t\t\t</TR>\n");
        strcat(cadena, "\t\t\t<TR>\n");
        strcat(cadena, "\t\t\t\t<TD> ");
        strcat(cadena, "mbr_disk_signature");
        strcat(cadena, " \t\t\t\t</TD>\n");
        strcat(cadena, "\t\t\t\t<TD> ");
        porcentaje = mbr_.mbr_disk_signature;
        while(porcentaje){
            if(porcentaje > 10){
                unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                porcentaje = porcentaje / 10;
            }else{
                unidades[posicion] = porcentaje;
                posicion++;
                break;
            }
            posicion++;
            inicio = 0;
            for(iterador = 0; iterador < posicion; iterador++){
                inicio = inicio * 10 + unidades[iterador];
            }
            if(inicio == porcentaje)
                break;
        }
        for(iterador = 0; iterador < 10000; iterador++)
            if(cadena[iterador] == '\0'){
                contador = iterador;
                break;
            }
        for(iterador = posicion - 1; iterador >= 0; iterador--)
            cadena[contador++] = unidades[iterador] + '0';
        posicion = 0;
        strcat(cadena, " \t\t\t\t</TD>\n");
        strcat(cadena, "\t\t\t</TR>\n");
        strcat(cadena, "\t\t\t<TR>\n");
        strcat(cadena, "\t\t\t\t<TD> ");
        strcat(cadena, "Disk_fit");
        strcat(cadena, " \t\t\t\t</TD>\n");
        strcat(cadena, "\t\t\t\t<TD> ");
        for(iterador = 0; iterador < 10000; iterador++)
            if(cadena[iterador] == '\0'){
                contador = iterador;
                break;
            }
        cadena[contador++] = mbr_.disk_fit;
        strcat(cadena, " \t\t\t\t</TD>\n");
        strcat(cadena, "\t\t\t</TR>\n");
        if(mbr_.mbr_partition_1.part_status == '1'){
            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_status_1");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> 1");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_type_1");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            cadena[contador++] = mbr_.mbr_partition_1.part_type;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_fit_1");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            cadena[contador++] = mbr_.mbr_partition_1.part_fit;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_start_1");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            porcentaje = mbr_.mbr_partition_1.part_start;
            while(porcentaje){
                if(porcentaje > 10){
                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                    porcentaje = porcentaje / 10;
                }else{
                    unidades[posicion] = porcentaje;
                    posicion++;
                    break;
                }
                posicion++;
                inicio = 0;
                for(iterador = 0; iterador < posicion; iterador++){
                    inicio = inicio * 10 + unidades[iterador];
                }
                if(inicio == porcentaje)
                    break;
            }
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            for(iterador = posicion - 1; iterador >= 0; iterador--)
                cadena[contador++] = unidades[iterador] + '0';
            posicion = 0;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_size_1");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            porcentaje = mbr_.mbr_partition_1.part_size;
            while(porcentaje){
                if(porcentaje > 10){
                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                    porcentaje = porcentaje / 10;
                }else{
                    unidades[posicion] = porcentaje;
                    posicion++;
                    break;
                }
                posicion++;
                inicio = 0;
                for(iterador = 0; iterador < posicion; iterador++){
                    inicio = inicio * 10 + unidades[iterador];
                }
                if(inicio == porcentaje)
                    break;
            }
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            for(iterador = posicion - 1; iterador >= 0; iterador--)
                cadena[contador++] = unidades[iterador] + '0';
            posicion = 0;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_name_1");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, mbr_.mbr_partition_1.part_name);
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");
        }
        if(mbr_.mbr_partition_2.part_status == '1'){
            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_status_2");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> 1");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_type_2");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            cadena[contador++] = mbr_.mbr_partition_2.part_type;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_fit_2");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            cadena[contador++] = mbr_.mbr_partition_2.part_fit;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_start_2");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            porcentaje = mbr_.mbr_partition_2.part_start;
            while(porcentaje){
                if(porcentaje > 10){
                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                    porcentaje = porcentaje / 10;
                }else{
                    unidades[posicion] = porcentaje;
                    posicion++;
                    break;
                }
                posicion++;
                inicio = 0;
                for(iterador = 0; iterador < posicion; iterador++){
                    inicio = inicio * 10 + unidades[iterador];
                }
                if(inicio == porcentaje)
                    break;
            }
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            for(iterador = posicion - 1; iterador >= 0; iterador--)
                cadena[contador++] = unidades[iterador] + '0';
            posicion = 0;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_size_2");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            porcentaje = mbr_.mbr_partition_2.part_size;
            while(porcentaje){
                if(porcentaje > 10){
                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                    porcentaje = porcentaje / 10;
                }else{
                    unidades[posicion] = porcentaje;
                    posicion++;
                    break;
                }
                posicion++;
                inicio = 0;
                for(iterador = 0; iterador < posicion; iterador++){
                    inicio = inicio * 10 + unidades[iterador];
                }
                if(inicio == porcentaje)
                    break;
            }
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            for(iterador = posicion - 1; iterador >= 0; iterador--)
                cadena[contador++] = unidades[iterador] + '0';
            posicion = 0;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_name_2");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, mbr_.mbr_partition_2.part_name);
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");
        }
        if(mbr_.mbr_partition_3.part_status == '1'){
            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_status_3");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> 1");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_type_3");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            cadena[contador++] = mbr_.mbr_partition_3.part_type;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_fit_3");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            cadena[contador++] = mbr_.mbr_partition_3.part_fit;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_start_3");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            porcentaje = mbr_.mbr_partition_3.part_start;
            while(porcentaje){
                if(porcentaje > 10){
                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                    porcentaje = porcentaje / 10;
                }else{
                    unidades[posicion] = porcentaje;
                    posicion++;
                    break;
                }
                posicion++;
                inicio = 0;
                for(iterador = 0; iterador < posicion; iterador++){
                    inicio = inicio * 10 + unidades[iterador];
                }
                if(inicio == porcentaje)
                    break;
            }
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            for(iterador = posicion - 1; iterador >= 0; iterador--)
                cadena[contador++] = unidades[iterador] + '0';
            posicion = 0;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_size_3");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            porcentaje = mbr_.mbr_partition_3.part_size;
            while(porcentaje){
                if(porcentaje > 10){
                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                    porcentaje = porcentaje / 10;
                }else{
                    unidades[posicion] = porcentaje;
                    posicion++;
                    break;
                }
                posicion++;
                inicio = 0;
                for(iterador = 0; iterador < posicion; iterador++){
                    inicio = inicio * 10 + unidades[iterador];
                }
                if(inicio == porcentaje)
                    break;
            }
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            for(iterador = posicion - 1; iterador >= 0; iterador--)
                cadena[contador++] = unidades[iterador] + '0';
            posicion = 0;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_name_3");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, mbr_.mbr_partition_3.part_name);
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");
        }
        if(mbr_.mbr_partition_4.part_status == '1'){
            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_status_4");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> 1");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_type_4");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            cadena[contador++] = mbr_.mbr_partition_4.part_type;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_fit_4");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            cadena[contador++] = mbr_.mbr_partition_4.part_fit;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_start_4");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            porcentaje = mbr_.mbr_partition_4.part_start;
            while(porcentaje){
                if(porcentaje > 10){
                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                    porcentaje = porcentaje / 10;
                }else{
                    unidades[posicion] = porcentaje;
                    posicion++;
                    break;
                }
                posicion++;
                inicio = 0;
                for(iterador = 0; iterador < posicion; iterador++){
                    inicio = inicio * 10 + unidades[iterador];
                }
                if(inicio == porcentaje)
                    break;
            }
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            for(iterador = posicion - 1; iterador >= 0; iterador--)
                cadena[contador++] = unidades[iterador] + '0';
            posicion = 0;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_size_4");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            porcentaje = mbr_.mbr_partition_4.part_size;
            while(porcentaje){
                if(porcentaje > 10){
                    unidades[posicion] = porcentaje - ((int) (porcentaje / 10)) *10;
                    porcentaje = porcentaje / 10;
                }else{
                    unidades[posicion] = porcentaje;
                    posicion++;
                    break;
                }
                posicion++;
                inicio = 0;
                for(iterador = 0; iterador < posicion; iterador++){
                    inicio = inicio * 10 + unidades[iterador];
                }
                if(inicio == porcentaje)
                    break;
            }
            for(iterador = 0; iterador < 10000; iterador++)
                if(cadena[iterador] == '\0'){
                    contador = iterador;
                    break;
                }
            for(iterador = posicion - 1; iterador >= 0; iterador--)
                cadena[contador++] = unidades[iterador] + '0';
            posicion = 0;
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");

            strcat(cadena, "\t\t\t<TR>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, "part_name_4");
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t\t<TD> ");
            strcat(cadena, mbr_.mbr_partition_4.part_name);
            strcat(cadena, " \t\t\t\t</TD>\n");
            strcat(cadena, "\t\t\t</TR>\n");
        }
        strcat(cadena, "\t\t</TABLE>\n\t>, ];\n\t");
        strcat(cadena, "\n}");
        remove("/home/moramaz/Escritorio/re.dot");
        dot = fopen(reporte, "w");
        fclose(dot);
        dot = fopen(reporte, "a+t");
        int index = 0;
        char c = cadena[0];
        while(c != '}'){
            fputc(c, dot);
            index++;
            c = cadena[index];
        }/**/
        fputc(c, dot);
        fclose(dot);
        int j = 0, k = 0, l = 0;
        for(index = 0; index < 5; index++) xtncn[index] = '\0';
        for(l = 0; l < 199; l++) if(path[l] == '\0') break;
        for(index = l; index >= 0; index--){
            if(path[index] != '\0'){
                if(path[index] == '.'){
                    k = index + 1;
                    break;
                }
                j++;
            }
        }
        l = 0;
        while(j < 5 && j > 0) {
            xtncn[l++] = path[k++];
            j--;
        }
        strcpy(cadena, "dot ");
        strcat(cadena, reporte);
        strcat(cadena, " -o ");
        strcat(cadena, path);
        strcat(cadena, " -T");
        strcat(cadena, xtncn);
        strcat(cadena, " -Gcharset=utf8\0");
        system(cadena);
        fclose(disco);
        return 0;
    }else{
        printf("No se ha encontrado el id ingresado.\n");
        return -1;
    }
    return 0;
}
