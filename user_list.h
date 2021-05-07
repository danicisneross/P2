/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ANA BAÑOBRE MARTÍNEZ LOGIN 1: ana.banobre
 * AUTHOR 2: DANIELA ALEJANDRA CISNEROS SANDE LOGIN 2: d.cisneross
 * GROUP: 3.3
 * DATE: 15 / 04 / 21
 */

#ifndef P2_USER_LIST_H
#define P2_USER_LIST_H

#include "types.h"
#include <stdbool.h>
#include "video_list.h"

#define NULL_USER NULL

typedef struct tUserList *tUserPos;
typedef tUserPos tUserList;
typedef struct tUserItem {
    tNickname nickname;
    tPlayTime totalPlayTime;
    tUserCategory userCategory;
    tVideoList videoList;
} tUserItem;
struct tUserList {
    tUserItem data;
    tUserPos next;
};


/*
 * * FUNCION CreateEmptyList *
 * Crea una lista vacía
 * PostCD: La lista queda inicializada y no contiene elementos
 */

void createEmptyList(tUserList *L);

/*
 * * FUNCION isEmptyList *
 * Determina si la lista está vacía.
*/

bool isEmptyList(tUserList);

/*
 * * FUNCION insertItem *
 * Inserta un elemento en la lista antes de la posición indicada. Si la posición es LNULL, entonces se añade al final.
 * Devuelve un valor true si el elemento fue insertado; false en caso contrario.
 * PreCD: La posición indicada es una posición válida en la lista o bien nula (LNULL).
 * PostCD: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado.
*/

bool insertItem(tUserItem, tUserList*);

/*
 * * FUNCION updateItem *
 * Modifica el contenido del elemento situado en la posición indicada.
 * PreCD: La posición indicada es una posición válida en la lista.
 * PostCD: El orden de los elementos de la lista no se ve modificado.PostCD: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado.
*/

void updateItem(tUserItem, tUserPos, tUserList*);

/*
 * * FUNCION deleteAtPosition *
 * Elimina de la lista el elemento que ocupa la posición indicada.
 * PreCD: La posición indicada es una posición válida en la lista.
 * PostCD: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado.
*/

void deleteAtPosition(tUserPos, tUserList*);

/*
 * * FUNCION findPosition *
 * Devuelve la posición del elemento de la lista que coincida con el usuario indicado
 * (o LNULL si no existe tal elemento).
*/

tUserPos findPosition(tUserList, tUserItem);

/*
 * * FUNCION findItem *
 * Devuelve la posición del primer elemento de la lista cuyo nick de usuario se corresponda con el indicado
 * (o LNULL si no existe tal elemento).
*/

tUserPos findItem(tNickname nickname, tUserList);

/*
 * * FUNCION getItem *
 * Devuelve el contenido del elemento de la lista que ocupa la posición indicada.
 * PreCD: La posición indicada es una posición válida en la lista.
 */

tUserItem getItem(tUserPos, tUserList);

/*
 * * FUNCION first *
 * Devuelve la posición del primer elemento de la lista.
 * PreCD: La lista no está vacía.
 */

tUserPos first(tUserList);

/*
 * * FUNCION last *
 * Devuelve la posición del último elemento de la lista.
 * PreCD: La lista no está vacía.
 */

tUserPos last(tUserList);

/*
 * * FUNCION previus *
 *Devuelve la posición en la lista del elemento anterior al de la posición indicada (o LNULL si la posición no tiene anterior).
 * PreCD: La posición indicada es una posición válida en la lista.
 */

tUserPos previous(tUserPos, tUserList);

/*
 * * FUNCION next *
 * Devuelve la posición en la lista del elemento siguiente al de la posición indicada (o LNULL si la posición no tiene siguiente).
 * PreCD: La posición indicada es una posición válida en la lista.
 */

tUserPos next(tUserPos, tUserList);


#endif //P2_USER_LIST_H