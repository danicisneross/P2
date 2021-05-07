/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ANA BAÑOBRE MARTINEZ LOGIN 1: ana.banobre
 * AUTHOR 2: DANIELA ALEJANDRA CISNEROS SANDE LOGIN 2: d.cisneross
 * GROUP: 3.3
 * DATE: 15 / 04 / 21
 */

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "video_list.h"
#include "user_list.h"
#include <stdlib.h>

#define MAX_BUFFER 255
#define N 20

/*
   **** FUNCION NEW ****
 * OBJETIVO: Dar de alta a los nuevos usarios con sus caracteristicas, introduciendolos en la lista.
 * CONDICION: que el usuario no exista previamente, si existiese se mostraria un error, que su categoría sea premium o standard y que su lista esté inicializada
 * ENTRADAS: nickname = nombre del usuario; userCategory = categoria del usuario; userL = lista en la que introducimos los datos de los usuarios.
 * SALIDAS: El parametro de salida seria unicamente la lista por referencia con el nuevo usuario.
*/

void new(tNickname nickname, tUserCategory userCategory, tUserList *userL) {
    char category[N];
    tUserItem user;
    tUserPos pos;
    pos = findItem(nickname, *userL);
    tVideoList *videoL;
    videoL = &user.videoList;

    if (pos == NULL_USER) { //Comprobar que la lista no contiene el nick que se quiere introducir

        strcpy(user.nickname, nickname); //Pasamos los datos a 'user'

        if (userCategory == standard) { //Si la categoria del usuario es standard el string 'category' sera 'standard'
            user.userCategory = standard;
            strcpy(category, "standard");
        } else { //Si la categoria del usuario no es standard (entonces premium) el string 'category' sera 'premium'
            user.userCategory = premium;
            strcpy(category, "premium");
        }
        createEmptyListV(videoL);
        user.totalPlayTime = 0;

        //Introducimos el tItem en la lista userL en la que se guardan todos los datos de los usuarios si responde con TRUE
        if (insertItem(user, userL) == true) {
            printf("* New: nick %s category %s\n", nickname, category);
        } else {
            printf("+ Error: New not possible\n");
        }
        //En caso de que la lista contenga el usuario el programa devolverá un error
    } else if (pos != NULL_USER) {
        printf("+ Error: New not possible\n");
    }
}

/*
 *  **** FUNCION STATS ****
 * OBJETIVO: En primer lugar mostraremos el usuario que contabilizaremos con su categoria y su numero de reproducciones, luego mostraremos las estadisticas
 *           en funcion de la categoria de cada usuario: numero de usuarios, el numero de videos que han reproducido y la media entre los videos y dichos usuarios.
 * CONDICION: que el usuario se haya creado y que la lista no este vacia, si esto ocurre todos los datos van a estar a cero.
 * ENTRADAS: userL = lista en la que tendremos los datos.
 * SALIDAS: No hay parametros de salida (ni por referencia) ya que la lista no se modifica y solo se muestran sus datos
 */

void stats(tUserList userL) {
    int sUsers = 0, sPlays = 0; //Variables que mostrarán el numero de usuarios 'Standard' y sus reproducciones
    int pUsers = 0, pPlays = 0;  //Variables que mostrarán el numero de usuarios 'Premium' y sus reproducciones
    tUserPos pos;
    tVideoPos posV;
    tUserItem user;
    tVideoItem video;
    tVideoList *videoL;
    videoL = &user.videoList;
    char category[20];

    if (!isEmptyList(userL)) { // Verificamos que la lista no está vacía
        pos = first(userL); // Inicializamos la posicion en el principio de la lista para que la recorra
        while (pos != NULL_USER) {
            user = getItem(pos, userL); // Buscamos el usuario que esta en la posicion 'pos'
            if (user.userCategory == standard) { // Si es standard sumara un usuario a standard
                strcpy(category, "standard");
                sUsers++;
                sPlays += user.totalPlayTime;
            } else { // Si no es standard (entonces premium) sumara un usuario a premium
                strcpy(category, "premium");
                pUsers++;
                pPlays += user.totalPlayTime;
            }
            printf("*Nick %s category %s totalplaytime %d\n", user.nickname, category, user.totalPlayTime);

            if (isEmptyListV(*videoL)) {
                printf("No videos\n");
            } else if (!isEmptyListV(*videoL)) {
                posV = firstV(*videoL);
                while (posV != NULL_VIDEO) {
                    video = getItemV(posV, *videoL);
                    printf("Video %s playtime %d\n", video.titleVideo, video.playTime);
                    posV = nextV(posV, *videoL);
                }
            }
            pos = next(pos, userL); // Cada vez que pase una posicion ira a la siguiente
        }
        printf("Category Users TimePlay Average\n"
               "Standard %6d %9d %8.2f\n"
               "Premium  %6d %9d %8.2f\n", sUsers, sPlays, sUsers == 0 ? 0 : (float) sPlays / sUsers, pUsers,
               pPlays, pUsers == 0 ? 0 : (float) pPlays / pUsers);
    } else {
        printf("+ Error: Stats not possible\n");
    }
}

