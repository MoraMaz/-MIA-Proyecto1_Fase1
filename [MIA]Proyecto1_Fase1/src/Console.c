#include <Console.h>

int menu(){
    char cadena1[300], cadena2[200], aexit[4] = "exit", aexec[4] = "exec";
    cadena1[0] = '\0';
    int posicion;
    boolean condicion = true, bexec = false;
    while(condicion){
        posicion = 0;
        printf("Comando > ");
        scanf(" %[^\n]s", cadena1);
        if(cadena1[0] == '\0'){
            printf(" ---------------- \n");
            return menu();
        }
        posicion = 0;
        for(posicion = 0; posicion < 4; posicion++){
            if(cadena1[posicion] != aexec[posicion] && cadena1[posicion] != aexec[posicion] - 32){
                bexec = false;
                break;
            }
            bexec = true;
        }
        if(bexec){
            while(cadena1[posicion] == ' ' || cadena1[posicion] == '-') posicion++;
            cadena2[0] = 'p'; cadena2[1] = 'a'; cadena2[2] = 't'; cadena2[3] = 'h';
            for(bexec = 0; bexec < 4; bexec++, posicion++){
                if(cadena2[bexec] != cadena1[posicion]){
                    bexec = false;
                    break;
                }
            }
            if(bexec){
                bexec = 0;
                if(cadena1[posicion] != '~'){
                    printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                    return -1;
                }
                posicion++; //~
                if(cadena1[posicion] != ':'){
                    printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                    return -1;
                }
                posicion++; //:
                if(cadena1[posicion] != '~'){
                    printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                    return -1;
                }
                posicion++; //~
                if(cadena1[posicion] == '"'){
                    posicion++;
                    while(cadena1[posicion] != '"'){
                        cadena2[bexec] = cadena1[posicion];
                        posicion++;
                        bexec++;
                    }
                }else{
                    while(cadena1[posicion] != '\0' && cadena1[posicion] != ' '){
                        cadena2[bexec] = cadena1[posicion];
                        posicion++;
                        bexec++;
                    }
                }
                cadena2[bexec] = '\0';
                FILE * exec;
                exec = fopen(cadena2, "r");
                if(!exec) {
                    printf("ERROR: No se ha podido abrir el archivo especificado.\n");
                } else {
                    do{
                        for(bexec = 0; bexec < 300; bexec++) cadena1[bexec] = '\0';
                        if(fgets(cadena1, 300, exec)){
                            printf("Comando > %s\n", cadena1);
                            comando(cadena1);
                        }
                    }while(cadena1[0] != '\0');
                    fclose(exec);
                }
            }
            bexec = false;
        }else{
            for(posicion = 0; posicion < 4; posicion++){
                if(cadena1[posicion] != aexit[posicion] && cadena1[posicion] != aexit[posicion] - 32){
                    condicion = true;
                    break;
                }
                condicion = false;
            }
            if(condicion){
                comando(cadena1);
            }
        }
        posicion = 299;
        while(posicion) cadena1[posicion--] = '\0';
        cadena1[0] = '\0';
    }
    return 0;
}

