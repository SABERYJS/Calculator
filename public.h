//
// Created by Administrator on 2019/9/18 0018.
//

#ifndef CALCULATOR_PUBLIC_H
#define CALCULATOR_PUBLIC_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include "Memory.h"

#define CHAR_LEFT_PARENT '('
#define CHAR_RIGHT_PARENT  ')'
#define CHAR_PLUS '+'
#define CHAR_MINUS '-'
#define CHAR_MULTIPLE '*'
#define CHAR_DIVISOR  '/'
#define CHAR_DOT '.'

#define CharIsLeftParent(c) (c==CHAR_LEFT_PARENT)
#define CharIsRightParent(c) (c==CHAR_RIGHT_PARENT)
#define CharIsPlus(c) (c==CHAR_PLUS)
#define CharIsMinus(c) (c==CHAR_MINUS)
#define CharIsMultiple(c) (c==CHAR_MULTIPLE)
#define CharIsDivisor(c) (c==CHAR_DIVISOR)
#define CharIsDot(c) (c==CHAR_DOT)
#define CharIsNumberic(c)  (c>='0'  && c<='9')
#endif //CALCULATOR_PUBLIC_H

