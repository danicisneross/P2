/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ANA BAÑOBRE MARTÍNEZ LOGIN 1: ana.banobre
 * AUTHOR 2: DANIELA ALEJANDRA CISNEROS SANDE LOGIN 2: d.cisneross
 * GROUP: 3.3
 * DATE: 15 / 04 / 21
 */

#ifndef P2_VIDEO_LIST_H
#define P2_VIDEO_LIST_H

#include "types.h"
#include <stdbool.h>

/* Definicion de tipos */

#define NULL_VIDEO -1
#define MAX 25

typedef int tVideoPos;

typedef struct tNodeV{
    tVideoItem data[MAX];
    tVideoPos lastPos;
} tVideoList;

// FUNCIONES:

/*
 * * FUNCION CreateEmptyList *
 * Crea una lista vacía
 * PostCD: La lista queda inicializada y no contiene elementos
 */

void createEmptyListV(tVideoList* vL);

/*
 * * FUNCION insertItem *
 * Inserta un elemento en la lista antes de la posición indicada. Si la posición es LNULL, entonces se añade al final.
 * Devuelve un valor true si el elemento fue insertado; false en caso contrario.
 * PreCD: La posición indicada es una posición válida en la lista o bien nula (LNULL).
 * PostCD: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado.
*/

bool insertItemV(tVideoItem tVideo, tVideoPos vp, tVideoList* vL);

/*
 * * FUNCION deleteAtPosition *
 * Elimina de la lista el elemento que ocupa la posición indicada.
 * PreCD: La posición indicada es una posición válida en la lista.
 * PostCD: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado.
*/

void deleteAtPositionV(tVideoPos vp, tVideoList* vL);

/*
 * * FUNCION updateItem *
 * Modifica el contenido del elemento situado en la posición indicada.
 * PreCD: La posición indicada es una posición válida en la lista.
 * PostCD: El orden de los elementos de la lista no se ve modificado.PostCD: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado.
*/

void updateItemV(tVideoItem tVideo, tVideoPos vp, tVideoList* vL);

/*
 * * FUNCION findItem *
 * Devuelve la posición del primer elemento de la lista cuyo nick de usuario se corresponda con el indicado
 * (o LNULL si no existe tal elemento).
*/

tVideoPos findItemV(tTitleVideo titleVideo, tVideoList vL);

/*
 * * FUNCION getItem *
 * Devuelve el contenido del elemento de la lista que ocupa la posición indicada.
 * PreCD: La posición indicada es una posición válida en la lista.
 */

tVideoItem getItemV(tVideoPos vp, tVideoList vL);

/*
 * * FUNCION isEmptyList *
 * Determina si la lista está vacía.
*/

bool isEmptyListV(tVideoList vL);

/*
 * * FUNCION first *
 * Devuelve la posición del primer elemento de la lista.
 * PreCD: La lista no está vacía.
 */

tVideoPos firstV(tVideoList vL);

/*
 * * FUNCION last *
 * Devuelve la posición del último elemento de la lista.
 * PreCD: La lista no está vacía.
 */

tVideoPos lastV(tVideoList vL);

/*
 * * FUNCION previus *
 *Devuelve la posición en la lista del elemento anterior al de la posición indicada (o LNULL si la posición no tiene anterior).
 * PreCD: La posición indicada es una posición válida en la lista.
 */

tVideoPos previousV(tVideoPos vp, tVideoList vL);

/*
 * * FUNCION next *
 * Devuelve la posición en la lista del elemento siguiente al de la posición indicada (o LNULL si la posición no tiene siguiente).
 * PreCD: La posición indicada es una posición válida en la lista.
 */

tVideoPos nextV(tVideoPos vp, tVideoList vL);

/*
 * * FUNCION deleteList *
 * Elimina la lista indicada.
 * PreCD: La lista existiia previamente.
 * PostCD: La lista queda vacia.
*/

void deleteListV(tVideoList *vL);

#endif //P2_VIDEO_LIST_H