int comando(char cadena1[300]){
    int posicion = 0, i = 0, j = -1996, a = -1996, condicion = false;
    char amk[6] = "mkdisk", arm[6] = "rmdisk", afd[5] = "fdisk", amo[5] = "mount", aun[7] = "unmount", are[3] = "rep", aml[6] = "mkfile", ams[4] = "mkfs", ali[5] = "login",
    alo[6] = "logout", agp[5] = "mkgrp", arp[5] = "rmgrp", amu[5] = "mkusr", aru[5] = "rmusr", ach[5] = "chmod", aca[3] = "cat", aem[3] = "rem", aed[4] = "edit",
    aen[3] = "ren", amd[5] = "mkdir", acp[2] = "cp", amv[2] = "mv", afi[4] = "find", aow[5] = "chown", acg[5] = "chgrp", ary[8] = "recovery", ass[4] = "loss", par1[200],
    ruta[200], par2[16], id[5], u = 'm', t = 'p', f = 'w', fd = 'f', d = '\0';
    while(cadena1[posicion] == '\n' || cadena1[posicion] == '\r' || cadena1[posicion] == '\c' || cadena1[posicion] == '#'){
         posicion++;
         //if(cadena1[posicion] == '#') while(cadena1[posicion] != '\n') posicion++;
         if(cadena1[posicion] == '\0') return -1;
    }
    for(posicion = 0; posicion < 6; posicion++){
        if(cadena1[posicion] != amk[posicion] && cadena1[posicion] != amk[posicion] - 32){
            condicion = false;
            break;
        }
        condicion = true;
    }
    if(condicion){
        par1[0] = '\0';
        j = -1996;
        while(cadena1[posicion] != '\0'){
            if(cadena1[posicion] == '#'){
                while(cadena1[posicion] != '\n' && cadena1[posicion] != '\0')
                    posicion++;
            }else if(cadena1[posicion] == 32 || cadena1[posicion] == '\n' || cadena1[posicion] == '\r'){
                posicion++;
            }else if(cadena1[posicion] == 45){
                posicion++;
                if(cadena1[posicion] == 'P' || cadena1[posicion] == 'p'){
                    posicion++;
                    if(cadena1[posicion] == 'A' || cadena1[posicion] == 'a'){
                        posicion++;
                        if(cadena1[posicion] == 'T' || cadena1[posicion] == 't'){
                            posicion++;
                            if(cadena1[posicion] == 'H' || cadena1[posicion] == 'h'){
                                posicion++; //~
                                if(cadena1[posicion] != '~'){
                                    printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                    return -1;
                                }
                                posicion++; //:
                                if(cadena1[posicion] != ':'){
                                    printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                    return -1;
                                }
                                posicion++; //~
                                if(cadena1[posicion] != '~'){
                                    printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                    return -1;
                                }
                                posicion++;
                                par1[0] = 'm'; par1[1] = 'k'; par1[2] = 'd'; par1[3] = 'i'; par1[4] = 'r'; par1[5] = ' '; par1[6] = '"';
                                if(cadena1[posicion] == '"'){
                                    i = 7;
                                    posicion++;
                                    while(cadena1[posicion] != '"'){
                                        if(cadena1[posicion] == '/' && i > 7){
                                            par1[i] = '"';
                                            par1[i + 1] = '\0';
                                            system(par1);
                                        }
                                        par1[i] = cadena1[posicion];
                                        i++;
                                        posicion++;
                                    }
                                    par1[i] = '\0';
                                    i = 0;
                                    while(par1[i] != '\0'){
                                        par1[i] = par1[i + 7];
                                        i++;
                                    }
                                    par1[i - 1] = '\0';
                                    posicion++;
                                }else {
                                    i = 6;
                                    while(cadena1[posicion] != ' ' && cadena1[posicion] != '\0' && cadena1[posicion] != '\n'){
                                        if(cadena1[posicion] == '/' && i > 6){
                                            par1[i] = '\0';
                                            system(par1);
                                        }
                                        par1[i] = cadena1[posicion];
                                        i++;
                                        posicion++;
                                    }
                                    par1[i] = '\0';
                                    i = 0;
                                    while(par1[i] != '\0'){
                                        par1[i] = par1[i + 6];
                                        i++;
                                    }
                                    par1[i - 1] = '\0';
                                    posicion++;
                                }
                            }else {
                                printf("ERROR: Parametro no identificado.\n");
                                condicion = false;
                            }
                        }else {
                            printf("ERROR: Parametro no identificado.\n");
                            condicion = false;
                        }
                    }else {
                        printf("ERROR: Parametro no identificado.\n");
                        condicion = false;
                    }
                }else if(cadena1[posicion] == 'u' || cadena1[posicion] == 'U'){
                    posicion++;
                    if(cadena1[posicion] == 'N' || cadena1[posicion] == 'n'){
                        posicion++;
                        if(cadena1[posicion] == 'i' || cadena1[posicion] == 'I'){
                            posicion++;
                            if(cadena1[posicion] == 't' || cadena1[posicion] == 'T'){
                                posicion++; //~
                                if(cadena1[posicion] != '~'){
                                    printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                    return -1;
                                }
                                posicion++; //:
                                if(cadena1[posicion] != ':'){
                                    printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                    return -1;
                                }
                                posicion++; //~
                                if(cadena1[posicion] != '~'){
                                    printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                    return -1;
                                }
                                posicion++;
                                if(cadena1[posicion] == 'k' || cadena1[posicion] == 'K')
                                    u = 'k';
                                else if(cadena1[posicion] == 'M' || cadena1[posicion] == 'm')
                                    u = 'm';
                                else{
                                    printf("ERROR: El parametro unit solo puede tener como valor 'k' o 'm'.\n");
                                    return 0;
                                }
                                posicion++;
                            }else{
                                printf("ERROR: Parametro no identificado.\n");
                                condicion = false;
                            }
                        }else{
                            printf("ERROR: Parametro no identificado.\n");
                            condicion = false;
                        }
                    }else{
                        printf("ERROR: Parametro no identificado.\n");
                        condicion = false;
                    }
                }else if(cadena1[posicion] == 'S' || cadena1[posicion] == 's'){
                    posicion++;
                    if(cadena1[posicion] == 'i' || cadena1[posicion] == 'I'){
                        posicion++;
                        if(cadena1[posicion] == 'z' || cadena1[posicion] == 'Z'){
                            posicion++;
                            if(cadena1[posicion] == 'E' || cadena1[posicion] == 'e'){
                                posicion++; //~
                                if(cadena1[posicion] != '~'){
                                    printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                    return -1;
                                }
                                posicion++; //:
                                if(cadena1[posicion] != ':'){
                                    printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                    return -1;
                                }
                                posicion++; //~
                                if(cadena1[posicion] != '~'){
                                    printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                    return -1;
                                }
                                posicion++;
                                if(cadena1[posicion] == '-'){
                                    printf("ERROR: El parametro size no puede tener un valor menor o igual a 0.\n");
                                    return 0;
                                }
                                j = -1996;
                                while(cadena1[posicion] != ' ' && cadena1[posicion] != '\0' && cadena1[posicion] != '\n' && cadena1[posicion] != '\r' && cadena1[posicion] != '\c'){
                                    if(j == -1996)
                                        j = cadena1[posicion] - '0';
                                    else{
                                        j = j * 10 + cadena1[posicion] - '0';
                                    }
                                    posicion++;
                                }
                                if(j == 0){
                                    printf("ERROR: El parametro size no puede tener un valor menor o igual a 0.\n");
                                    return j;
                                }
                                posicion++;
                            }else {
                                printf("ERROR: Parametro no identificado.\n");
                                condicion = false;
                            }
                        }else {
                            printf("ERROR: Parametro no identificado.\n");
                            condicion = false;
                        }
                    }else {
                        printf("ERROR: Parametro no identificado.\n");
                        condicion = false;
                    }
                }else if(cadena1[posicion] == 'f' || cadena1[posicion] == 'F'){
                    posicion++;
                    if(cadena1[posicion] == 'i' || cadena1[posicion] == 'I'){
                        posicion++;
                        if(cadena1[posicion] == 't' || cadena1[posicion] == 'T'){
                            posicion++; //~
                            if(cadena1[posicion] != '~'){
                                printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                return -1;
                            }
                            posicion++; //:
                            if(cadena1[posicion] != ':'){
                                printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                return -1;
                            }
                            posicion++; //~
                            if(cadena1[posicion] != '~'){
                                printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                return -1;
                            }
                            posicion++;
                            if(cadena1[posicion] == 'b' || cadena1[posicion] == 'B') fd = 'b';
                            else if(cadena1[posicion] == 'f' || cadena1[posicion] == 'F') fd = 'f';
                            else if(cadena1[posicion] == 'w' || cadena1[posicion] == 'W') fd = 'w';
                            else{
                                printf("ERROR: El parametro fit solo puede tener como valor 'bf', 'ff' o 'wf'.\n");
                                return -1;
                            }
                            posicion++; // f
                            posicion++;
                        }else {
                            printf("ERROR: Parametro no identificado.\n");
                            condicion = false;
                        }
                    }else {
                        printf("ERROR: Parametro no identificado.\n");
                        condicion = false;
                    }
                }else if(cadena1[posicion] == '#'){
                    while(cadena1[posicion] != '\n' && cadena1[posicion] != '\0')
                        posicion++;
                }else {
                    printf("ERROR: Parametro no identificado.\n");
                    condicion = false;
                }
            }else{
                printf("%c\n", cadena1[posicion]);
                posicion++;
            }
        }
       if(u == 'm' || u == 'M') j = j * 1024;
        if(condicion && j > 0 && par1[0] != '\0') return mkdisk(par1, fd, j);
        else {
            printf("ERROR: Falta por lo menos un parametro obligatorio.\n");
            return -1;
        }
    }else{
        condicion = true;
        for(posicion = 0; posicion < 6; posicion++){
            if(cadena1[posicion] != arm[posicion] && cadena1[posicion] != arm[posicion] - 32){
                condicion = false;
                break;
            }
            condicion = true;
        }
        if(condicion){
            par1[0] = '\0';
            while(cadena1[posicion] != '\0' && cadena1[posicion] != '\n'){
                if(cadena1[posicion] == '#'){
                    while(cadena1[posicion] != '\n' && cadena1[posicion] != '\0')
                        posicion++;
                }else if(cadena1[posicion] == 32 || cadena1[posicion] == '\n' || cadena1[posicion] == '\r'){
                    posicion++;
                }else if(cadena1[posicion] == 45){
                    posicion++;
                    if(cadena1[posicion] == 'P' || cadena1[posicion] == 'p'){
                        posicion++;
                        if(cadena1[posicion] == 'A' || cadena1[posicion] == 'a'){
                            posicion++;
                            if(cadena1[posicion] == 'T' || cadena1[posicion] == 't'){
                                posicion++;
                                if(cadena1[posicion] == 'H' || cadena1[posicion] == 'h'){
                                    posicion++; //~
                                    if(cadena1[posicion] != '~'){
                                        printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                        return -1;
                                    }
                                    posicion++; //:
                                    if(cadena1[posicion] != ':'){
                                        printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                        return -1;
                                    }
                                    posicion++; //~
                                    if(cadena1[posicion] != '~'){
                                        printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                        return -1;
                                    }
                                    posicion++;
                                    i = 0;
                                    if(cadena1[posicion] == '"'){
                                        posicion++;
                                        while(cadena1[posicion] != '"'){
                                            par1[i] = cadena1[posicion];
                                            i++;
                                            posicion++;
                                        }
                                    }else {
                                        while(cadena1[posicion] != ' ' && cadena1[posicion] != '\0' && cadena1[posicion] != '\n'){
                                            par1[i] = cadena1[posicion];
                                            i++;
                                            posicion++;
                                        }
                                    }
                                    par1[i] = '\0';
                                    FILE * f = fopen(par1, "r");
                                    if(!f){
                                        printf("ERROR: No existe el disco especificado.\n");
                                        return -1;
                                    }
                                    fclose(f);
                                    printf("Está seguro de querer eliminar el disco? [s/n]\n");
                                    posicion++;
                                }else {
                                    printf("ERROR: Parametro no identificado.\n");
                                    condicion = false;
                                }
                            }else {
                                printf("ERROR: Parametro no identificado.\n");
                                condicion = false;
                            }
                        }else {
                            printf("ERROR: Parametro no identificado.\n");
                            condicion = false;
                        }
                    }else {
                        printf("ERROR: Parametro no identificado.\n");
                        condicion = false;
                    }
                }else if(cadena1[posicion] == '#'){
                    while(cadena1[posicion] != '\n' && cadena1[posicion] != '\0')
                        posicion++;
                }else {
                    printf("%c\n", cadena1[posicion]);
                    posicion++;
                }
            }
            if(condicion && par1[0] != '\0') return rmdisk(par1);
            else {
                printf("ERROR: Falta por lo menos un parametro obligatorio.\n");
                return -1;
            }
        }else{
            condicion = true;
            for(posicion = 0; posicion < 5; posicion++){
                if(cadena1[posicion] != afd[posicion] && cadena1[posicion] != afd[posicion] - 32){
                    condicion = false;
                    break;
                }
                condicion = true;
            }
            if(condicion){
                j = -1996;
                u = 'k';
                while(cadena1[posicion] != '\0' && cadena1[posicion] != '\n'){
                    if(cadena1[posicion] == '#'){
                        while(cadena1[posicion] != '\n' && cadena1[posicion] != '\0')
                            posicion++;
                    }else if(cadena1[posicion] == 32 || cadena1[posicion] == '\n' || cadena1[posicion] == '\r'){
                        posicion++;
                    }else if(cadena1[posicion] == 45){
                        posicion++;
                        if(cadena1[posicion] == 's' || cadena1[posicion] == 'S'){
                            posicion++;
                            if(cadena1[posicion] == 'i' || cadena1[posicion] == 'I'){
                                posicion++;
                                if(cadena1[posicion] == 'z' || cadena1[posicion] == 'Z'){
                                    posicion++;
                                    if(cadena1[posicion] == 'e' || cadena1[posicion] == 'E'){
                                        posicion++; //~
                                        if(cadena1[posicion] != '~'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++; //:
                                        if(cadena1[posicion] != ':'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++; //~
                                        if(cadena1[posicion] != '~'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++;
                                        if(cadena1[posicion] == '-'){
                                            printf("ERROR: El parametro size no puede tener un valor menor o igual a 0.\n");
                                            return 0;
                                        }
                                        j = -1996;
                                        while(cadena1[posicion] != ' ' && cadena1[posicion] != '\0' && cadena1[posicion] != '\n'){
                                            if(j == -1996)
                                                j = cadena1[posicion] - '0';
                                            else{
                                                j = j * 10 + cadena1[posicion] - '0';
                                            }
                                            posicion++;
                                        }
                                        if(j == 0){
                                            printf("ERROR: El parametro size no puede tener un valor menor o igual a 0.\n");
                                            return j;
                                        }
                                        posicion++;
                                    }else {
                                        printf("ERROR: Parametro no identificado.\n");
                                        condicion = false;
                                    }
                                }else {
                                    printf("ERROR: Parametro no identificado.\n");
                                    condicion = false;
                                }
                            }else {
                                printf("ERROR: Parametro no identificado.\n");
                                condicion = false;
                            }
                        } else if(cadena1[posicion] == 'u' || cadena1[posicion] == 'U'){
                            posicion++;
                            if(cadena1[posicion] == 'n' || cadena1[posicion] == 'N'){
                                posicion++;
                                if(cadena1[posicion] == 'i' || cadena1[posicion] == 'I'){
                                    posicion++;
                                    if(cadena1[posicion] == 't' || cadena1[posicion] == 'T'){
                                        posicion++; //~
                                        if(cadena1[posicion] != '~'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++; //:
                                        if(cadena1[posicion] != ':'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++; //~
                                        if(cadena1[posicion] != '~'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++;
                                        if(cadena1[posicion] == 'B' || cadena1[posicion] == 'b')
                                            u = 'b';
                                        else if(cadena1[posicion] == 'k' || cadena1[posicion] == 'K')
                                            u = 'k';
                                        else if(cadena1[posicion] == 'M' || cadena1[posicion] == 'm')
                                            u = 'm';
                                        else {
                                            printf("ERROR: El parametro unit solo puede tener como valor 'b', 'k' o 'm'.\n");
                                            return 0;
                                        }
                                        posicion++;
                                    }else {
                                        printf("ERROR: Parametro no identificado.\n");
                                        condicion = false;
                                    }
                                }else {
                                    printf("ERROR: Parametro no identificado.\n");
                                    condicion = false;
                                }
                            }else {
                                printf("ERROR: Parametro no identificado.\n");
                                condicion = false;
                            }
                        } else if(cadena1[posicion] == 'p' || cadena1[posicion] == 'P'){
                            posicion++;
                            if(cadena1[posicion] == 'a' || cadena1[posicion] == 'A'){
                                posicion++;
                                if(cadena1[posicion] == 't' || cadena1[posicion] == 'T'){
                                    posicion++;
                                    if(cadena1[posicion] == 'h' || cadena1[posicion] == 'H'){
                                        posicion++; //~
                                        if(cadena1[posicion] != '~'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++; //:
                                        if(cadena1[posicion] != ':'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++; //~
                                        if(cadena1[posicion] != '~'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++;
                                        i = 0;
                                        if(cadena1[posicion] == '"'){
                                            posicion++;
                                            while(cadena1[posicion] != '"'){
                                                par1[i] = cadena1[posicion];
                                                i++;
                                                posicion++;
                                            }
                                        }else {
                                            while(cadena1[posicion] != ' ' && cadena1[posicion] != '\0' && cadena1[posicion] != '\n'){
                                                par1[i] = cadena1[posicion];
                                                i++;
                                                posicion++;
                                            }
                                        }
                                        par1[i] = '\0';
                                        FILE * disco = fopen(par1, "r");
                                        if(!disco){
                                            printf("ERROR: No existe el disco especificado.\n");
                                            return -1;
                                        }
                                        fclose(disco);
                                        posicion++;
                                    }else {
                                        printf("ERROR: Parametro no identificado.\n");
                                        condicion = false;
                                    }
                                }else {
                                    printf("ERROR: Parametro no identificado.\n");
                                    condicion = false;
                                }
                            }else {
                                printf("ERROR: Parametro no identificado.\n");
                                condicion = false;
                            }
                        }else if(cadena1[posicion] == 't' || cadena1[posicion] == 'T'){
                            posicion++;
                            if(cadena1[posicion] == 'y' || cadena1[posicion] == 'Y'){
                                posicion++;
                                if(cadena1[posicion] == 'p' || cadena1[posicion] == 'P'){
                                    posicion++;
                                    if(cadena1[posicion] == 'e' || cadena1[posicion] == 'E'){
                                        posicion++; //~
                                        if(cadena1[posicion] != '~'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++; //:
                                        if(cadena1[posicion] != ':'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++; //~
                                        if(cadena1[posicion] != '~'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++;
                                        if(cadena1[posicion] == 'p' || cadena1[posicion] == 'P')
                                            t = 'p';
                                        else if(cadena1[posicion] == 'e' || cadena1[posicion] == 'E')
                                            t = 'e';
                                        else if(cadena1[posicion] == 'l' || cadena1[posicion] == 'L')
                                            t = 'l';
                                        else{
                                            printf("ERROR: El parametro type solo puede tener como valor 'p', 'e' o 'l'.\n");
                                            return 0;
                                        }
                                        posicion++;
                                    }else {
                                        printf("ERROR: Parametro no identificado.\n");
                                        condicion = false;
                                    }
                                }else {
                                    printf("ERROR: Parametro no identificado.\n");
                                    condicion = false;
                                }
                            }else {
                                printf("ERROR: Parametro no identificado.\n");
                                condicion = false;
                            }
                        } else if(cadena1[posicion] == 'f' || cadena1[posicion] == 'F'){
                            posicion++;
                            if(cadena1[posicion] == 'i' || cadena1[posicion] == 'I'){
                                posicion++;
                                if(cadena1[posicion] == 't' || cadena1[posicion] == 'T'){
                                    posicion++; //~
                                    if(cadena1[posicion] != '~'){
                                        printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                        return -1;
                                    }
                                    posicion++; //:
                                    if(cadena1[posicion] != ':'){
                                        printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                        return -1;
                                    }
                                    posicion++; //~
                                    if(cadena1[posicion] != '~'){
                                        printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                        return -1;
                                    }
                                    posicion++;
                                    if(cadena1[posicion] == 'b' || cadena1[posicion] == 'B')
                                        f = 'b';
                                    else if(cadena1[posicion] == 'f' || cadena1[posicion] == 'F')
                                        f = 'f';
                                    else if(cadena1[posicion] == 'w' || cadena1[posicion] == 'W')
                                        f = 'w';
                                    else{
                                        printf("ERROR: El parametro fit solo puede tener como valor 'bf', 'ff' o 'wf'.\n");
                                        return 0;
                                    }
                                    posicion++;
                                    posicion++;
                                }else {
                                    printf("ERROR: Parametro no identificado.\n");
                                    condicion = false;
                                }
                            }else {
                                printf("ERROR: Parametro no identificado.\n");
                                condicion = false;
                            }
                        }else if(cadena1[posicion] == 'd' || cadena1[posicion] == 'D'){
                            posicion++;
                            if(cadena1[posicion] == 'e' || cadena1[posicion] == 'E'){
                                posicion++;
                                if(cadena1[posicion] == 'l' || cadena1[posicion] == 'L'){
                                    posicion++;
                                    if(cadena1[posicion] == 'e' || cadena1[posicion] == 'E'){
                                        posicion++;
                                        if(cadena1[posicion] == 't' || cadena1[posicion] == 'T'){
                                            posicion++;
                                            if(cadena1[posicion] == 'e' || cadena1[posicion] == 'E'){
                                                posicion++; //~
                                                if(cadena1[posicion] != '~'){
                                                    printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                                    return -1;
                                                }
                                                posicion++; //:
                                                if(cadena1[posicion] != ':'){
                                                    printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                                    return -1;
                                                }
                                                posicion++; //~
                                                if(cadena1[posicion] != '~'){
                                                    printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                                    return -1;
                                                }
                                                posicion++;
                                                if(cadena1[posicion] == 'f' || cadena1[posicion] == 'F'){
                                                    posicion++;
                                                    if(cadena1[posicion] == 'a' || cadena1[posicion] == 'A'){
                                                        posicion++;
                                                        if(cadena1[posicion] == 's' || cadena1[posicion] == 'S'){
                                                            posicion++;
                                                            if(cadena1[posicion] == 't' || cadena1[posicion] == 'T'){
                                                                d = 'a';
                                                                posicion++;
                                                            } else{
                                                                printf("ERROR: El parametro delete solo puede tener valores 'fast' o 'full'.\n");
                                                                return -1;
                                                            }
                                                        } else{
                                                            printf("ERROR: El parametro delete solo puede tener valores 'fast' o 'full'.\n");
                                                            return -1;
                                                        }
                                                    } else if(cadena1[posicion] == 'u' || cadena1[posicion] == 'U'){
                                                        posicion++;
                                                        if(cadena1[posicion] == 'l' || cadena1[posicion] == 'L'){
                                                            posicion++;
                                                            if(cadena1[posicion] == 'l' || cadena1[posicion] == 'L'){
                                                                d = 'u';
                                                                posicion++;
                                                            } else{
                                                                printf("ERROR: El parametro delete solo puede tener valores 'fast' o 'full'.\n");
                                                                return -1;
                                                            }
                                                        } else{
                                                            printf("ERROR: El parametro delete solo puede tener valores 'fast' o 'full'.\n");
                                                            return -1;
                                                        }
                                                    } else{
                                                        printf("ERROR: El parametro delete solo puede tener valores 'fast' o 'full'.\n");
                                                        return -1;
                                                    }
                                                } else{
                                                    printf("ERROR: El parametro delete solo puede tener valores 'fast' o 'full'.\n");
                                                    return -1;
                                                }
                                            } else {
                                                printf("ERROR: Parametro no identificado.\n");
                                                condicion = false;
                                            }
                                        } else {
                                            printf("ERROR: Parametro no identificado.\n");
                                            condicion = false;
                                        }
                                    } else {
                                        printf("ERROR: Parametro no identificado.\n");
                                        condicion = false;
                                    }
                                } else {
                                    printf("ERROR: Parametro no identificado.\n");
                                    condicion = false;
                                }
                            } else {
                                printf("ERROR: Parametro no identificado.\n");
                                condicion = false;
                            }
                        } else if(cadena1[posicion] == 'n' || cadena1[posicion] == 'N'){
                            posicion++;
                            if(cadena1[posicion] == 'a' || cadena1[posicion] == 'A'){
                                posicion++;
                                if(cadena1[posicion] == 'm' || cadena1[posicion] == 'M'){
                                    posicion++;
                                    if(cadena1[posicion] == 'e' || cadena1[posicion] == 'E'){
                                        posicion++; //~
                                        if(cadena1[posicion] != '~'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++; //:
                                        if(cadena1[posicion] != ':'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++; //~
                                        if(cadena1[posicion] != '~'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++;
                                        i = 0;
                                        if(cadena1[posicion] == '"'){
                                            posicion++;
                                            while(cadena1[posicion] != '"'){
                                                par2[i] = cadena1[posicion];
                                                i++;
                                                posicion++;
                                            }
                                        } else {
                                            while(cadena1[posicion] != ' ' && cadena1[posicion] != '\0' && cadena1[posicion] != '\n'){
                                                par2[i] = cadena1[posicion];
                                                i++;
                                                posicion++;
                                            }
                                        }
                                        par2[i] = '\0';
                                        posicion++;
                                    } else{
                                        printf("ERROR: Parametro no identificado.\n");
                                        condicion = false;
                                    }
                                } else{
                                    printf("ERROR: Parametro no identificado.\n");
                                    condicion = false;
                                }
                            } else{
                                printf("ERROR: Parametro no identificado.\n");
                                condicion = false;
                            }
                        } else if(cadena1[posicion] == 'a' || cadena1[posicion] == 'A'){
                                posicion++;
                                if(cadena1[posicion] == 'd' || cadena1[posicion] == 'D'){
                                    posicion++;
                                    if(cadena1[posicion] == 'd' || cadena1[posicion] == 'D'){
                                        posicion++; //~
                                        if(cadena1[posicion] != '~'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++; //:
                                        if(cadena1[posicion] != ':'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++; //~
                                        if(cadena1[posicion] != '~'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++;
                                        a = -1996;
                                        if(cadena1[posicion] == '-'){
                                            a = -1;
                                            posicion++;
                                        }
                                        while(cadena1[posicion] != ' ' && cadena1[posicion] != '\0' && cadena1[posicion] != '\r' && cadena1[posicion] != '\c' && cadena1[posicion] != '\n'){
                                            if(a == -1996)
                                                a = cadena1[posicion] - '0';
                                            else if(a == -1)
                                                a = a * (cadena1[posicion] - '0');
                                            else if(a < 0)
                                                a = a * 10 - (cadena1[posicion] - '0');
                                            else
                                                a = a * 10 + (cadena1[posicion] - '0');
                                            posicion++;
                                        }
                                        posicion++;
                                    } else{
                                        printf("ERROR: Parametro no identificado.\n");
                                        condicion = false;
                                    }
                                } else {
                                    printf("ERROR: Parametro no identificado.\n");
                                    condicion = false;
                                }
                        } else if(cadena1[posicion] == '#'){
                            while(cadena1[posicion] != '\n' && cadena1[posicion] != '\0')
                                posicion++;
                        }else {
                            printf("ERROR: Parametro no identificado.\n");
                            condicion = false;
                        }
                    }else{
                        printf("%c\n", cadena1[posicion]);
                        posicion++;
                    }
                }
                if(condicion && par1[0] != '\0') return fdisk(j, u, par1, t, f, d, par2, a);
                else {
                    printf("ERROR: Falta por lo menos un parametro obligatorio.\n");
                    return -1;
                }
            }else{
                condicion = true;
                for(posicion = 0; posicion < 5; posicion++){
                    if(cadena1[posicion] != amo[posicion] && cadena1[posicion] != amo[posicion] - 32){
                        condicion = false;
                        break;
                    }
                    condicion = true;
                }
                if(condicion){
                    par1[0] = '\0';
                    par2[0] = '\0';
                    while(cadena1[posicion] != '\0' && cadena1[posicion] != '\n'){
                        if(cadena1[posicion] == '#'){
                            while(cadena1[posicion] != '\n' && cadena1[posicion] != '\0')
                                posicion++;
                        }else if(cadena1[posicion] == 32 || cadena1[posicion] == '\n' || cadena1[posicion] == '\r'){
                            posicion++;
                        }else if(cadena1[posicion] == 45){
                            posicion++;
                            if(cadena1[posicion] == 'P' || cadena1[posicion] == 'p'){
                                posicion++;
                                if(cadena1[posicion] == 'A' || cadena1[posicion] == 'a'){
                                    posicion++;
                                    if(cadena1[posicion] == 'T' || cadena1[posicion] == 't'){
                                        posicion++;
                                        if(cadena1[posicion] == 'H' || cadena1[posicion] == 'h'){
                                            posicion++; //~
                                            if(cadena1[posicion] != '~'){
                                                printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                                return -1;
                                            }
                                            posicion++; //:
                                            if(cadena1[posicion] != ':'){
                                                printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                                return -1;
                                            }
                                            posicion++; //~
                                            if(cadena1[posicion] != '~'){
                                                printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                                return -1;
                                            }
                                            posicion++;
                                            i = 0;
                                            if(cadena1[posicion] == '"'){
                                                posicion++;
                                                while(cadena1[posicion] != '"'){
                                                    par1[i] = cadena1[posicion];
                                                    i++;
                                                    posicion++;
                                                }
                                            }else {
                                                while(cadena1[posicion] != ' ' && cadena1[posicion] != '\0' && cadena1[posicion] != '\n'){
                                                    par1[i] = cadena1[posicion];
                                                    i++;
                                                    posicion++;
                                                }
                                            }
                                            par1[i] = '\0';
                                            FILE * f = fopen(par1, "r");
                                            if(!f){
                                                printf("ERROR: No existe el disco especificado.\n");
                                                return -1;
                                            }
                                            fclose(f);
                                            posicion++;
                                        }else {
                                            printf("ERROR: Parametro no identificado.\n");
                                            condicion = false;
                                        }
                                    }else {
                                        printf("ERROR: Parametro no identificado.\n");
                                        condicion = false;
                                    }
                                }else {
                                    printf("ERROR: Parametro no identificado.\n");
                                    condicion = false;
                                }
                            } else if(cadena1[posicion] == 'N' || cadena1[posicion] == 'n'){
                                posicion++;
                                if(cadena1[posicion] == 'a' || cadena1[posicion] == 'A'){
                                    posicion++;
                                    if(cadena1[posicion] == 'M' || cadena1[posicion] == 'm'){
                                        posicion++;
                                        if(cadena1[posicion] == 'e' || cadena1[posicion] == 'E'){
                                            posicion++; //~
                                            if(cadena1[posicion] != '~'){
                                                printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                                return -1;
                                            }
                                            posicion++; //:
                                            if(cadena1[posicion] != ':'){
                                                printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                                return -1;
                                            }
                                            posicion++; //~
                                            if(cadena1[posicion] != '~'){
                                                printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                                return -1;
                                            }
                                            posicion++;
                                            i = 0;
                                            if(cadena1[posicion] == '"'){
                                                posicion++;
                                                while(cadena1[posicion] != '"'){
                                                    par2[i] = cadena1[posicion];
                                                    i++;
                                                    posicion++;
                                                }
                                            }else {
                                                while(cadena1[posicion] != ' ' && cadena1[posicion] != '\0' && cadena1[posicion] != '\n'){
                                                    par2[i] = cadena1[posicion];
                                                    i++;
                                                    posicion++;
                                                }
                                            }
                                            par2[i] = '\0';
                                            posicion++;
                                        }else{
                                            printf("ERROR: Parametro no identificado.\n");
                                            condicion = false;
                                        }
                                    }else{
                                        printf("ERROR: Parametro no identificado.\n");
                                        condicion = false;
                                    }
                                }else {
                                    printf("ERROR: Parametro no identificado.\n");
                                    condicion = false;
                                }
                            } else {
                                printf("ERROR: Parametro no identificado.\n");
                                condicion = false;
                            }
                        }else if(cadena1[posicion] == '#'){
                            while(cadena1[posicion] != '\n' && cadena1[posicion] != '\0')
                                posicion++;
                        }else {
                            printf("%c\n", cadena1[posicion]);
                            posicion++;
                        }
                    }
                    if(condicion && par1[0] != '\0' && par2[0] != '\0') return mount(par1, par2);
                    else {
                        printf("ERROR: Falta por lo menos un parametro obligatorio.\n");
                        return -1;
                    }
                }else{
                    condicion = true;
                    for(posicion = 0; posicion < 7; posicion++){
                        if(cadena1[posicion] != aun[posicion] && cadena1[posicion] != aun[posicion] - 32){
                            condicion = false;
                            break;
                        }
                        condicion = true;
                    }
                    if(condicion){
                        id[0] = '\0';
                        while(cadena1[posicion] != '\0' && cadena1[posicion] != '\n'){
                            if(cadena1[posicion] == '#'){
                                while(cadena1[posicion] != '\n' && cadena1[posicion] != '\0')
                                    posicion++;
                            }else if(cadena1[posicion] == 32 || cadena1[posicion] == '\n' || cadena1[posicion] == '\r'){
                                posicion++;
                            }else if(cadena1[posicion] == 45){
                                posicion++;
                                if(cadena1[posicion] == 'i' || cadena1[posicion] == 'I'){
                                    posicion++;
                                    if(cadena1[posicion] == 'd' || cadena1[posicion] == 'D'){
                                        posicion++; //~
                                        if(cadena1[posicion] != '~'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++; //:
                                        if(cadena1[posicion] != ':'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++; //~
                                        if(cadena1[posicion] != '~'){
                                            printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                            return -1;
                                        }
                                        posicion++;
                                        for(i = 0; i < 4; i++) id[i] = cadena1[posicion++];
                                        i++;
                                        id[i] = '\0';
                                        posicion++;
                                    }else {
                                        printf("ERROR: Parametro no identificado.\n");
                                        condicion = false;
                                    }
                                }else {
                                    printf("ERROR: Parametro no identificado.\n");
                                    condicion = false;
                                }
                            }
                        }
                        if(condicion && id[0] != '\0') return unmount(id);
                        else {
                            printf("ERROR: Falta por lo menos un parametro obligatorio.\n");
                            return -1;
                        }
                    }else{
                        condicion = true;
                        for(posicion = 0; posicion < 3; posicion++){
                            if(cadena1[posicion] != are[posicion] && cadena1[posicion] != are[posicion] - 32){
                                condicion = false;
                                break;
                            }
                            condicion = true;
                        }
                        if(condicion){
                            par2[0] = '\0';
                            par1[0] = '\0';
                            ruta[0] = '\0';
                            id[0] = '\0';
                            while(cadena1[posicion] != '\0' && cadena1[posicion] != '\n'){
                                if(cadena1[posicion] == '#'){
                                    while(cadena1[posicion] != '\n' && cadena1[posicion] != '\0')
                                        posicion++;
                                }else if(cadena1[posicion] == 32 || cadena1[posicion] == '\n' || cadena1[posicion] == '\r'){
                                    posicion++;
                                }else if(cadena1[posicion] == 45){
                                    posicion++;
                                    if(cadena1[posicion] == 'N' || cadena1[posicion] == 'n'){
                                        posicion++;
                                        if(cadena1[posicion] == 'a' || cadena1[posicion] == 'A'){
                                            posicion++;
                                            if(cadena1[posicion] == 'M' || cadena1[posicion] == 'm'){
                                                posicion++;
                                                if(cadena1[posicion] == 'e' || cadena1[posicion] == 'E'){
                                                    posicion++; //~
                                                    if(cadena1[posicion] != '~'){
                                                        printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                                        return -1;
                                                    }
                                                    posicion++; //:
                                                    if(cadena1[posicion] != ':'){
                                                        printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                                        return -1;
                                                    }
                                                    posicion++; //~
                                                    if(cadena1[posicion] != '~'){
                                                        printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                                        return -1;
                                                    }
                                                    posicion++;
                                                    i = 0;
                                                    while(cadena1[posicion] != ' ' && cadena1[posicion] != '\0' && cadena1[posicion] != '\c' && cadena1[posicion] != '\r' && cadena1[posicion] != '\n'){
                                                        par2[i] = cadena1[posicion];
                                                        i++;
                                                        posicion++;
                                                    }
                                                    par2[i] = '\0';
                                                    posicion++;
                                                }else{
                                                    printf("ERROR: Parametro no identificado.\n");
                                                    condicion = false;
                                                }
                                            }else{
                                                printf("ERROR: Parametro no identificado.\n");
                                                condicion = false;
                                            }
                                        }else {
                                            printf("ERROR: Parametro no identificado.\n");
                                            condicion = false;
                                        }
                                    } else if(cadena1[posicion] == 'p' || cadena1[posicion] == 'P'){
                                        posicion++;
                                        if(cadena1[posicion] == 'a' || cadena1[posicion] == 'A'){
                                            posicion++;
                                            if(cadena1[posicion] == 't' || cadena1[posicion] == 'T'){
                                                posicion++;
                                                if(cadena1[posicion] == 'h' || cadena1[posicion] == 'H'){
                                                    posicion++; //~
                                                    if(cadena1[posicion] != '~'){
                                                        printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                                        return -1;
                                                    }
                                                    posicion++; //:
                                                    if(cadena1[posicion] != ':'){
                                                        printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                                        return -1;
                                                    }
                                                    posicion++; //~
                                                    if(cadena1[posicion] != '~'){
                                                        printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                                        return -1;
                                                    }
                                                    posicion++;
                                                    par1[0] = 'm'; par1[1] = 'k'; par1[2] = 'd'; par1[3] = 'i'; par1[4] = 'r'; par1[5] = ' '; par1[6] = '"';
                                                    if(cadena1[posicion] == '"'){
                                                        i = 7;
                                                        posicion++;
                                                        while(cadena1[posicion] != '"'){
                                                            if(cadena1[posicion] == '/' && i > 7){
                                                                par1[i] = '"';
                                                                par1[i + 1] = '\0';
                                                                system(par1);
                                                            }
                                                            par1[i] = cadena1[posicion];
                                                            i++;
                                                            posicion++;
                                                        }
                                                        par1[i] = '\0';
                                                        i = 0;
                                                        while(par1[i] != '\0'){
                                                            par1[i] = par1[i + 7];
                                                            i++;
                                                        }
                                                    }else {
                                                        i = 6;
                                                        while(cadena1[posicion] != ' ' && cadena1[posicion] != '\0' && cadena1[posicion] != '\n'){
                                                            if(cadena1[posicion] == '/' && i > 6){
                                                                par1[i] = '\0';
                                                                system(par1);
                                                            }
                                                            par1[i] = cadena1[posicion];
                                                            i++;
                                                            posicion++;
                                                        }
                                                        par1[i] = '\0';
                                                        i = 0;
                                                        while(par1[i] != '\0'){
                                                            par1[i] = par1[i + 6];
                                                            i++;
                                                        }
                                                    }
                                                    par1[i - 1] = '\0';
                                                    posicion++;
                                                }else{
                                                    printf("ERROR: Parametro no identificado.\n");
                                                    condicion = false;
                                                }
                                            }else{
                                                printf("ERROR: Parametro no identificado.\n");
                                                condicion = false;
                                            }
                                        }else {
                                            printf("ERROR: Parametro no identificado.\n");
                                            condicion = false;
                                        }
                                    } else if(cadena1[posicion] == 'i' || cadena1[posicion] == 'I'){
                                        posicion++;
                                        if(cadena1[posicion] == 'd' || cadena1[posicion] == 'D'){
                                            posicion++; //~
                                            if(cadena1[posicion] != '~'){
                                                printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                                return -1;
                                            }
                                            posicion++; //:
                                            if(cadena1[posicion] != ':'){
                                                printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                                return -1;
                                            }
                                            posicion++; //~
                                            if(cadena1[posicion] != '~'){
                                                printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                                return -1;
                                            }
                                            posicion++;
                                            i = 0;
                                            if(cadena1[posicion] == '"'){
                                                posicion++;
                                                while(cadena1[posicion] != '"'){
                                                    id[i] = cadena1[posicion];
                                                    i++;
                                                    posicion++;
                                                }
                                            }else {
                                                while(cadena1[posicion] != ' ' && cadena1[posicion] != '\0' && cadena1[posicion] != '\n'){
                                                    id[i] = cadena1[posicion];
                                                    i++;
                                                    posicion++;
                                                }
                                            }
                                            id[i] = '\0';
                                            posicion++;
                                        }else {
                                            printf("ERROR: Parametro no identificado.\n");
                                            condicion = false;
                                        }
                                    } else if(cadena1[posicion] == 'r' || cadena1[posicion] == 'R'){
                                        posicion++;
                                        if(cadena1[posicion] == 'u' || cadena1[posicion] == 'U'){
                                            posicion++;
                                            if(cadena1[posicion] == 't' || cadena1[posicion] == 'T'){
                                                posicion++;
                                                if(cadena1[posicion] == 'a' || cadena1[posicion] == 'A'){
                                                    posicion++; //~
                                                    if(cadena1[posicion] != '~'){
                                                        printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                                        return -1;
                                                    }
                                                    posicion++; //:
                                                    if(cadena1[posicion] != ':'){
                                                        printf("ERROR: No se reconoció el caracter '%c', se esperaba ':'.", cadena1[posicion]);
                                                        return -1;
                                                    }
                                                    posicion++; //~
                                                    if(cadena1[posicion] != '~'){
                                                        printf("ERROR: No se reconoció el caracter '%c', se esperaba '~'.", cadena1[posicion]);
                                                        return -1;
                                                    }
                                                    posicion++;
                                                    ruta[0] = 'm'; ruta[1] = 'k'; ruta[2] = 'd'; ruta[3] = 'i'; ruta[4] = 'r'; ruta[5] = ' '; ruta[6] = '"';
                                                    if(cadena1[posicion] == '"'){
                                                        i = 7;
                                                        posicion++;
                                                        while(cadena1[posicion] != '"'){
                                                            if(cadena1[posicion] == '/' && i > 7){
                                                                ruta[i] = '"';
                                                                ruta[i + 1] = '\0';
                                                                //system(ruta);
                                                            }
                                                            ruta[i] = cadena1[posicion];
                                                            i++;
                                                            posicion++;
                                                        }
                                                        ruta[i] = '\0';
                                                        i = 0;
                                                        while(ruta[i] != '\0'){
                                                            ruta[i] = ruta[i + 7];
                                                            i++;
                                                        }
                                                    }else {
                                                        i = 6;
                                                        while(cadena1[posicion] != ' ' && cadena1[posicion] != '\0' && cadena1[posicion] != '\n'){
                                                            if(cadena1[posicion] == '/' && i > 6){
                                                                ruta[i] = '\0';
                                                                //system(ruta);
                                                            }
                                                            ruta[i] = cadena1[posicion];
                                                            i++;
                                                            posicion++;
                                                        }
                                                        ruta[i] = '\0';
                                                        i = 0;
                                                        while(ruta[i] != '\0'){
                                                            ruta[i] = ruta[i + 6];
                                                            i++;
                                                        }
                                                    }
                                                    ruta[i - 1] = '\0';
                                                    posicion++;
                                                }else{
                                                    printf("ERROR: Parametro no identificado.\n");
                                                    condicion = false;
                                                }
                                            }else{
                                                printf("ERROR: Parametro no identificado.\n");
                                                condicion = false;
                                            }
                                        }else{
                                            printf("ERROR: Parametro no identificado.\n");
                                            condicion = false;
                                        }
                                    }else{
                                        printf("ERROR: Parametro no identificado.\n");
                                        condicion = false;
                                    }
                                }else if(cadena1[posicion] == '#'){
                                    while(cadena1[posicion] != '\n' && cadena1[posicion] != '\0')
                                        posicion++;
                                }else {
                                    printf("%c\n", cadena1[posicion]);
                                    posicion++;
                                }
                            }
                            if(condicion && par2[0] != '\0' && par1[0] != '\0' && id[0] != '\0') return rep(par2, par1, id);
                            else{
                                printf("ERROR: Falta por lo menos un parametro obligatorio.\n");
                                return -1;
                            }
                        }else if(cadena1[posicion] == '#') while(cadena1[posicion] != '\n') posicion++;
                        else{
                            printf("ERROR: Comando no identificado.\n");
                            condicion = true;
                            return menu();
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int mkdisk(char path[200], char fit, int tamano){
    int iterador;
    FILE * disco;
    disco = fopen(path, "r");
    if(disco != NULL){
        printf("El disco especificado ya existe.\n");
        fclose(disco);
        return -1;
    }
    disco = fopen(path, "wb+");
    if(disco == NULL){
        printf("No se ha podido crear el disco.\n");
        return -1;
    }
    char nulo[1024];
    for(iterador = 0; iterador < 1024; iterador++) nulo[iterador] = '\0';
    fseek(disco, 0, SEEK_SET);
    for(iterador = 0; iterador < tamano; iterador++)
        fwrite(&nulo, 1, 1024, disco);
    mbr mbr_;
    limpiar_mbr(&mbr_);
    mbr_.mbr_tamano = tamano * 1024;
    mbr_.disk_fit = fit;
    fseek(disco, 0, SEEK_SET);
    fwrite(&mbr_, sizeof(mbr), 1, disco);
    fclose(disco);
    printf("Disco creado exitosamente.\n");
    return 0;
}

int rmdisk(char path[200]){
    int iterador = 0;
    char op[2] = {'\0', '\0'};
    scanf("%s", op);
    boolean bandera = true, dicequesi = false;
    char c[4] = {'s', 'S', 'n', 'N'};
    while(bandera){
        if(iterador == 4){
            printf("Ingrese una opción válida: ");
            op[0] = '\0';
            op[1] = '\0';
            scanf("%s", op);
            iterador = 0;
        }
        if(c[iterador] == op[0]){
            bandera = false;
            if(iterador < 2) dicequesi = true;
            break;
        }
        iterador++;
    }
    if(dicequesi){
        if(!remove(path)) printf("Disco eliminado exitosamente.\n");
        else printf("No se ha podido eliminar el disco.\n");
    }else printf("Entendido. No se ha eliminado el disco.\n");
    return 0;
}

int fdisk(int size, char unit, char path[200], char type, char fit, char del, char name[16], int add){
    FILE *disco;
    disco = fopen(path, "rb+");
    if(disco == NULL){
        printf("No se ha encontrado el disco en la dirección especificada.\n");
        return -1;
    }
    mbr mbr_;
    limpiar_mbr(&mbr_);
    fseek(disco, 0, SEEK_SET);
    fread(&mbr_, sizeof(mbr), 1, disco);
    fclose(disco);
    part nueva, primera, segunda, tercera;
    if(size == add && size == -1996){  /* ES UN DELETE */
        printf("Esta seguro que desea eliminar '%s'? [s/n]: ", name);
        int iterador = 0;
        char op[2] = {'\0', '\0'};
        scanf("%s", op);
        boolean bandera = true, dicequesi = false;
        char c[4] = {'s', 'S', 'n', 'N'};
        while(bandera){
            if(iterador == 4){
                printf("Ingrese una opción válida: ");
                op[0] = '\0';
                op[1] = '\0';
                scanf("%s", op);
                iterador = 0;
            }
            if(c[iterador] == op[0]){
                bandera = false;
                if(iterador < 2) dicequesi = true;
                break;
            }
            iterador++;
        }
        if(!dicequesi){
            printf("Entendido. No se ha eliminado la particion.\n");
            return 0;
        }
        int pos = 0, end = 0;
        if(!strcmp(mbr_.mbr_partition_1.part_name, name)){
            pos = mbr_.mbr_partition_1.part_start;
            end = pos + mbr_.mbr_partition_1.part_size;
            mbr_.mbr_partition_1 = mbr_.mbr_partition_4;
        }else if(!strcmp(mbr_.mbr_partition_2.part_name, name)){
            pos = mbr_.mbr_partition_2.part_start;
            end = pos + mbr_.mbr_partition_2.part_size;
            mbr_.mbr_partition_2 = mbr_.mbr_partition_4;
        }else if(!strcmp(mbr_.mbr_partition_3.part_name, name)){
            pos = mbr_.mbr_partition_3.part_start;
            end = pos + mbr_.mbr_partition_3.part_size;
            mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
        }else if(!strcmp(mbr_.mbr_partition_4.part_name, name)){
            pos = mbr_.mbr_partition_4.part_start;
            end = pos + mbr_.mbr_partition_4.part_size;
        }else {
            printf("No existe una particion con ese nombre en el disco especificado.\n");
            return -1;
        }
        limpiar_part(&mbr_.mbr_partition_4);
        if(del == 'u' || del == 'U'){
            del = '\0';
            disco = fopen(path, "rb+");
            fseek(disco, pos, SEEK_SET);
            for(int i = pos; i < end + 1; i++){
                fwrite(&del, sizeof(mbr), 1, disco);
            }
            fclose(disco);
        }
        if(mbr_.mbr_partition_1.part_status == '1' && mbr_.mbr_partition_2.part_status == '1' && mbr_.mbr_partition_3.part_status == '1' && mbr_.mbr_partition_4.part_status == '1'){
            if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                nueva = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                mbr_.mbr_partition_4 = nueva;
            }
            if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                nueva = mbr_.mbr_partition_2;
                mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = nueva;
            }
            if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_2.part_start){
                nueva = mbr_.mbr_partition_1;
                mbr_.mbr_partition_1 = mbr_.mbr_partition_2;
                mbr_.mbr_partition_2 = nueva;
            }
            if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                nueva = mbr_.mbr_partition_2;
                mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = nueva;
            }
            if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                nueva = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                mbr_.mbr_partition_4 = nueva;
            }
            if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                nueva = mbr_.mbr_partition_2;
                mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = nueva;
            }
        }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_1.part_status == '1'){
            if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                nueva = mbr_.mbr_partition_2;
                mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = nueva;
            }
            if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_2.part_start){
                nueva = mbr_.mbr_partition_1;
                mbr_.mbr_partition_1 = mbr_.mbr_partition_2;
                mbr_.mbr_partition_2 = nueva;
            }
            if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                nueva = mbr_.mbr_partition_2;
                mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = nueva;
            }
        }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_1.part_status == '1'){
            if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_4.part_start){
                nueva = mbr_.mbr_partition_2;
                mbr_.mbr_partition_2 = mbr_.mbr_partition_4;
                mbr_.mbr_partition_4 = nueva;
            }
            if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_2.part_start){
                nueva = mbr_.mbr_partition_1;
                mbr_.mbr_partition_1 = mbr_.mbr_partition_2;
                mbr_.mbr_partition_2 = nueva;
            }
            if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_4.part_start){
                nueva = mbr_.mbr_partition_2;
                mbr_.mbr_partition_2 = mbr_.mbr_partition_4;
                mbr_.mbr_partition_4 = nueva;
            }
        }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_3.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_1.part_status == '1'){
            if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                nueva = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                mbr_.mbr_partition_4 = nueva;
            }
            if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_3.part_start){
                nueva = mbr_.mbr_partition_1;
                mbr_.mbr_partition_1 = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = nueva;
            }
            if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                nueva = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                mbr_.mbr_partition_4 = nueva;
            }
        }else if(mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_3.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_2.part_status == '1'){
            if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                nueva = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                mbr_.mbr_partition_4 = nueva;
            }
            if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                nueva = mbr_.mbr_partition_2;
                mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = nueva;
            }
            if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                nueva = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                mbr_.mbr_partition_4 = nueva;
            }
        }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_1.part_status == '1'){
            if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_2.part_start){
                nueva = mbr_.mbr_partition_1;
                mbr_.mbr_partition_1 = mbr_.mbr_partition_2;
                mbr_.mbr_partition_2 = nueva;
            }
        }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_1.part_status == '1'){
            if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_3.part_start){
                nueva = mbr_.mbr_partition_1;
                mbr_.mbr_partition_1 = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = nueva;
            }
        }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_1.part_status == '1'){
            if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_4.part_start){
                nueva = mbr_.mbr_partition_1;
                mbr_.mbr_partition_1 = mbr_.mbr_partition_4;
                mbr_.mbr_partition_4 = nueva;
            }
        }else if(mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_2.part_status == '1'){
            if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                nueva = mbr_.mbr_partition_2;
                mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = nueva;
            }
        }else if(mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_2.part_status == '1'){
            if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_4.part_start){
                nueva = mbr_.mbr_partition_2;
                mbr_.mbr_partition_2 = mbr_.mbr_partition_4;
                mbr_.mbr_partition_4 = nueva;
            }
        }else if(mbr_.mbr_partition_3.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_3.part_status == '1'){
            if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                nueva = mbr_.mbr_partition_3;
                mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                mbr_.mbr_partition_4 = nueva;
            }
        }else{
            printf("El disco se ha quedado sin particiones.\n");
        }
        disco = fopen(path, "rb+");
        fseek(disco, 0, SEEK_SET);
        fwrite(&mbr_, sizeof(mbr), 1, disco);
        fclose(disco);
        //imprimir_mbr(mbr_);
        printf("Particion eliminada exitosamente.\n");
    }else if(size == -1996){   /* ES UN ADD */
        int libre = 0;
        if(unit == 'k') add = add * 1024;
        else if(unit == 'm') add = add * 1024 * 1024;
        if(add < 0){
            add = add * -1;
            if(!strcmp(mbr_.mbr_partition_1.part_name, name)){
                if(mbr_.mbr_partition_1.part_size > add){
                    mbr_.mbr_partition_1.part_size = mbr_.mbr_partition_1.part_size - add;
                }else{
                    printf("El tamano de la particion es menor de lo que se le quiere reducir con el parametro add.\n");
                    return -1;
                }
            }else if(!strcmp(mbr_.mbr_partition_2.part_name, name)){
                if(mbr_.mbr_partition_2.part_size > add){
                    mbr_.mbr_partition_2.part_size = mbr_.mbr_partition_2.part_size - add;
                }else{
                    printf("El tamano de la particion es menor de lo que se le quiere reducir con el parametro add.\n");
                    return -1;
                }
            }else if(!strcmp(mbr_.mbr_partition_3.part_name, name)){
                if(mbr_.mbr_partition_3.part_size > add){
                    mbr_.mbr_partition_3.part_size = mbr_.mbr_partition_3.part_size - add;
                }else{
                    printf("El tamano de la particion es menor de lo que se le quiere reducir con el parametro add.\n");
                    return -1;
                }
            }else if(!strcmp(mbr_.mbr_partition_4.part_name, name)){
                if(mbr_.mbr_partition_4.part_size > add){
                    mbr_.mbr_partition_4.part_size = mbr_.mbr_partition_4.part_size - add;
                }else{
                    printf("El tamano de la particion es menor de lo que se le quiere reducir con el parametro add.\n");
                    return -1;
                }
            }else {
                printf("No existe una particion con ese nombre en el disco especificado.\n");
                return -1;
            }
            disco = fopen(path, "rb+");
            fseek(disco, 0, SEEK_SET);
            fwrite(&mbr_, sizeof(mbr), 1, disco);
            fclose(disco);
            //imprimir_mbr(mbr_);
            printf("Se ha quitado espacio exitosamente.\n");
        }else if (add == 0){
            printf("El valor del parametro add es 0.\n");
            return -1;
        }else{
            if(!strcmp(mbr_.mbr_partition_1.part_name, name)){
                libre = mbr_.mbr_partition_2.part_start - (mbr_.mbr_partition_1.part_start + mbr_.mbr_partition_1.part_size);
                if(libre >= add){
                    mbr_.mbr_partition_1.part_size = mbr_.mbr_partition_1.part_size + add;
                }else{
                    printf("El tamano disponible es menor de lo que se le quiere aumentar con el parametro add.\n");
                    return -1;
                }
            }else if(!strcmp(mbr_.mbr_partition_2.part_name, name)){
                libre = mbr_.mbr_partition_3.part_start - (mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size);
                if(libre >= add){
                    mbr_.mbr_partition_2.part_size = mbr_.mbr_partition_2.part_size + add;
                }else{
                    printf("El tamano disponible es menor de lo que se le quiere aumentar con el parametro add.\n");
                    return -1;
                }
            }else if(!strcmp(mbr_.mbr_partition_3.part_name, name)){
                libre = mbr_.mbr_partition_4.part_start - (mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size);
                if(libre >= add){
                    mbr_.mbr_partition_3.part_size = mbr_.mbr_partition_3.part_size + add;
                }else{
                    printf("El tamano disponible es menor de lo que se le quiere aumentar con el parametro add.\n");
                    return -1;
                }
            }else if(!strcmp(mbr_.mbr_partition_4.part_name, name)){
                libre = mbr_.mbr_tamano - (mbr_.mbr_partition_1.part_start + mbr_.mbr_partition_1.part_size);
                if(libre >= add){
                    mbr_.mbr_partition_1.part_size = mbr_.mbr_partition_1.part_size + add;
                }else{
                    printf("El tamano disponible es menor de lo que se le quiere aumentar con el parametro add.\n");
                    return -1;
                }
            }else {
                printf("No existe una particion con ese nombre en el disco especificado.\n");
                return -1;
            }
            disco = fopen(path, "rb+");
            fseek(disco, 0, SEEK_SET);
            fwrite(&mbr_, sizeof(mbr), 1, disco);
            fclose(disco);
            //imprimir_mbr(mbr_);
            printf("Se ha anadido espacio exitosamente.\n");
        }
    }else{                  /* ES UN CREAR */
        int libre;
        nueva.part_status = '1';
        nueva.part_fit = fit;
        nueva.part_type = type;
        for(libre = 0; libre < 16; libre++) nueva.part_name[libre] = name[libre];
        libre = 0;
        if(unit == 'k' || unit == 'K') size = size * 1024;
        else if(unit == 'm' || unit == 'M') size = size * 1024 * 1024;
        nueva.part_size = size;
        if(mbr_.disk_fit == 'f'){ //primer ajuste
            if(type != 'l' && type != 'L'){
                if(!strcmp(mbr_.mbr_partition_1.part_name, name) || !strcmp(mbr_.mbr_partition_2.part_name, name) || !strcmp(mbr_.mbr_partition_3.part_name, name) || !strcmp(mbr_.mbr_partition_4.part_name, name)){
                    printf("Ya existe una particion con ese nombre.\n");
                    return -1;
                }else if((type == 'e' || type == 'E') && (mbr_.mbr_partition_1.part_type == 'e' || mbr_.mbr_partition_1.part_type == 'E' || mbr_.mbr_partition_2.part_type == 'e' || mbr_.mbr_partition_2.part_type == 'E' || mbr_.mbr_partition_3.part_type == 'e' || mbr_.mbr_partition_3.part_type == 'E' || mbr_.mbr_partition_4.part_type == 'e' || mbr_.mbr_partition_4.part_type == 'E')){
                    printf("Ya existe una particion extendida.\n");
                    return -1;
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_2.part_status == '1'){
                    printf("Solo puede existir un total de 4 particiones primarias o 3 primarias y una extendida.\n");
                    return -1;
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_2.part_status == '0'){ /// todas libres
                    nueva.part_start = sizeof(mbr) + 1;
                    if(size >= (libre = (mbr_.mbr_tamano - sizeof(mbr)))){
                        printf("No hay suficiente espacio para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_1 = nueva;
                }else if(mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_3.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_3.part_status == '1'){ /////p1 libre
                    if(mbr_.mbr_partition_4.part_start > mbr_.mbr_partition_3.part_start && mbr_.mbr_partition_4.part_start > mbr_.mbr_partition_2.part_start){
                        tercera = mbr_.mbr_partition_4;
                        if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_2.part_start){
                            segunda = mbr_.mbr_partition_3;
                            primera = mbr_.mbr_partition_2;
                        }else{
                            segunda = mbr_.mbr_partition_2;
                            primera = mbr_.mbr_partition_3;
                        }
                    }else if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start && mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_2.part_start){
                        tercera = mbr_.mbr_partition_3;
                        if(mbr_.mbr_partition_4.part_start > mbr_.mbr_partition_2.part_start){
                            segunda = mbr_.mbr_partition_4;
                            primera = mbr_.mbr_partition_2;
                        }else{
                            segunda = mbr_.mbr_partition_2;
                            primera = mbr_.mbr_partition_4;
                        }
                    }else{
                        tercera = mbr_.mbr_partition_2;
                        if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                            segunda = mbr_.mbr_partition_3;
                            primera = mbr_.mbr_partition_4;
                        }else{
                            segunda = mbr_.mbr_partition_4;
                            primera = mbr_.mbr_partition_3;
                        }
                    }
                    if(size < (libre = primera.part_start - sizeof(mbr))){
                        nueva.part_start = sizeof(mbr) + 1;
                    }else if(size < (libre = segunda.part_start - (primera.part_start + primera.part_size))){
                        nueva.part_start = primera.part_start + primera.part_size + 1;
                    }else if(size < (libre = tercera.part_start - (segunda.part_start + segunda.part_size))){
                        nueva.part_start = segunda.part_start + segunda.part_size + 1;
                    }else if(size <= (libre = mbr_.mbr_tamano - (tercera.part_start + tercera.part_size))){
                        nueva.part_start = tercera.part_start + tercera.part_size + 1;
                    }else{
                        printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_1 = nueva;
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_3.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_3.part_status == '1'){ /////p2 libre
                    if(mbr_.mbr_partition_4.part_start > mbr_.mbr_partition_3.part_start && mbr_.mbr_partition_4.part_start > mbr_.mbr_partition_1.part_start){
                        tercera = mbr_.mbr_partition_4;
                        if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_1.part_start){
                            segunda = mbr_.mbr_partition_3;
                            primera = mbr_.mbr_partition_1;
                        }else{
                            segunda = mbr_.mbr_partition_1;
                            primera = mbr_.mbr_partition_3;
                        }
                    }else if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start && mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_1.part_start){
                        tercera = mbr_.mbr_partition_3;
                        if(mbr_.mbr_partition_4.part_start > mbr_.mbr_partition_1.part_start){
                            segunda = mbr_.mbr_partition_4;
                            primera = mbr_.mbr_partition_1;
                        }else{
                            segunda = mbr_.mbr_partition_1;
                            primera = mbr_.mbr_partition_4;
                        }
                    }else{
                        tercera = mbr_.mbr_partition_1;
                        if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                            segunda = mbr_.mbr_partition_3;
                            primera = mbr_.mbr_partition_4;
                        }else{
                            segunda = mbr_.mbr_partition_4;
                            primera = mbr_.mbr_partition_3;
                        }
                    }
                    if(size < (libre = primera.part_start - sizeof(mbr))){
                        nueva.part_start = sizeof(mbr) + 1;
                    }else if(size < (libre = segunda.part_start - (primera.part_start + primera.part_size))){
                        nueva.part_start = primera.part_start + primera.part_size + 1;
                    }else if(size < (libre = tercera.part_start - (segunda.part_start + segunda.part_size))){
                        nueva.part_start = segunda.part_start + segunda.part_size + 1;
                    }else if(size < (libre = mbr_.mbr_tamano - (tercera.part_start + tercera.part_size))){
                        nueva.part_start = tercera.part_start + tercera.part_size + 1;
                    }else{
                        printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_2 = nueva;
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_2.part_status == '1'){ /////p3 libre
                    if(mbr_.mbr_partition_4.part_start > mbr_.mbr_partition_2.part_start && mbr_.mbr_partition_4.part_start > mbr_.mbr_partition_1.part_start){
                        tercera = mbr_.mbr_partition_4;
                        if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_1.part_start){
                            segunda = mbr_.mbr_partition_2;
                            primera = mbr_.mbr_partition_1;
                        }else{
                            segunda = mbr_.mbr_partition_1;
                            primera = mbr_.mbr_partition_2;
                        }
                    }else if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_4.part_start && mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_1.part_start){
                        tercera = mbr_.mbr_partition_2;
                        if(mbr_.mbr_partition_4.part_start > mbr_.mbr_partition_1.part_start){
                            segunda = mbr_.mbr_partition_4;
                            primera = mbr_.mbr_partition_1;
                        }else{
                            segunda = mbr_.mbr_partition_1;
                            primera = mbr_.mbr_partition_4;
                        }
                    }else{
                        tercera = mbr_.mbr_partition_1;
                        if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_4.part_start){
                            segunda = mbr_.mbr_partition_2;
                            primera = mbr_.mbr_partition_4;
                        }else{
                            segunda = mbr_.mbr_partition_4;
                            primera = mbr_.mbr_partition_2;
                        }
                    }
                    if(size < (libre = primera.part_start - sizeof(mbr))){
                        nueva.part_start = sizeof(mbr) + 1;
                    }else if(size < (libre = segunda.part_start - (primera.part_start + primera.part_size))){
                        nueva.part_start = primera.part_start + primera.part_size + 1;
                    }else if(size < (libre = tercera.part_start - (segunda.part_start + segunda.part_size))){
                        nueva.part_start = segunda.part_start + segunda.part_size + 1;
                    }else if(size < (libre = mbr_.mbr_tamano - (tercera.part_start + tercera.part_size))){
                        nueva.part_start = tercera.part_start + tercera.part_size + 1;
                    }else{
                        printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_3 = nueva;
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_2.part_status == '1'){ /////p4 libre
                    if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_2.part_start && mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_1.part_start){
                        tercera = mbr_.mbr_partition_3;
                        if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_1.part_start){
                            segunda = mbr_.mbr_partition_2;
                            primera = mbr_.mbr_partition_1;
                        }else{
                            segunda = mbr_.mbr_partition_1;
                            primera = mbr_.mbr_partition_2;
                        }
                    }else if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start && mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_1.part_start){
                        tercera = mbr_.mbr_partition_2;
                        if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_1.part_start){
                            segunda = mbr_.mbr_partition_3;
                            primera = mbr_.mbr_partition_1;
                        }else{
                            segunda = mbr_.mbr_partition_1;
                            primera = mbr_.mbr_partition_3;
                        }
                    }else{
                        tercera = mbr_.mbr_partition_1;
                        if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                            segunda = mbr_.mbr_partition_2;
                            primera = mbr_.mbr_partition_3;
                        }else{
                            segunda = mbr_.mbr_partition_3;
                            primera = mbr_.mbr_partition_2;
                        }
                    }
                    if(size < (libre = primera.part_start - sizeof(mbr))){
                        nueva.part_start = sizeof(mbr) + 1;
                    }else if(size < (libre = segunda.part_start - (primera.part_start + primera.part_size))){
                        nueva.part_start = primera.part_start + primera.part_size + 1;
                    }else if(size < (libre = tercera.part_start - (segunda.part_start + segunda.part_size))){
                        nueva.part_start = segunda.part_start + segunda.part_size + 1;
                    }else if(size < (libre = mbr_.mbr_tamano - (tercera.part_start + tercera.part_size))){
                        nueva.part_start = tercera.part_start + tercera.part_size + 1;
                    }else{
                        printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_4 = nueva;
                }else if(mbr_.mbr_partition_3.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_4.part_status == '1'){ /////p1 & p2
                    if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                        primera = mbr_.mbr_partition_4;
                        segunda = mbr_.mbr_partition_3;
                    }else{
                        primera = mbr_.mbr_partition_3;
                        segunda = mbr_.mbr_partition_4;
                    }
                    if(size < (libre = primera.part_start - sizeof(mbr))){
                        nueva.part_start = sizeof(mbr) + 1;
                    }else if(size < (libre = segunda.part_start - (primera.part_start + primera.part_size))){
                        nueva.part_start = primera.part_start + primera.part_size + 1;
                    }else if(size < (libre = mbr_.mbr_tamano - (segunda.part_start + segunda.part_size))){
                        nueva.part_start = segunda.part_start + segunda.part_size + 1;
                    }else{
                        printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_1 = nueva;
                }else if(mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_4.part_status == '1'){ /////p1 & p3
                    if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_4.part_start){
                        primera = mbr_.mbr_partition_4;
                        segunda = mbr_.mbr_partition_2;
                    }else{
                        primera = mbr_.mbr_partition_2;
                        segunda = mbr_.mbr_partition_4;
                    }
                    if(size < (libre = primera.part_start - sizeof(mbr))){
                        nueva.part_start = sizeof(mbr) + 1;
                    }else if(size < (libre = segunda.part_start - (primera.part_start + primera.part_size))){
                        nueva.part_start = primera.part_start + primera.part_size + 1;
                    }else if(size < (libre = mbr_.mbr_tamano - (segunda.part_start + segunda.part_size))){
                        nueva.part_start = segunda.part_start + segunda.part_size + 1;
                    }else{
                        printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_1 = nueva;
                }else if(mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_3.part_status == '1'){ /////p1 & p4
                    if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                        primera = mbr_.mbr_partition_3;
                        segunda = mbr_.mbr_partition_2;
                    }else{
                        primera = mbr_.mbr_partition_2;
                        segunda = mbr_.mbr_partition_3;
                    }
                    if(size < (libre = primera.part_start - sizeof(mbr))){
                        nueva.part_start = sizeof(mbr) + 1;
                    }else if(size < (libre = segunda.part_start - (primera.part_start + primera.part_size))){
                        nueva.part_start = primera.part_start + primera.part_size + 1;
                    }else if(size < (libre = mbr_.mbr_tamano - (segunda.part_start + segunda.part_size))){
                        nueva.part_start = segunda.part_start + segunda.part_size + 1;
                    }else{
                        printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_1 = nueva;
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_1.part_status == '1'){ /////p2 & p3
                    if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_4.part_start){
                        primera = mbr_.mbr_partition_4;
                        segunda = mbr_.mbr_partition_1;
                    }else{
                        primera = mbr_.mbr_partition_1;
                        segunda = mbr_.mbr_partition_4;
                    }
                    if(size < (libre = primera.part_start - sizeof(mbr))){
                        nueva.part_start = sizeof(mbr) + 1;
                    }else if(size < (libre = segunda.part_start - (primera.part_start + primera.part_size))){
                        nueva.part_start = primera.part_start + primera.part_size + 1;
                    }else if(size < (libre = mbr_.mbr_tamano - (segunda.part_start + segunda.part_size))){
                        nueva.part_start = segunda.part_start + segunda.part_size + 1;
                    }else{
                        printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_2 = nueva;
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_1.part_status == '1'){ /////p2 & p4
                    if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_3.part_start){
                        primera = mbr_.mbr_partition_3;
                        segunda = mbr_.mbr_partition_1;
                    }else{
                        primera = mbr_.mbr_partition_1;
                        segunda = mbr_.mbr_partition_3;
                    }
                    if(size < (libre = primera.part_start - sizeof(mbr))){
                        nueva.part_start = sizeof(mbr) + 1;
                    }else if(size < (libre = segunda.part_start - (primera.part_start + primera.part_size))){
                        nueva.part_start = primera.part_start + primera.part_size + 1;
                    }else if(size < (libre = mbr_.mbr_tamano - (segunda.part_start + segunda.part_size))){
                        nueva.part_start = segunda.part_start + segunda.part_size + 1;
                    }else{
                        printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_2 = nueva;
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_1.part_status == '1'){ /////p3 & p4
                    if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_2.part_start){
                        primera = mbr_.mbr_partition_2;
                        segunda = mbr_.mbr_partition_1;
                    }else{
                        primera = mbr_.mbr_partition_1;
                        segunda = mbr_.mbr_partition_2;
                    }
                    if(size < (libre = primera.part_start - sizeof(mbr))){
                        nueva.part_start = sizeof(mbr) + 1;
                    }else if(size < (libre = segunda.part_start - (primera.part_start + primera.part_size))){
                        nueva.part_start = primera.part_start + primera.part_size + 1;
                    }else if(size < (libre = mbr_.mbr_tamano - (segunda.part_start + segunda.part_size))){
                        nueva.part_start = segunda.part_start + segunda.part_size + 1;
                    }else{
                        printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_3 = nueva;
                }else if(mbr_.mbr_partition_4.part_status == '1'){ /////p1,p2&p3
                    primera =  mbr_.mbr_partition_4;
                    if(size < (libre = primera.part_start - sizeof(mbr))){
                        nueva.part_start =  sizeof(mbr) + 1;
                    }else if(size < (libre = mbr_.mbr_tamano - (primera.part_start + primera.part_size))){
                        nueva.part_start = primera.part_start + primera.part_size + 1;
                    }else{
                        printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_1 = nueva;
                }else if(mbr_.mbr_partition_3.part_status == '1'){ /////p1,p2&p4
                    primera =  mbr_.mbr_partition_3;
                    if(size < (libre = primera.part_start - sizeof(mbr))){
                        nueva.part_start =  sizeof(mbr) + 1;
                    }else if(size < (libre = mbr_.mbr_tamano - (primera.part_start + primera.part_size))){
                        nueva.part_start = primera.part_start + primera.part_size + 1;
                    }else{
                        printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_1 = nueva;
                }else if(mbr_.mbr_partition_2.part_status == '1'){ /////p1,p3&p4
                    primera =  mbr_.mbr_partition_2;
                    if(size < (libre = primera.part_start - sizeof(mbr))){
                        nueva.part_start =  sizeof(mbr) + 1;
                    }else if(size < (libre = mbr_.mbr_tamano - (primera.part_start + primera.part_size))){
                        nueva.part_start = primera.part_start + primera.part_size + 1;
                    }else{
                        printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_1 = nueva;
                }else if(mbr_.mbr_partition_1.part_status == '1'){ /////p2,p3&p4
                    primera =  mbr_.mbr_partition_1;
                    if(size < (libre = primera.part_start - sizeof(mbr))){
                        nueva.part_start =  sizeof(mbr) + 1;
                    }else if(size < (libre = mbr_.mbr_tamano - (primera.part_start + primera.part_size))){
                        nueva.part_start = primera.part_start + primera.part_size + 1;
                    }else{
                        printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_2 = nueva;
                }else {
                    printf("Excepcion no esperada.\n");
                    return -1;
                }
                if(mbr_.mbr_partition_1.part_status == '1' && mbr_.mbr_partition_2.part_status == '1' && mbr_.mbr_partition_3.part_status == '1' && mbr_.mbr_partition_4.part_status == '1'){
                    if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                        nueva = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                        mbr_.mbr_partition_4 = nueva;
                    }
                    if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                        nueva = mbr_.mbr_partition_2;
                        mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = nueva;
                    }
                    if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_2.part_start){
                        nueva = mbr_.mbr_partition_1;
                        mbr_.mbr_partition_1 = mbr_.mbr_partition_2;
                        mbr_.mbr_partition_2 = nueva;
                    }
                    if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                        nueva = mbr_.mbr_partition_2;
                        mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = nueva;
                    }
                    if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                        nueva = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                        mbr_.mbr_partition_4 = nueva;
                    }
                    if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                        nueva = mbr_.mbr_partition_2;
                        mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = nueva;
                    }
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_1.part_status == '1'){
                    if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                        nueva = mbr_.mbr_partition_2;
                        mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = nueva;
                    }
                    if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_2.part_start){
                        nueva = mbr_.mbr_partition_1;
                        mbr_.mbr_partition_1 = mbr_.mbr_partition_2;
                        mbr_.mbr_partition_2 = nueva;
                    }
                    if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                        nueva = mbr_.mbr_partition_2;
                        mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = nueva;
                    }
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_1.part_status == '1'){
                    if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_4.part_start){
                        nueva = mbr_.mbr_partition_2;
                        mbr_.mbr_partition_2 = mbr_.mbr_partition_4;
                        mbr_.mbr_partition_4 = nueva;
                    }
                    if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_2.part_start){
                        nueva = mbr_.mbr_partition_1;
                        mbr_.mbr_partition_1 = mbr_.mbr_partition_2;
                        mbr_.mbr_partition_2 = nueva;
                    }
                    if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_4.part_start){
                        nueva = mbr_.mbr_partition_2;
                        mbr_.mbr_partition_2 = mbr_.mbr_partition_4;
                        mbr_.mbr_partition_4 = nueva;
                    }
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_3.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_1.part_status == '1'){
                    if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                        nueva = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                        mbr_.mbr_partition_4 = nueva;
                    }
                    if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_3.part_start){
                        nueva = mbr_.mbr_partition_1;
                        mbr_.mbr_partition_1 = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = nueva;
                    }
                    if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                        nueva = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                        mbr_.mbr_partition_4 = nueva;
                    }
                }else if(mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_3.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_2.part_status == '1'){
                    if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                        nueva = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                        mbr_.mbr_partition_4 = nueva;
                    }
                    if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                        nueva = mbr_.mbr_partition_2;
                        mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = nueva;
                    }
                    if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                        nueva = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                        mbr_.mbr_partition_4 = nueva;
                    }
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_1.part_status == '1'){
                    if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_2.part_start){
                        nueva = mbr_.mbr_partition_1;
                        mbr_.mbr_partition_1 = mbr_.mbr_partition_2;
                        mbr_.mbr_partition_2 = nueva;
                    }
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_1.part_status == '1'){
                    if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_3.part_start){
                        nueva = mbr_.mbr_partition_1;
                        mbr_.mbr_partition_1 = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = nueva;
                    }
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_1.part_status == '1'){
                    if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_4.part_start){
                        nueva = mbr_.mbr_partition_1;
                        mbr_.mbr_partition_1 = mbr_.mbr_partition_4;
                        mbr_.mbr_partition_4 = nueva;
                    }
                }else if(mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_2.part_status == '1'){
                    if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                        nueva = mbr_.mbr_partition_2;
                        mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = nueva;
                    }
                }else if(mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_2.part_status == '1'){
                    if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_4.part_start){
                        nueva = mbr_.mbr_partition_2;
                        mbr_.mbr_partition_2 = mbr_.mbr_partition_4;
                        mbr_.mbr_partition_4 = nueva;
                    }
                }else if(mbr_.mbr_partition_3.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_3.part_status == '1'){
                    if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                        nueva = mbr_.mbr_partition_3;
                        mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                        mbr_.mbr_partition_4 = nueva;
                    }
                }else{
                    printf("Error.\n");
                }
            }else{
                if((type == 'l' || type == 'L') && mbr_.mbr_partition_1.part_type != 'e' && mbr_.mbr_partition_1.part_type != 'E' && mbr_.mbr_partition_2.part_type != 'e' && mbr_.mbr_partition_2.part_type != 'E' && mbr_.mbr_partition_3.part_type != 'e' && mbr_.mbr_partition_3.part_type != 'E' && mbr_.mbr_partition_4.part_type != 'e' && mbr_.mbr_partition_4.part_type != 'E'){
                    printf("No se puede crear particion logica (no hay una particion extendida).");
                    return -1;
                }else{
                    return 0;
                }
            }
        }else{ //mejor y peor ajuste
            int posiciones [2][20], iter, par = 0, rest, mayor = -1, menor = -1, pma = 0, pme = 0;
            char particiones [16][20];
            posiciones[0][0] = sizeof(mbr);
            particiones[0][0] = '\0';
            particiones[0][1] = 'm';
            particiones[0][2] = 'b';
            particiones[0][3] = 'r';
            particiones[0][4] = '\0';
            if(type != 'l' && type != 'L'){
                if(!strcmp(mbr_.mbr_partition_1.part_name, name) || !strcmp(mbr_.mbr_partition_2.part_name, name) || !strcmp(mbr_.mbr_partition_3.part_name, name) || !strcmp(mbr_.mbr_partition_4.part_name, name)){
                    printf("Ya existe una particion con ese nombre.\n");
                    return -1;
                }else if((type == 'e' || type == 'E') && (mbr_.mbr_partition_1.part_type == 'e' || mbr_.mbr_partition_1.part_type == 'E' || mbr_.mbr_partition_2.part_type == 'e' || mbr_.mbr_partition_2.part_type == 'E' || mbr_.mbr_partition_3.part_type == 'e' || mbr_.mbr_partition_3.part_type == 'E' || mbr_.mbr_partition_4.part_type == 'e' || mbr_.mbr_partition_4.part_type == 'E')){
                    printf("Ya existe una particion extendida.\n");
                    return -1;
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_2.part_status == '1'){
                    printf("Solo puede existir un total de 4 particiones primarias o 3 primarias y una extendida.\n");
                    return -1;
                }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_2.part_status == '0'){ /// todas libres
                    nueva.part_start = sizeof(mbr) + 1;
                    if(size >= (libre = (mbr_.mbr_tamano - sizeof(mbr)))){
                        printf("No hay suficiente espacio para crear la particion.\n");
                        return -1;
                    }
                    mbr_.mbr_partition_1 = nueva;
                }else {
                    if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_3.part_status == '1'){
                        if(mbr_.mbr_partition_1.part_start < mbr_.mbr_partition_2.part_start && mbr_.mbr_partition_1.part_start < mbr_.mbr_partition_3.part_start){
                            posiciones[1][0] = mbr_.mbr_partition_1.part_start;
                            for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                            par++;
                            posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_1.part_size;
                            if(mbr_.mbr_partition_2.part_start < mbr_.mbr_partition_3.part_start){
                                posiciones[1][1] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][1] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }
                        }else if(mbr_.mbr_partition_2.part_start < mbr_.mbr_partition_1.part_start && mbr_.mbr_partition_2.part_start < mbr_.mbr_partition_3.part_start){
                            posiciones[1][0] = mbr_.mbr_partition_2.part_start;
                            for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                            par++;
                            posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_2.part_size;
                            if(mbr_.mbr_partition_1.part_start < mbr_.mbr_partition_3.part_start){
                                posiciones[1][1] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][1] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }
                        }else{
                            posiciones[1][0] = mbr_.mbr_partition_3.part_start;
                            for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                            par++;
                            posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_3.part_size;
                            if(mbr_.mbr_partition_2.part_start < mbr_.mbr_partition_1.part_start){
                                posiciones[1][1] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][1] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }
                        }
                    }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_4.part_status == '1'){
                        if(mbr_.mbr_partition_1.part_start < mbr_.mbr_partition_2.part_start && mbr_.mbr_partition_1.part_start < mbr_.mbr_partition_4.part_start){
                            posiciones[1][0] = mbr_.mbr_partition_1.part_start;
                            for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                            par++;
                            posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_1.part_size;
                            if(mbr_.mbr_partition_2.part_start < mbr_.mbr_partition_4.part_start){
                                posiciones[1][1] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][1] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }
                        }else if(mbr_.mbr_partition_2.part_start < mbr_.mbr_partition_1.part_start && mbr_.mbr_partition_2.part_start < mbr_.mbr_partition_4.part_start){
                            posiciones[1][0] = mbr_.mbr_partition_2.part_start;
                            for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                            par++;
                            posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_2.part_size;
                            if(mbr_.mbr_partition_1.part_start < mbr_.mbr_partition_4.part_start){
                                posiciones[1][1] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][1] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }
                        }else{
                            posiciones[1][0] = mbr_.mbr_partition_4.part_start;
                            for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                            par++;
                            posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_4.part_size;
                            if(mbr_.mbr_partition_1.part_start < mbr_.mbr_partition_2.part_start){
                                posiciones[1][1] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][1] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }
                        }
                    }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_3.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_4.part_status == '1'){
                        if(mbr_.mbr_partition_1.part_start < mbr_.mbr_partition_3.part_start && mbr_.mbr_partition_1.part_start < mbr_.mbr_partition_4.part_start){
                            posiciones[1][0] = mbr_.mbr_partition_1.part_start;
                            for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                            par++;
                            posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_1.part_size;
                            if(mbr_.mbr_partition_3.part_start < mbr_.mbr_partition_4.part_start){
                                posiciones[1][1] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][1] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }
                        }else if(mbr_.mbr_partition_3.part_start < mbr_.mbr_partition_1.part_start && mbr_.mbr_partition_3.part_start < mbr_.mbr_partition_4.part_start){
                            posiciones[1][0] = mbr_.mbr_partition_3.part_start;
                            for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                            par++;
                            posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_3.part_size;
                            if(mbr_.mbr_partition_1.part_start < mbr_.mbr_partition_4.part_start){
                                posiciones[1][1] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][1] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }
                        }else{
                            posiciones[1][0] = mbr_.mbr_partition_4.part_start;
                            for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                            par++;
                            posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_4.part_size;
                            if(mbr_.mbr_partition_1.part_start < mbr_.mbr_partition_3.part_start){
                                posiciones[1][1] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][1] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }
                        }
                    }else if(mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_3.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_4.part_status == '1'){
                        if(mbr_.mbr_partition_2.part_start < mbr_.mbr_partition_3.part_start && mbr_.mbr_partition_2.part_start < mbr_.mbr_partition_4.part_start){
                            posiciones[1][0] = mbr_.mbr_partition_2.part_start;
                            for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                            par++;
                            posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_2.part_size;
                            if(mbr_.mbr_partition_3.part_start < mbr_.mbr_partition_4.part_start){
                                posiciones[1][1] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][1] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }
                        }else if(mbr_.mbr_partition_3.part_start < mbr_.mbr_partition_2.part_start && mbr_.mbr_partition_3.part_start < mbr_.mbr_partition_4.part_start){
                            posiciones[1][0] = mbr_.mbr_partition_3.part_start;
                            for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                            par++;
                            posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_3.part_size;
                            if(mbr_.mbr_partition_2.part_start < mbr_.mbr_partition_4.part_start){
                                posiciones[1][1] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][1] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }
                        }else{
                            posiciones[1][0] = mbr_.mbr_partition_4.part_start;
                            for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                            par++;
                            posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_4.part_size;
                            if(mbr_.mbr_partition_2.part_start < mbr_.mbr_partition_3.part_start){
                                posiciones[1][1] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][1] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][2] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][3] = posiciones[1][2] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][3] = mbr_.mbr_tamano;
                            }
                        }
                    }else {
                        if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_2.part_status == '1'){
                            if(mbr_.mbr_partition_1.part_start < mbr_.mbr_partition_2.part_start){
                                posiciones[1][0] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][1] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][2] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][0] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][1] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][2] = mbr_.mbr_tamano;
                            }
                        }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_3.part_status == '1'){
                            if(mbr_.mbr_partition_1.part_start < mbr_.mbr_partition_3.part_start){
                                posiciones[1][0] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][1] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][2] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][0] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][1] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][2] = mbr_.mbr_tamano;
                            }
                        }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_4.part_status == '1'){
                            if(mbr_.mbr_partition_1.part_start < mbr_.mbr_partition_4.part_start){
                                posiciones[1][0] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][1] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][2] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][0] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][1] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][2] = mbr_.mbr_tamano;
                            }
                        }else if(mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_3.part_status == '1'){
                            if(mbr_.mbr_partition_2.part_start < mbr_.mbr_partition_3.part_start){
                                posiciones[1][0] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][1] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][2] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][0] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][1] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][2] = mbr_.mbr_tamano;
                            }
                        }else if(mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_4.part_status == '1'){
                            if(mbr_.mbr_partition_2.part_start < mbr_.mbr_partition_4.part_start){
                                posiciones[1][0] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][1] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][2] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][0] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][1] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][2] = mbr_.mbr_tamano;
                            }
                        }else if(mbr_.mbr_partition_3.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_4.part_status == '1'){
                            if(mbr_.mbr_partition_3.part_start < mbr_.mbr_partition_4.part_start){
                                posiciones[1][0] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][1] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][2] = mbr_.mbr_tamano;
                            }else{
                                posiciones[1][0] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][1] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][2] = posiciones[1][1] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][2] = mbr_.mbr_tamano;
                            }
                        }else{
                            if(mbr_.mbr_partition_1.part_status == '1'){
                                posiciones[1][0] = mbr_.mbr_partition_1.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_1.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_1.part_size;
                                posiciones[1][1] = mbr_.mbr_tamano;
                            }else if(mbr_.mbr_partition_2.part_status == '1'){
                                posiciones[1][0] = mbr_.mbr_partition_2.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_2.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_2.part_size;
                                posiciones[1][1] = mbr_.mbr_tamano;
                            }else if(mbr_.mbr_partition_3.part_status == '1'){
                                posiciones[1][0] = mbr_.mbr_partition_3.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_3.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_3.part_size;
                                posiciones[1][1] = mbr_.mbr_tamano;
                            }else if(mbr_.mbr_partition_4.part_status == '1'){
                                posiciones[1][0] = mbr_.mbr_partition_4.part_start;
                                for(iter = 0; iter < 16; iter++) particiones[par + 1][iter] = mbr_.mbr_partition_4.part_name[iter];
                                par++;
                                posiciones[0][1] = posiciones[1][0] + mbr_.mbr_partition_4.part_size;
                                posiciones[1][1] = mbr_.mbr_tamano;
                            }else {
                                nueva.part_start = sizeof(mbr) + 1;
                                if(size >= (libre = (mbr_.mbr_tamano - sizeof(mbr)))){
                                    printf("No hay suficiente espacio para crear la particion.\n");
                                    return -1;
                                }
                                mbr_.mbr_partition_1 = nueva;
                            }
                        }
                    }
                    for(iter = 0; iter <= par; iter++){
                        rest = posiciones[1][iter] - posiciones[0][iter] - 1;
                        if(rest > mayor){
                            mayor = rest;
                            pma = iter;
                        }
                        if((menor == -1 && rest >= size) || (rest < menor && rest >= size)){
                            menor = rest;
                            pme = iter;
                        }
                    }
                    if(mbr_.disk_fit == 'b'){ //mejor ajuste
                        if(menor == -1){
                            printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                            return -1;
                        }else{
                            if(particiones[pme][1] == 'm' && particiones[pme][2] == 'b' && particiones[pme][3] == 'r'){
                                nueva.part_start = sizeof(mbr) + 1;
                                if(mbr_.mbr_partition_1.part_status != '1') mbr_.mbr_partition_1 = nueva;
                                else if(mbr_.mbr_partition_2.part_status != '1') mbr_.mbr_partition_2 = nueva;
                                else if(mbr_.mbr_partition_3.part_status != '1') mbr_.mbr_partition_3 = nueva;
                                else if(mbr_.mbr_partition_4.part_status != '1') mbr_.mbr_partition_4 = nueva;
                                else {
                                    printf("No se ha podido crear la particion.\n");
                                    return -1;
                                }
                            }else {
                                int opc = 0;
                                for(iter = 0; iter < 16; iter++){
                                    if(mbr_.mbr_partition_1.part_status == '1' && particiones[pma][iter] == mbr_.mbr_partition_1.part_name[iter]) opc = 1;
                                    if(mbr_.mbr_partition_2.part_status == '1' && particiones[pma][iter] == mbr_.mbr_partition_2.part_name[iter]) opc = 2;
                                    if(mbr_.mbr_partition_3.part_status == '1' && particiones[pma][iter] == mbr_.mbr_partition_3.part_name[iter]) opc = 3;
                                    if(mbr_.mbr_partition_4.part_status == '1' && particiones[pma][iter] == mbr_.mbr_partition_4.part_name[iter]) opc = 4;
                                }
                                switch(opc){
                                    case 1:
                                        nueva.part_start = mbr_.mbr_partition_1.part_start + mbr_.mbr_partition_1.part_size + 1;
                                        if(mbr_.mbr_partition_2.part_status != '1') mbr_.mbr_partition_2 = nueva;
                                        else if(mbr_.mbr_partition_3.part_status != '1') mbr_.mbr_partition_3 = nueva;
                                        else if(mbr_.mbr_partition_4.part_status != '1') mbr_.mbr_partition_4 = nueva;
                                        else {
                                            printf("No se ha podido crear la particion.\n");
                                            return -1;
                                        }
                                        break;
                                    case 2:
                                        nueva.part_start = mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1;
                                        if(mbr_.mbr_partition_1.part_status != '1') mbr_.mbr_partition_1 = nueva;
                                        else if(mbr_.mbr_partition_3.part_status != '1') mbr_.mbr_partition_3 = nueva;
                                        else if(mbr_.mbr_partition_4.part_status != '1') mbr_.mbr_partition_4 = nueva;
                                        else {
                                            printf("No se ha podido crear la particion.\n");
                                            return -1;
                                        }
                                        break;
                                    case 3:
                                        nueva.part_start = mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1;
                                        if(mbr_.mbr_partition_1.part_status != '1') mbr_.mbr_partition_1 = nueva;
                                        else if(mbr_.mbr_partition_2.part_status != '1') mbr_.mbr_partition_2 = nueva;
                                        else if(mbr_.mbr_partition_4.part_status != '1') mbr_.mbr_partition_4 = nueva;
                                        else {
                                            printf("No se ha podido crear la particion.\n");
                                            return -1;
                                        }
                                        break;
                                    case 4:
                                        nueva.part_start = mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1;
                                        if(mbr_.mbr_partition_1.part_status != '1') mbr_.mbr_partition_1 = nueva;
                                        else if(mbr_.mbr_partition_2.part_status != '1') mbr_.mbr_partition_2 = nueva;
                                        else if(mbr_.mbr_partition_3.part_status != '1') mbr_.mbr_partition_3 = nueva;
                                        else {
                                            printf("No se ha podido crear la particion.\n");
                                            return -1;
                                        }
                                        break;
                                    default:
                                        printf("ERROR al crear la particion.\n");
                                        return -1;
                                        break;
                                }
                            }
                        }
                    }else{ //peor ajuste
                        if(mayor == -1 && mayor < size){
                            printf("No hay suficiente espacio (contiguo) para crear la particion.\n");
                            return -1;
                        }else{
                            if(particiones[pma][1] == 'm' && particiones[pma][2] == 'b' && particiones[pma][3] == 'r'){
                                nueva.part_start = sizeof(mbr) + 1;
                                if(mbr_.mbr_partition_1.part_status != '1') mbr_.mbr_partition_1 = nueva;
                                else if(mbr_.mbr_partition_2.part_status != '1') mbr_.mbr_partition_2 = nueva;
                                else if(mbr_.mbr_partition_3.part_status != '1') mbr_.mbr_partition_3 = nueva;
                                else if(mbr_.mbr_partition_4.part_status != '1') mbr_.mbr_partition_4 = nueva;
                                else {
                                    printf("No se ha podido crear la particion.\n");
                                    return -1;
                                }
                            }else {
                                int opc = 0;
                                for(iter = 0; iter < 16; iter++){
                                    if(mbr_.mbr_partition_1.part_status == '1' && particiones[pma][iter] == mbr_.mbr_partition_1.part_name[iter]) opc = 1;
                                    if(mbr_.mbr_partition_2.part_status == '1' && particiones[pma][iter] == mbr_.mbr_partition_2.part_name[iter]) opc = 2;
                                    if(mbr_.mbr_partition_3.part_status == '1' && particiones[pma][iter] == mbr_.mbr_partition_3.part_name[iter]) opc = 3;
                                    if(mbr_.mbr_partition_4.part_status == '1' && particiones[pma][iter] == mbr_.mbr_partition_4.part_name[iter]) opc = 4;
                                }
                                switch(opc){
                                    case 1:
                                        nueva.part_start = mbr_.mbr_partition_1.part_start + mbr_.mbr_partition_1.part_size + 1;
                                        if(mbr_.mbr_partition_2.part_status != '1') mbr_.mbr_partition_2 = nueva;
                                        else if(mbr_.mbr_partition_3.part_status != '1') mbr_.mbr_partition_3 = nueva;
                                        else if(mbr_.mbr_partition_4.part_status != '1') mbr_.mbr_partition_4 = nueva;
                                        else {
                                            printf("No se ha podido crear la particion.\n");
                                            return -1;
                                        }
                                        break;
                                    case 2:
                                        nueva.part_start = mbr_.mbr_partition_2.part_start + mbr_.mbr_partition_2.part_size + 1;
                                        if(mbr_.mbr_partition_1.part_status != '1') mbr_.mbr_partition_1 = nueva;
                                        else if(mbr_.mbr_partition_3.part_status != '1') mbr_.mbr_partition_3 = nueva;
                                        else if(mbr_.mbr_partition_4.part_status != '1') mbr_.mbr_partition_4 = nueva;
                                        else {
                                            printf("No se ha podido crear la particion.\n");
                                            return -1;
                                        }
                                        break;
                                    case 3:
                                        nueva.part_start = mbr_.mbr_partition_3.part_start + mbr_.mbr_partition_3.part_size + 1;
                                        if(mbr_.mbr_partition_1.part_status != '1') mbr_.mbr_partition_1 = nueva;
                                        else if(mbr_.mbr_partition_2.part_status != '1') mbr_.mbr_partition_2 = nueva;
                                        else if(mbr_.mbr_partition_4.part_status != '1') mbr_.mbr_partition_4 = nueva;
                                        else {
                                            printf("No se ha podido crear la particion.\n");
                                            return -1;
                                        }
                                        break;
                                    case 4:
                                        nueva.part_start = mbr_.mbr_partition_4.part_start + mbr_.mbr_partition_4.part_size + 1;
                                        if(mbr_.mbr_partition_1.part_status != '1') mbr_.mbr_partition_1 = nueva;
                                        else if(mbr_.mbr_partition_2.part_status != '1') mbr_.mbr_partition_2 = nueva;
                                        else if(mbr_.mbr_partition_3.part_status != '1') mbr_.mbr_partition_3 = nueva;
                                        else {
                                            printf("No se ha podido crear la particion.\n");
                                            return -1;
                                        }
                                        break;
                                    default:
                                        printf("ERROR al crear la particion.\n");
                                        return -1;
                                        break;
                                }
                            }
                        }
                    }
                    if(mbr_.mbr_partition_1.part_status == '1' && mbr_.mbr_partition_2.part_status == '1' && mbr_.mbr_partition_3.part_status == '1' && mbr_.mbr_partition_4.part_status == '1'){
                        if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                            nueva = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                            mbr_.mbr_partition_4 = nueva;
                        }
                        if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                            nueva = mbr_.mbr_partition_2;
                            mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = nueva;
                        }
                        if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_2.part_start){
                            nueva = mbr_.mbr_partition_1;
                            mbr_.mbr_partition_1 = mbr_.mbr_partition_2;
                            mbr_.mbr_partition_2 = nueva;
                        }
                        if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                            nueva = mbr_.mbr_partition_2;
                            mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = nueva;
                        }
                        if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                            nueva = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                            mbr_.mbr_partition_4 = nueva;
                        }
                        if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                            nueva = mbr_.mbr_partition_2;
                            mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = nueva;
                        }
                    }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_1.part_status == '1'){
                        if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                            nueva = mbr_.mbr_partition_2;
                            mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = nueva;
                        }
                        if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_2.part_start){
                            nueva = mbr_.mbr_partition_1;
                            mbr_.mbr_partition_1 = mbr_.mbr_partition_2;
                            mbr_.mbr_partition_2 = nueva;
                        }
                        if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                            nueva = mbr_.mbr_partition_2;
                            mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = nueva;
                        }
                    }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_1.part_status == '1'){
                        if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_4.part_start){
                            nueva = mbr_.mbr_partition_2;
                            mbr_.mbr_partition_2 = mbr_.mbr_partition_4;
                            mbr_.mbr_partition_4 = nueva;
                        }
                        if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_2.part_start){
                            nueva = mbr_.mbr_partition_1;
                            mbr_.mbr_partition_1 = mbr_.mbr_partition_2;
                            mbr_.mbr_partition_2 = nueva;
                        }
                        if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_4.part_start){
                            nueva = mbr_.mbr_partition_2;
                            mbr_.mbr_partition_2 = mbr_.mbr_partition_4;
                            mbr_.mbr_partition_4 = nueva;
                        }
                    }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_3.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_1.part_status == '1'){
                        if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                            nueva = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                            mbr_.mbr_partition_4 = nueva;
                        }
                        if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_3.part_start){
                            nueva = mbr_.mbr_partition_1;
                            mbr_.mbr_partition_1 = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = nueva;
                        }
                        if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                            nueva = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                            mbr_.mbr_partition_4 = nueva;
                        }
                    }else if(mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_3.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_2.part_status == '1'){
                        if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                            nueva = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                            mbr_.mbr_partition_4 = nueva;
                        }
                        if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                            nueva = mbr_.mbr_partition_2;
                            mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = nueva;
                        }
                        if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                            nueva = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                            mbr_.mbr_partition_4 = nueva;
                        }
                    }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_2.part_status && mbr_.mbr_partition_1.part_status == '1'){
                        if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_2.part_start){
                            nueva = mbr_.mbr_partition_1;
                            mbr_.mbr_partition_1 = mbr_.mbr_partition_2;
                            mbr_.mbr_partition_2 = nueva;
                        }
                    }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_1.part_status == '1'){
                        if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_3.part_start){
                            nueva = mbr_.mbr_partition_1;
                            mbr_.mbr_partition_1 = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = nueva;
                        }
                    }else if(mbr_.mbr_partition_1.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_1.part_status == '1'){
                        if(mbr_.mbr_partition_1.part_start > mbr_.mbr_partition_4.part_start){
                            nueva = mbr_.mbr_partition_1;
                            mbr_.mbr_partition_1 = mbr_.mbr_partition_4;
                            mbr_.mbr_partition_4 = nueva;
                        }
                    }else if(mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_3.part_status && mbr_.mbr_partition_2.part_status == '1'){
                        if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_3.part_start){
                            nueva = mbr_.mbr_partition_2;
                            mbr_.mbr_partition_2 = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = nueva;
                        }
                    }else if(mbr_.mbr_partition_2.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_2.part_status == '1'){
                        if(mbr_.mbr_partition_2.part_start > mbr_.mbr_partition_4.part_start){
                            nueva = mbr_.mbr_partition_2;
                            mbr_.mbr_partition_2 = mbr_.mbr_partition_4;
                            mbr_.mbr_partition_4 = nueva;
                        }
                    }else if(mbr_.mbr_partition_3.part_status == mbr_.mbr_partition_4.part_status && mbr_.mbr_partition_3.part_status == '1'){
                        if(mbr_.mbr_partition_3.part_start > mbr_.mbr_partition_4.part_start){
                            nueva = mbr_.mbr_partition_3;
                            mbr_.mbr_partition_3 = mbr_.mbr_partition_4;
                            mbr_.mbr_partition_4 = nueva;
                        }
                    }else{
                        printf("Error.\n");
                    }
                }
            }else{
                if((type == 'l' || type == 'L') && mbr_.mbr_partition_1.part_type != 'e' && mbr_.mbr_partition_1.part_type != 'E' && mbr_.mbr_partition_2.part_type != 'e' && mbr_.mbr_partition_2.part_type != 'E' && mbr_.mbr_partition_3.part_type != 'e' && mbr_.mbr_partition_3.part_type != 'E' && mbr_.mbr_partition_4.part_type != 'e' && mbr_.mbr_partition_4.part_type != 'E'){
                    printf("No se puede crear particion logica (no hay una particion extendida).");
                    return -1;
                }else{
                    return 0;
                }
            }
        }
        disco = fopen(path, "rb+");
        fseek(disco, 0, SEEK_SET);
        fwrite(&mbr_, sizeof(mbr), 1, disco);
        fclose(disco);
        //imprimir_mbr(mbr_);
        printf("Particion creada exitosamente.\n");
    }
    return 0;
}

