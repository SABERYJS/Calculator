//
// Created by Administrator on 2019/9/18 0018.
//

#ifndef CALCULATOR_EXPRESSIONPARSER_H
#define CALCULATOR_EXPRESSIONPARSER_H

#include "public.h"
#include "Token.h"
#include "ExpressionFormatException.h"
#include "MemoryAllocateException.h"

using namespace std;

class ExpressionParser {
private:
    string exp;
    vector<Token *> container;
    bool operand_matched;
    bool dot_matched;
    int operand_pos_start;
public:
    explicit ExpressionParser(const char *p) : exp(p) {
        container = vector<Token *>();
        ResetParseStatus();
    }

    void Parse() {
        int len = ExpressionLength();
        char c = 0;
        Token *token = nullptr;
        bool last = false;
        for (int j = 0; j < len; ++j) {
            last = (j == (len - 1));
            c = exp[j];
            if (!CharIsValid(c)) {
                ThrowExpressionException(j);
            }
            if (!CheckOperandMatched()) {
                if (CharIsNumberic(c)) {
                    SetOperandMatched(true);
                    SetOperandPosStart(j);
                } else if (CharIsDot(c)) {
                    ThrowExpressionException(j);
                }
            } else {
                if (!CharIsDot(c) && !CharIsNumberic(c)) {
                    //complete numeric matched
                    AddTokenToContainer(CreateToken(exp.data() + GetOperandPosStart(), OperandLength(j),true));
                    //add current token
                    AddTokenToContainer(CreateToken(exp.data() + j, 2, false));
                    ResetParseStatus();
                } else if (CharIsDot(c)) {
                    if (CheckDotMatched()) {
                        ThrowExpressionException(j);
                    } else {
                        if (last) {
                            ThrowExpressionException(j);
                        } else {
                            SetDotMatched(true);
                        }
                    }
                } else {
                    //number matched ,just skip it
                    if (last) {
                        AddTokenToContainer(CreateToken(exp.data() + GetOperandPosStart(), OperandLength(j) + 1,true));
                    }
                }
            }
        }
    }

    vector<Token *> GetContainer() {
        return container;
    }


private:

    void ResetParseStatus() {
        operand_matched = false;
        dot_matched = false;
        operand_pos_start = 0;
    }

    Token *CreateToken(const char *s, size_t l, bool is_operand) noexcept(false) {
        char *buf = MemAlloc(l);
        if (!buf) {
            throw MemoryAllocateException((char *) "Memory Allocate failed");
        } else {
            memcpy(buf, s, l - 1);
            auto token = new Token(buf,is_operand);
            return token;
        }
    }

    void AddTokenToContainer(Token *token) {
        container.push_back(token);
    }

    static inline bool CharIsValid(const char c) {
        return CharIsDivisor(c) || CharIsLeftParent(c) || CharIsRightParent(c) || CharIsPlus(c) || CharIsMinus(c) ||
               CharIsMultiple(c) || CharIsNumberic(c)||CharIsDot(c);
    }

    inline int ExpressionLength() {
        return exp.size();
    }

    inline void SetOperandMatched(bool matched) {
        operand_matched = matched;
    }

    inline void SetOperandPosStart(int pos) {
        operand_pos_start = pos;
    }

    inline int OperandLength(int end) {
        return (end - operand_pos_start + 1);
    }

    inline int GetOperandPosStart() {
        return operand_pos_start;
    }

    inline void SetDotMatched(bool matched) {
        dot_matched = matched;
    }

    inline bool CheckDotMatched() {
        return dot_matched;
    }

    inline bool CheckOperandMatched() {
        return operand_matched;
    }

    static inline void ThrowExpressionException(int pos) {
        throw ExpressionFormatException((char *) "expression format error checked,position is:" + pos);
    }
};

#endif //CALCULATOR_EXPRESSIONPARSER_H
