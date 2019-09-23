//
// Created by Administrator on 2019/9/18 0018.
//

#ifndef CALCULATOR_MEMORY_H
#define CALCULATOR_MEMORY_H

#include "public.h"

char *MemAlloc(size_t l) {
    char *b = (char *) malloc(l);
    if (!b) {
        return NULL;
    } else {
        memset(b, 0, l);
        return b;
    }
}

#endif //CALCULATOR_MEMORY_H
