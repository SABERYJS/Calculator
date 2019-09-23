//
// Created by Administrator on 2019/9/18 0018.
//

#ifndef CALCULATOR_MEMORYALLOCATEEXCEPTION_H
#define CALCULATOR_MEMORYALLOCATEEXCEPTION_H

#include "public.h"
#include <exception>

class MemoryAllocateException : public std::exception {
private:
    char *msg;
public:
    explicit MemoryAllocateException(char *m) : msg(m) {}

    const char *what() const noexcept override {
        return msg;
    }
};

#endif //CALCULATOR_MEMORYALLOCATEEXCEPTION_H
