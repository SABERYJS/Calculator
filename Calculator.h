//
// Created by Administrator on 2019/9/19 0019.
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include "public.h"
#include "ExpressionParser.h"
#include "BinaryExpression.h"

class Calculator {
public:
    Calculator() {}

     int Calculate(const  char *expression) {
        auto parser = ExpressionParser(expression);
        parser.Parse();
        auto exp = BinaryExpression(parser.GetContainer());
        cout<<exp.Calculate();
    }
};

#endif //CALCULATOR_CALCULATOR_H
