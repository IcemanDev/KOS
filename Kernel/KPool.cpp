#include "Kernel.h"

UInt32 KPoolIndexOf(PoolHeader *hdr, void *element)
{
    Int32 index = (((UInt8*) element - (UInt8*) &(hdr->elements[hdr->poolSize]))) / hdr->elementSize;
    if (index >= 0 && index < hdr->poolSize)
        return index;
    return -1;
}

void* KPoolElementAt(PoolHeader *hdr, UInt32 index)
{
    if (index < 0 || index >= hdr->poolSize)
        return NULL;
    return (UInt8*) &(hdr->elements[hdr->poolSize]) + index * hdr->elementSize;
}

PoolHeader *KPoolAllocate(UInt32 poolID, UInt32 size, UInt32 elementSize)
{
    UInt32 requiredMemory = sizeof(PoolHeader) + size * sizeof(ElementEntry) + size * elementSize;

    PoolHeader *hdr = (PoolHeader*) KVirtualAlloc(requiredMemory, 0);

    hdr->poolID = poolID;
    hdr->poolSize = size;
    hdr->elementSize = elementSize;
    hdr->firstFree = hdr->elements;

    for (int i = 0; i < size; i++)
    {
        hdr->elements[i].next = &(hdr->elements[i + 1]);
        hdr->elements[i].pointer = KPoolElementAt(hdr, i);
    }

    hdr->elements[size - 1].next = 0;

    return hdr;
}

void *KPoolAcquireElement(PoolHeader *hdr)
{
    if (!hdr->firstFree)
    {
        KDebugPrintF(L"TODO: Grow pool %08x...\r\n", hdr->poolID);
        return NULL;
    }

    ElementEntry *f = hdr->firstFree;

    hdr->firstFree = f->next;

    void* ptr = f->pointer;

    f->pointer = NULL;
    f->next = NULL;

    return ptr;
}

void KPoolReleaseElement(PoolHeader *hdr, void* element)
{
    UInt32 index = KPoolIndexOf(hdr, element);

    ElementEntry *f = &(hdr->elements[index]);

    f->pointer = KPoolElementAt(hdr, index);
    f->next = hdr->firstFree;

    hdr->firstFree = f;
}