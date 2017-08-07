#include <stdlib.h>
#include <mem.h>
#include "LINEAR_SEQUENCE.h"
#include <stdbool.h>
/*When I wrote this code, only God and I known what I had to do. Now even God doesn't.*/

#define DynamicArrayGrowthFactor 2
#define StartContainerSize 1
#define IS_INVALID(handle)(handle == LSQ_HandleInvalid)

typedef enum {
    BEFOREFIRST,
    DEREFENCABLE,
    PASTREAR,
    UNKNOWN,
} IteratorState;

typedef struct {
    LSQ_BaseTypeT *ArrData;
    LSQ_IntegerIndexT FirstIndex, LastIndex;
    int RealSize, VirtualSize;
} Container, *ContainerP;

typedef struct {
    ContainerP Container;
    LSQ_IntegerIndexT Current;
} Iterator, *IteratorP;

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 * My internal functions needed to simplify code of some API functions *
 -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
static IteratorState GetState(IteratorP iter) {
    if (IS_INVALID(iter)) return UNKNOWN;
    if ((iter->Current >= 0) && ((iter->Current < iter->Container->VirtualSize)))
        return DEREFENCABLE;
    if (iter->Current < 0)
        return BEFOREFIRST;
    if (iter->Current >= iter->Container->VirtualSize)
        return PASTREAR;
    return UNKNOWN;
}

static IteratorP CreateIterator(ContainerP cont, int index) {
    IteratorP iter = (IteratorP) malloc(sizeof(Iterator));
    if (IS_INVALID(iter))
        return LSQ_HandleInvalid;
    iter->Container = cont;
    iter->Current = index;
    return iter;
}

static void TailMove(ContainerP cont, int oldSize) {
    int sizeOfTale = (oldSize - cont->FirstIndex);
    LSQ_BaseTypeT *buff = (LSQ_BaseTypeT *) malloc(sizeOfTale * sizeof(LSQ_BaseTypeT));
    memcpy(buff, cont->ArrData + cont->FirstIndex, sizeOfTale * sizeof(LSQ_BaseTypeT));
    memcpy(cont->ArrData + cont->RealSize - sizeOfTale, buff, sizeOfTale * sizeof(LSQ_BaseTypeT));
    cont->FirstIndex = cont->RealSize - sizeOfTale;
    free(buff);
}

static void SetContainerSize(ContainerP cont, int size) {
    if (IS_INVALID(cont))
        return;
    LSQ_BaseTypeT *buff = (LSQ_BaseTypeT *) realloc(cont->ArrData, size * sizeof(LSQ_BaseTypeT));
    if (IS_INVALID(buff))
        return;
    int oldSize = cont->RealSize;
    cont->ArrData = buff;
    cont->RealSize = size;
    if (cont->FirstIndex > cont->LastIndex)
        TailMove(cont, oldSize);
}

static void DataShift(ContainerP cont, LSQ_IntegerIndexT index, int size, int dir) {
    LSQ_BaseTypeT *buff = (LSQ_BaseTypeT *) malloc(size * sizeof(LSQ_BaseTypeT));
    memcpy(buff, cont->ArrData + index, size * sizeof(LSQ_BaseTypeT));
    memcpy(cont->ArrData + index + dir, buff, size * sizeof(LSQ_BaseTypeT));
    free(buff);
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 * Implementation of API functions *
 -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
LSQ_HandleT LSQ_CreateSequence(void) {
    ContainerP cont = (ContainerP) malloc(sizeof(Container));
    if (IS_INVALID(cont))
        return LSQ_HandleInvalid;
    cont->ArrData = (LSQ_BaseTypeT *) malloc(StartContainerSize * sizeof(LSQ_BaseTypeT));
    if (IS_INVALID(cont->ArrData)) {
        free(cont);
        return LSQ_HandleInvalid;
    }
    cont->FirstIndex = cont->LastIndex = cont->VirtualSize = 0;
    cont->RealSize = StartContainerSize;
    return (LSQ_HandleT) cont;
}

void LSQ_DestroySequence(LSQ_HandleT handle) {
    if (IS_INVALID(handle))
        return;
    ContainerP cont = (ContainerP) handle;
    if (!IS_INVALID(cont->ArrData))
        free(cont->ArrData);
    free(handle);
}

LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle) {
    return (IS_INVALID(handle) ? -1 : ((ContainerP) handle)->VirtualSize);
}

int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator) {
    return (GetState((IteratorP) iterator) == DEREFENCABLE);
}

int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator) {
    return (GetState((IteratorP) iterator) == PASTREAR);
}

int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator) {
    return (GetState((IteratorP) iterator) == BEFOREFIRST);
}

LSQ_BaseTypeT *LSQ_DereferenceIterator(LSQ_IteratorT iterator) {
    if (!LSQ_IsIteratorDereferencable(iterator))
        return LSQ_HandleInvalid;
    IteratorP iter = (IteratorP) iterator;
    int index = (iter->Container->FirstIndex + iter->Current) % iter->Container->RealSize;
    return iter->Container->ArrData + index;
}

LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index) {
    return IS_INVALID(handle) ? LSQ_HandleInvalid : CreateIterator((ContainerP) handle, index);;
}

LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle) {
    return IS_INVALID(handle) ? LSQ_HandleInvalid : LSQ_GetElementByIndex(handle, 0);
}

LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle) {
    return IS_INVALID(handle) ? LSQ_HandleInvalid : LSQ_GetElementByIndex(handle, ((ContainerP) handle)->VirtualSize);
}

void LSQ_DestroyIterator(LSQ_IteratorT iterator) {
    if (!IS_INVALID(iterator))
        free(iterator);
}