int mount(char path[300], char name[20]){
    FILE *mounts, *disco;
    char aidi[5], ult;
    ult = '`';
    aidi[0] = 'v';
    aidi[1] = 'd';
    aidi[2] = '\0';
    aidi[3] = '\0';
    aidi[4] = '\0';
    disco = fopen(path, "rb+");
    if(!disco){
        printf("No se ha encontrado el disco especificado.\n");
        return -1;
    }
    mbr mbr_;
    limpiar_mbr(&mbr_);
    fseek(disco, 0, SEEK_SET);
    fread(&mbr_, sizeof(mbr), 1, disco);
    fclose(disco);
    moun est;
    limpiar_mount(&est);
    if(!strcmp(mbr_.mbr_partition_1.part_name, name) || !strcmp(mbr_.mbr_partition_2.part_name, name) || !strcmp(mbr_.mbr_partition_3.part_name, name) || !strcmp(mbr_.mbr_partition_4.part_name, name)){
        mounts = fopen("/home/moramaz/Escritorio/mounts.dsk", "rb+");
        int esta = 0, cont_id = 0;
        int ej;
        if(mounts){
            ej = 1;
        }else{
            mounts = fopen("/home/moramaz/Escritorio/mounts.dsk", "wb+");
            printf("Archivo creado en \n");
            aidi[2] = 'a';
            aidi[3] = '1';
            ej = 0;
        }
        int cont_part = 0;
        while(ej){
            fread(&est, sizeof(moun), 1, mounts);
            if(!strcmp(est.id, "\0")){
                if(esta){
                    aidi[2] = ult;
                    aidi[3] = cont_id + '0';
                }else{
                    ult++;
                    aidi[2] = ult;
                    aidi[3] = '1';
                }
                break;
            }else{
                if(est.id[2] > ult){
                    ult = est.id[2];
                }
                if(!strcmp(path, est.path)){
                    esta = 1;
                    ult = est.id[2];
                    cont_id = (est.id[3] - '0') + 1;
                    if(!strcmp(name, est.nombre)){
                        printf("La particion ya habia sido montada con el id %s.\n", est.id);
                        return -1;
                    }
                }else{
                    esta = 0;
                }
                cont_part++;
                limpiar_mount(&est);
            }
        }
        fseek(disco, cont_part * sizeof(moun), SEEK_SET);
        int i;
        for(i = 0; i < 5; i++){
            est.id[i] = aidi[i];
        }
        i = 0;
        while(name[i] != '\0'){
            est.nombre[i] = name[i];
            i++;
        }
        est.nombre[i] = '\0';
        i = 0;
        while(path[i] != '\0'){
            est.path[i] = path[i];
            i++;
        }
        est.path[i] = '\0';
        fwrite(&est, sizeof(moun), 1, disco);
        fclose(disco);
        printf("La particion ha sido montada con el id %s exitosamente.\n\n", est.id);
        printf("Mostrando la lista de particiones montadas:\n");
        disco = fopen("/home/moramaz/Escritorio/mounts.dsk", "r");
        while(!feof(disco)){
            fread(&est, sizeof(moun), 1, mounts);
            if(strcmp(est.id, "\0")){
                printf("\tid: %s \tnombre: %s\n", est.id, est.nombre);
            }
            limpiar_mount(&est);
        }
        fclose(disco);
    } else {
        printf("No existe esa particion en el disco especificado.\n");
        return -1;
    }
    return 0;
}