/*
 *  **** FUNCION ADD ****
 * OBJETIVO: Añadirle videos a un determinado usuario.
 * CONDICION: Que el usuario exista en la lista de usuarios y por otro lado no debe existir el video en la lista de videos.
 * ENTRADAS: nickname = nombre del usuario; titleVideo = titulo del video; userL = lista en la que tendremos los datos de los usuarios; videoL = lista en la que tendremos los datos de los videos.
 * SALIDAS: La lista de videos por referencia con los nuevos videos agregados.
 */

void add(tNickname nickname, tTitleVideo titleVideo, tUserList *userL) {
    tVideoItem video;
    tUserItem user;
    tVideoList *videoL;
    tUserPos pos;
    pos = findItem(nickname, *userL);
    videoL = &user.videoList;

    //Comprobar que la lista contiene el nick al que le agregaremos el video
    if (pos != NULL_USER) {

        video = getItemV(findItemV(titleVideo, *videoL), *videoL);
        user = getItem(pos, *userL);
        strcpy(video.titleVideo, titleVideo); //Pasamos los datos a 'video'
        video.playTime = 0;

        if (insertItemV(video, NULL_VIDEO, videoL) == true) {
            printf("* Add: nick %s adds video %s\n", nickname, video.titleVideo);
            updateItem(user, pos, userL);
        } else {//En caso de que la lista no contenga el usuario se devolverá un error
            printf("+ Error: Add not possible\n");
        }
    } else {//En caso de que la lista no contenga el usuario se devolverá un error
        printf("+ Error: Add not possible\n");
    }

}

/*
 * **** FUNCION PLAYS ****
 * OBJETIVO: Visualizar la reproduccion del video con su titulo, el usuario y la cuenta de las reproducciones de dicho usuario; en el caso de que no se pueda porque
 *           no cumple las condiciones entonces el error que saldra sera que no ha sido posible esta operacion.
 * CONDICION: Que la lista no este vacia, si lo esta se mostrara un error.
 * ENTRADAS: nickname = nombre del usuario; titleVideo = titulo del video reproducido; userL = lista en la que introducimos los datos.
 * SALIDAS: El parametro de salida seria unicamente la lista por referencia cambiada, con las reproducciones de los usuarios actualizadas.
 */

void play(tNickname nickname, tTitleVideo titleVideo, tPlayTime playTime, tUserList *userL) {
    tVideoItem video;
    tUserItem user;
    tUserPos pos;
    pos = findItem(nickname, *userL);
    tVideoList *videoL;
    videoL = &user.videoList;
    tVideoPos posV;
    posV = findItemV(titleVideo, *videoL);

    user = getItem(pos, *userL);
    //Tanto el usuario como el video deben existir en sus respectivas listas
    if ((pos != NULL_USER) && (posV != NULL_VIDEO)) {
        video = getItemV(posV, *videoL);
        strcpy(video.titleVideo, titleVideo);
        video.playTime = playTime;
        user.totalPlayTime = user.totalPlayTime + playTime;
        printf("* Play: nick %s plays video %s playtime %d totalplaytime %d\n", nickname, titleVideo,
               video.playTime, user.totalPlayTime);
        updateItemV(video, posV, videoL);
        updateItem(user, pos, userL);

    } else {//En caso contrario se devolverá un error
        printf("+ Error: Play not possible\n");
    }
}

/*
 *  **** FUNCION DELETE ****
 * OBJETIVO: Eliminar un determinado usuario de la lista (incluyendo sus caracteristicas).
 * CONDICION: Que la lista no este vacia, si lo esta se mostrara un error.
 * ENTRADAS: nickname = nombre del usuario; userL = lista en la que tendremos los datos.
 * SALIDAS: El parametro de salida seria unicamente la lista por referencia cambiada, sin el usuario eliminado.
 */

