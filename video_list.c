/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ANA BAÑOBRE MARTÍNEZ LOGIN 1: ana.banobre
 * AUTHOR 2: DANIELA ALEJANDRA CISNEROS SANDE LOGIN 2: d.cisneross
 * GROUP: 3.3
 * DATE: 15 / 04 / 21
 */

#include "video_list.h"
#include "string.h"


void createEmptyListV(tVideoList *vL) {
    vL->lastPos = NULL_VIDEO;
}

bool insertItemV(tVideoItem vd, tVideoPos vp, tVideoList *vL) {
    tVideoPos i;
    if (vL->lastPos == MAX - 1)
        return false;
    vL->lastPos++;
    if (vp == NULL_VIDEO) { //Insertar al final
        vL->data[vL->lastPos] = vd;
    } else {
        for (i = vL->lastPos; i >= vp + 1; i--)
            vL->data[i] = vL->data[i - 1];
        vL->data[vp] = vd;
    }
    return true;
}

void updateItemV(tVideoItem vd, tVideoPos vp, tVideoList *vL) {
    vL->data[vp] = vd;
}

tVideoPos findItemV(tTitleVideo titleVideo, tVideoList vL) {
    tVideoPos p;

    if (isEmptyListV(vL) == true)
        return NULL_VIDEO;

    for (p = firstV(vL); p <= vL.lastPos; p++) {
        if (strcmp(vL.data[p].titleVideo, titleVideo) == 0) {
            return p;
        }
    }
    return NULL_VIDEO;
}

bool isEmptyListV(tVideoList vL) {
    return vL.lastPos == NULL_VIDEO;
}

tVideoItem getItemV(tVideoPos vp, tVideoList vL) {
    return vL.data[vp];
}

tVideoPos firstV(tVideoList vL) {
    if (isEmptyListV(vL)){
        return NULL_VIDEO;
    }
    return 0;
}

tVideoPos lastV(tVideoList vL) {
    return vL.lastPos;
}

tVideoPos previousV(tVideoPos vp, tVideoList vL) {
    if (vp == firstV(vL)){
        return NULL_VIDEO;
    }
    return --vp;
}

tVideoPos nextV(tVideoPos vp, tVideoList vL) {
    if (vp == vL.lastPos){
        return NULL_VIDEO;
    }
    return ++vp;
}

void deleteAtPositionV(tVideoPos vp, tVideoList *vL) {
    for (tVideoPos i = vp; i < vL->lastPos; i++) {
        vL->data[i] = vL->data[i + 1];
    }
    vL->lastPos--;
}

void deleteListV(tVideoList *vL){
    vL->lastPos = NULL_VIDEO;
}