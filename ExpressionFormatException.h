//
// Created by Administrator on 2019/9/18 0018.
//

#ifndef CALCULATOR_EXPRESSIONFORMATEXCEPTION_H
#define CALCULATOR_EXPRESSIONFORMATEXCEPTION_H

#include "public.h"
#include <exception>

class ExpressionFormatException : public std::exception {
private:
    char *msg;
public:
    explicit ExpressionFormatException(char *m) : msg(m) {}

    const char *what() const noexcept override {
        return msg;
    }
};

#endif //CALCULATOR_EXPRESSIONFORMATEXCEPTION_H