void delete(tNickname nickname, tUserList *userL) {
    tUserItem user;
    char category[N];
    tUserPos pos;
    pos = findItem(nickname, *userL);
    tVideoList *videoL;

    if (findItem(nickname, *userL) != NULL_USER) {

        user = getItem(pos, *userL);
        videoL = &user.videoList;
        if (user.userCategory == standard) strcpy(category, "standard");
        else strcpy(category, "premium");
        deleteListV(videoL);
        deleteAtPosition(pos, userL);
        printf("* Delete: nick %s category %s totalplaytime %d\n", nickname, category, user.totalPlayTime);

    } else printf("+ Error: Delete not possible\n"); //Si el usuario no existe mostrara un error

}

/*
 *  **** FUNCION REMOVE ****
 * OBJETIVO: Eliminar de la lista los usuarios cumplan las condiciones.
 * CONDICION: La lista debe contener a los usuarios standard, usuarios que deben exceder el tiempo maximo.
 * ENTRADAS: maxtime = tiempo maximo de reproducciones ; userL = lista de usuarios en la que tendremos los datos.
 * SALIDAS: El parametro de salida sera la lista por referencia cambiada, sin el usuario standard eliminado.
 */

void removeUser(int maxTime, tUserList *userL) {
    tUserItem user;
    tUserPos pos;
    tVideoList *videoL;
    videoL = &user.videoList;

    bool noError = false;

    if (!isEmptyList(*userL)) { // Verificamos que la lista no está vacía
        //Recorre la lista de usuarios, los standard con mas reproducciones que maxTime los elimina
        for (pos = first(*userL); pos != NULL_USER; pos = next(pos, *userL)) {
            user = getItem(pos, *userL);
            if ((user.userCategory == standard) && (user.totalPlayTime > maxTime)) {
                deleteListV(videoL);
                deleteAtPosition(pos, userL);
                noError = true;
                printf("Removing nick %s totalplaytime %d\n", user.nickname, user.totalPlayTime);
            }
            if (noError == false) {
                printf("+ Error: Remove not possible\n");
            }
        }
    } else {
        printf("+ Error: Remove not possible\n");
    }
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tUserList *userL) {

    switch (command) {
        case 'N': {
            printf("********************\n");
            printf("%s %c: nick %s category %s\n", commandNumber, command, param1, param2);
            // Si 'param2' (que recibe la categoria) es 'standard', la funcion new recibe el enum standard
            if (strcmp(param2, "standard") == 0) {
                new(param1, standard, userL);
            }
                // Si 'param2' es 'premium', la funcion new recibe el enum premium
            else if (strcmp(param2, "premium") == 0) {
                new(param1, premium, userL);
            }
            break;
        }
        case 'S': {
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            //La funcion 'stats' recibe la lista con los usuarios y su lista de videos asociados
            stats(*userL);
            break;
        }
        case 'A': {
            printf("********************\n");
            printf("%s %c: nick %s video %s\n", commandNumber, command, param1, param2);
            //La funcion 'add' recibe la lista con los usuarios y su lista de videos asociados
            add(param1, param2, userL);
            break;
        }
        case 'P': {
            printf("********************\n");
            printf("%s %c: nick %s video %s minutes %s\n", commandNumber, command, param1, param2, param3);
            int time = strtol(param3, NULL, 10); //Pasamos param3 (string) a integer
            play(param1, param2, time, userL);
            break;
        }
        case 'D': {
            printf("********************\n");
            printf("%s %c: nick %s\n", commandNumber, command, param1);
            delete(param1, userL); //La funcion 'delete' recibe 'param1' (nickname) y la lista con los usuarios
            break;
        }
        case 'R': {
            printf("********************\n");
            printf("%s %c: maxtime %s\n", commandNumber, command, param1);
            int time = strtol(param1, NULL, 10);
            removeUser(time, userL); //La funcion 'remove' recibe 'time' (param1->maxtime) y la lista con los usuarios
            break;
        }
        default: {
            break;
        }
    }
}

void readTasks(char *filename) {
    FILE *df;
    char *commandNumber, *command, *param1, *param2, *param3;

    tUserList userL;
    createEmptyList(&userL);

    df = fopen(filename, "rb");
    if (df != NULL) {
        const char delimiters[] = " \n\r";
        char buffer[MAX_BUFFER];
        while (fgets(buffer, MAX_BUFFER, df)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            processCommand(commandNumber, command[0], param1, param2, param3, &userL);
        }
        fclose(df);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name);

    return 0;
}
