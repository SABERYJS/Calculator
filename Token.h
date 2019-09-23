//
// Created by Administrator on 2019/9/18 0018.
//

#ifndef CALCULATOR_TOKEN_H
#define CALCULATOR_TOKEN_H

#include "public.h"

using namespace std;

class Token {
private:
    string tk;
    bool is_operand;
public:
    explicit Token(const char *s, bool is_operand) : tk(s) {
        this->is_operand = is_operand;
    }

    /*ostream &operator<<(ostream &out) {
        out << tk << endl;
    }*/

    string GetToken() const {
        return tk;
    }

    bool GetIsOperand() {
        return is_operand;
    }

    /**
     * '*' and '/' has high priority
     * **/
    bool OperatorHasHighPriority() {
        return CharIsMultiple(tk[0]) || CharIsDivisor(tk[0]);
    }

    bool CheckIsOperator() {
        return CharIsDivisor(tk[0]) || CharIsMinus(tk[0]) || CharIsPlus(tk[0]) || CharIsMultiple(tk[0]);
    }

    bool CheckIsParentheses() {
        return CharIsLeftParent(tk[0]) || CharIsRightParent(tk[0]);
    }

    bool CheckIsLeftParentheses() {
        return CharIsLeftParent(tk[0]);
    }

    bool CheckIsRightParentheses() {
        return CharIsRightParent(tk[0]);
    }
};

#endif //CALCULATOR_TOKEN_H