void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift) {
    if (!IS_INVALID(iterator))
        ((IteratorP) iterator)->Current += shift;
}

void LSQ_AdvanceOneElement(LSQ_IteratorT iterator) {
    LSQ_ShiftPosition(iterator, 1);
}

void LSQ_RewindOneElement(LSQ_IteratorT iterator) {
    LSQ_ShiftPosition(iterator, -1);
}

void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos) {
    if (!IS_INVALID(iterator))
        LSQ_ShiftPosition(iterator, pos - ((IteratorP) iterator)->Current);
}

void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement) {
    if (IS_INVALID(iterator) || LSQ_IsIteratorBeforeFirst(iterator))
        return;
    IteratorP iter = (IteratorP) iterator;
    ContainerP cont = iter->Container;
    if (cont->VirtualSize == cont->RealSize)
        SetContainerSize(cont, cont->RealSize * DynamicArrayGrowthFactor);
    if (iter->Current == 0) {
        LSQ_InsertFrontElement((LSQ_HandleT) iter->Container, newElement);
        return;
    }
    if (iter->Current == cont->VirtualSize) {
        LSQ_InsertRearElement((LSQ_HandleT) iter->Container, newElement);
        return;
    }
    if (!LSQ_IsIteratorDereferencable(iterator))
        return;
    int index = cont->FirstIndex + iter->Current;
    if (cont->FirstIndex <= cont->LastIndex) {
        if (cont->LastIndex == (cont->RealSize - 1)) {
            cont->ArrData[0] = cont->ArrData[cont->LastIndex];
            DataShift(cont, index, cont->LastIndex - index, 1);
        } else
            DataShift(cont, index, cont->LastIndex - index + 1, 1);
    } else {
        if (index <= (cont->RealSize - 1)) {
            DataShift(cont, 0, cont->LastIndex + 1, 1);
            cont->ArrData[0] = cont->ArrData[cont->RealSize - 1];
            if (index < (cont->RealSize - 1))
                DataShift(cont, index, cont->RealSize - 1 - index, 1);
        } else {
            index %= cont->RealSize;
            DataShift(cont, index, cont->LastIndex - (index) + 1, 1);
        }
    }
    cont->LastIndex = (cont->LastIndex + cont->RealSize + 1) % cont->RealSize;
    cont->ArrData[(cont->FirstIndex + iter->Current) % cont->RealSize] = newElement;
    cont->VirtualSize++;
}

void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element) {
    if (IS_INVALID(handle))
        return;
    ContainerP cont = (ContainerP) handle;
    if (cont->VirtualSize == cont->RealSize)
        SetContainerSize(cont, cont->RealSize * DynamicArrayGrowthFactor);
    cont->FirstIndex = (cont->FirstIndex + cont->RealSize - 1) % cont->RealSize;
    cont->ArrData[cont->FirstIndex] = element;
    cont->VirtualSize++;
}

void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element) {
    if (IS_INVALID(handle))
        return;
    ContainerP cont = (ContainerP) handle;
    if (cont->VirtualSize == cont->RealSize)
        SetContainerSize(cont, cont->RealSize * DynamicArrayGrowthFactor);
    cont->LastIndex = (cont->LastIndex + cont->RealSize + 1) % cont->RealSize;
    cont->ArrData[cont->LastIndex] = element;
    cont->VirtualSize++;
}

void LSQ_DeleteGivenElement(LSQ_IteratorT iterator) {
    if (IS_INVALID(iterator) || LSQ_IsIteratorBeforeFirst(iterator) || LSQ_IsIteratorPastRear(iterator))
        return;
    IteratorP iter = (IteratorP) iterator;
    ContainerP cont = iter->Container;
    if (LSQ_GetSize((LSQ_HandleT) cont) == 0)
        return;
    if (iter->Current == 0) {
        LSQ_DeleteFrontElement((LSQ_HandleT) iter->Container);
        return;
    }
    if (iter->Current == cont->VirtualSize - 1) {
        LSQ_DeleteRearElement((LSQ_HandleT) iter->Container);
        return;
    }
    if (!LSQ_IsIteratorDereferencable(iterator))
        return;
    int index = cont->FirstIndex + iter->Current;
    if (cont->FirstIndex <= cont->LastIndex) {
        DataShift(cont, index + 1, cont->LastIndex - index, -1);
    } else {
        if (index > (cont->RealSize - 1)) {
            index %= cont->RealSize;
            DataShift(cont, index + 1, cont->LastIndex - index, -1);
        } else {
            if (index < (cont->RealSize - 1))
                DataShift(cont, index + 1, cont->RealSize - 1 - index, -1);
            cont->ArrData[cont->RealSize - 1] = cont->ArrData[0];
            DataShift(cont, 1, cont->LastIndex, -1);
        }
    }
    cont->LastIndex = (cont->LastIndex + cont->RealSize - 1) % cont->RealSize;
    cont->VirtualSize--;
}

void LSQ_DeleteFrontElement(LSQ_HandleT handle) {
    if (IS_INVALID(handle) || (((ContainerP) handle)->VirtualSize <= 0))
        return;
    ContainerP cont = (ContainerP) handle;
    cont->FirstIndex = (cont->FirstIndex + cont->RealSize + 1) % cont->RealSize;
    cont->VirtualSize--;
}

void LSQ_DeleteRearElement(LSQ_HandleT handle) {
    if (IS_INVALID(handle) || (((ContainerP) handle)->VirtualSize <= 0))
        return;
    ContainerP cont = (ContainerP) handle;
    cont->LastIndex = (cont->LastIndex + cont->RealSize - 1) % cont->RealSize;
    cont->VirtualSize--;
}