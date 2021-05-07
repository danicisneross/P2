/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ANA BAÑOBRE MARTÍNEZ LOGIN 1: ana.banobre
 * AUTHOR 2: DANIELA ALEJANDRA CISNEROS SANDE LOGIN 2: d.cisneross
 * GROUP: 3.3
 * DATE: 15 / 04 / 21
 */


#include "types.h"
#include "user_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

void createEmptyList(tUserList *L) {
    *L = NULL_USER;
}

bool isEmptyList(tUserList L) {
    return L == NULL_USER;
}

tUserPos first(tUserList L) {
    return L;
}

tUserPos next(tUserPos p, tUserList L) {
    return p->next;
}

tUserPos last(tUserList L) {
    tUserPos p;

    for (p = L; p->next != NULL_USER; p = p->next);
    return p;
}

tUserPos previous(tUserPos p, tUserList L) {
    tUserPos q;

    if (p == L) {
        return NULL_USER;
    } else {
        q = L;
        for (q = L; q->next != p; q = q->next);
    }
    return q;
}

tUserItem getItem(tUserPos p, tUserList L) {
    return p->data;
}

void updateItem(tUserItem d, tUserPos p, tUserList *L) {
    p->data = d;
}

tUserPos findItem(tNickname nickname, tUserList L) {
    tUserPos p;

    for (p = L; (p != NULL_USER) && (strcmp(p->data.nickname, nickname) < 0); p = p->next);
    if (p != NULL_USER && (strcmp(p->data.nickname, nickname) == 0)){
        return p;
    }
    return NULL_USER;
}

bool createNode(tUserPos *p) {
    *p = malloc(sizeof(struct tUserList));
    return *p != NULL_USER;
}

tUserPos findPosition(tUserList L, tUserItem d) {
    tUserPos p;
    p = L;
    while ((p->next != NULL_USER) && (strcmp((p->next->data.nickname), d.nickname) < 0))
        p = p->next;
    return p;
}

bool insertItem(tUserItem d, tUserList *L) {
    tUserPos p, q;
    if (!createNode(&q))
        return false;
    else {
        q->data = d;
        q->next = NULL_USER;
        if (*L == NULL_USER) {
            *L = q;
        } else if (strcmp((*L)->data.nickname, d.nickname) > 0) {
            q->next = *L;
            *L = q;
        } else {
            p = findPosition(*L, d);
            q->next = p->next;
            p->next = q;
        }
        return true;
    }
}

void deleteAtPosition(tUserPos p, tUserList *L) {
    tUserPos q;
    if (p == *L) { // borrar primer elemento
        *L = (*L)->next;
    } else if (p->next == NULL_USER) { // eliminar última posicion
        q = previous(p, *L);
        q->next = NULL_USER;
    } else { // eliminar posición intermedia
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q; // se borra realmente el nodo siguiente a p
    }
    free(p);
}





