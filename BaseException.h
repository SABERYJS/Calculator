//
// Created by Administrator on 2019/9/20 0020.
//

#ifndef CALCULATOR_BASEEXCEPTION_H
#define CALCULATOR_BASEEXCEPTION_H

#include "public.h"

class BaseException : std::exception {
    const char *what() const noexcept override {
        return "Expression Error";
    }
};

#endif //CALCULATOR_BASEEXCEPTION_H