int unmount(char id[5]){
    FILE *mounts;
    moun lector, limpio;
    limpiar_mount(&lector);
    limpiar_mount(&limpio);
    mounts = fopen("/home/moramaz/Escritorio/mounts.dsk", "rb+");
    if(mounts == NULL){
        printf("No se ha podido desmontar la particion.\n");
        return -1;
    }
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
    if(condicion){

    }else{
        printf("No se ha encontrado el id ingresado.\n");
        return -1;
    }
    return 0;
}

int rep(char name[16], char path[200], char id[5]){
    int posicion = 0, condicion = 0, contador = 0;
    char r1[3] = "mbr", r2[4] = "disk", r3[5] = "inode", r4[10] = "journaling", r5[5] = "block", r6[8] = "bm_inode", r7[8] = "bm_block", r8[4] = "tree", r9[2] = "sb",
    r10[4] = "file", r11[2] = "ls";
    for(contador = 0, posicion = 0; contador < 3; contador++, posicion++){
        if(name[posicion] != r1[contador] && name[posicion] != r1[contador] - 32){
            condicion = 0;
            break;
        }
        condicion = 1;
    }
    if(condicion){
        return rep_mbr(id, path);
    }else{
        for(contador = 0, posicion = 0; contador < 4; contador++, posicion++){
            if(name[posicion] != r2[contador] && name[posicion] != r2[contador] - 32){
                condicion = 0;
                break;
            }
            condicion = 1;
        }
        if(condicion){
            return rep_disk(id, path);
        }else{
            /*for(contador = 0, posicion = 0; contador < 5; contador++, posicion++){
                if(name[posicion] != r3[contador] && name[posicion] != r3[contador] - 32){
                    condicion = 0;
                    break;
                }
                condicion = 1;
            }*/
            /*if(condicion){
                //return rep_inode(id, path);
            }else{
                for(contador = 0, posicion = 0; contador < 10; contador++, posicion++){
                    if(name[posicion] != r4[contador] && name[posicion] != r4[contador] - 32){
                        condicion = 0;
                        break;
                    }
                    condicion = 1;
                }
                if(condicion){
                    //return rep_jour(id, path);
                }else{
                    for(contador = 0, posicion = 0; contador < 5; contador++, posicion++){
                        if(name[posicion] != r5[contador] && name[posicion] != r5[contador] - 32){
                            condicion = 0;
                            break;
                        }
                        condicion = 1;
                    }
                    if(condicion){
                        //return rep_block(id, path);
                    }else{
                        for(contador = 0, posicion = 0; contador < 8; contador++, posicion++){
                            if(name[posicion] != r6[contador] && name[posicion] != r6[contador] - 32){
                                condicion = 0;
                                break;
                            }
                            condicion = 1;
                        }
                        if(condicion){
                            //return rep_bm_inode(id, path);
                        }else{
                            for(contador = 0, posicion = 0; contador < 8; contador++, posicion++){
                                if(name[posicion] != r7[contador] && name[posicion] != r7[contador] - 32){
                                    condicion = 0;
                                    break;
                                }
                                condicion = 1;
                            }
                            if(condicion){
                                //return rep_bm_block(id, path);
                            }else{
                                for(contador = 0, posicion = 0; contador < 4; contador++, posicion++){
                                    if(name[posicion] != r8[contador] && name[posicion] != r8[contador] - 32){
                                        condicion = 0;
                                        break;
                                    }
                                    condicion = 1;
                                }
                                if(condicion){
                                    //return rep_tree(id, path);
                                }else{
                                    for(contador = 0, posicion = 0; contador < 2; contador++, posicion++){
                                        if(name[posicion] != r9[contador] && name[posicion] != r9[contador] - 32){
                                            condicion = 0;
                                            break;
                                        }
                                        condicion = 1;
                                    }
                                    if(condicion){
                                        return rep_sb(id, path);
                                    }else{
                                        for(contador = 0, posicion = 0; contador < 4; contador++, posicion++){
                                            if(name[posicion] != r10[contador] && name[posicion] != r10[contador] - 32){
                                                condicion = 0;
                                                break;
                                            }
                                            condicion = 1;
                                        }
                                        if(condicion){
                                            //return rep_file(id, path, ruta);
                                        }else{
                                            for(contador = 0, posicion = 0; contador < 2; contador++, posicion++){
                                                if(name[posicion] != r11[contador] && name[posicion] != r11[contador] - 32){
                                                    condicion = 0;
                                                    break;
                                                }
                                                condicion = 1;
                                            }
                                            if(condicion){
                                                //return rep_ls(id, path, ruta);
                                            }else{
                                                //for(contador = 0, posicion = 0; contador < 4; contador++, posicion++){
                                                //    if(name[posicion] != r2[contador] && name[posicion] != r2[contador] - 32){
                                                //        condicion = 0;
                                                //        break;
                                                //    }
                                                    condicion = 1;
                                            }*/
                                            printf("No se ha reconocido el valor del parametro name.\n");
                                            return -1;
                                        /*}
                                    }
                                }
                            }
                        }
                    }
                }
            }/**/
        }
    }
    return 0;
}
