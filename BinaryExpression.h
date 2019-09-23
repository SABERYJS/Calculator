//
// Created by Administrator on 2019/9/19 0019.
//

#ifndef CALCULATOR_BINARYEXPRESSION_H
#define CALCULATOR_BINARYEXPRESSION_H

#include "public.h"
#include "vector"
#include "Token.h"
#include "BaseException.h"
#include "ExpressionFormatException.h"

class BinaryExpression : public BaseException {
private:
    vector<Token *>::iterator itb;
    vector<Token *>::iterator ite;
    bool reach_last;
    vector<Token *>::iterator predict_iterator;
    bool predict_reach_last;
    bool expression_is_empty;
    vector<Token *> tokens;
public:
    explicit BinaryExpression(vector<Token *> tokens) {
        reach_last = false;
        predict_reach_last = false;
        expression_is_empty = false;
        this->tokens = tokens;
        itb = this->tokens.begin();
        ite = this->tokens.end();
    }

    double Calculate() {
        Token *opd_one = ConsumeToken();
        if (!opd_one) {
            //expression is empty
            ThrowException();
            return 0;
        }
        if (!opd_one->GetIsOperand()) {
            ThrowException();
            return 0;
        }
        Token *optr = nullptr;
        Token *opd_two = nullptr;
        if (reach_last) {
            //no more token,so just return it
            return stod(opd_one->GetToken());
        } else {
            optr = ConsumeToken();
            if (!optr->CheckIsOperator()) {
                //( or )
                ThrowException();
                return 0;
            }
            if (reach_last) {
                //second operand is required
                ThrowException();
                return 0;
            }
            opd_two = PredictToken();
            //two operator  checked
            if (opd_two->CheckIsOperator()) {
                ThrowException();
                return 0;
            }
            if (opd_two->GetIsOperand()) {
                bool should_calculate = false;
                if (optr->OperatorHasHighPriority()) {
                    should_calculate = true;
                } else if (predict_reach_last) {
                    should_calculate = true;
                } else {
                    Token *next = PredictToken();
                    if (next->CheckIsParentheses()) {
                        ThrowException();
                        return 0;
                    }
                    if (!next->OperatorHasHighPriority()) {
                        should_calculate = true;
                    }
                }
                //operand checked
                if (should_calculate) {
                    //no more token to check
                    double d3 = CalculateValue(opd_one, opd_two, optr);
                    if (predict_reach_last) {
                        return d3;
                    } else {
                        ConsumeToken();//consume third operand
                        auto tok = new Token(to_string(d3).data(), true);
                        InsertToken(tok);
                        auto exp = BinaryExpression(tokens);
                        return exp.Calculate();
                    }
                } else {
                    auto tok = BinaryExpression(tokens);
                    return CalculateSubValue(opd_one, tok, optr);
                }
            } else {
                //Parentheses detected
            }
        }
    }

private:

    static double CalculateToken(const Token *token) {
        return stod(token->GetToken());
    }

    static double CalculateSubValue(const Token *token, BinaryExpression &exp, const Token *optr) {
        double dt = CalculateToken(token);
        double de = exp.Calculate();
        int a = 1;
        return CalculateAccordingToOperator(dt,de, optr);
    }

    static double CalculateValue(const Token *o1, const Token *o2, const Token *optr) {
        double d1, d2, d3;
        d1 = stod(o1->GetToken());
        d2 = stod(o2->GetToken());
        return CalculateAccordingToOperator(d1, d2, optr);
    }

    static double CalculateAccordingToOperator(double d1, double d2, const Token *optr) {
        double d3;
        switch (optr->GetToken()[0]) {
            case CHAR_MULTIPLE:
                d3 = d1 * d2;
                break;
            case CHAR_PLUS:
                d3 = d1 + d2;
                break;
            case CHAR_MINUS:
                d3 = d1 - d2;
                break;
            case CHAR_DIVISOR:
                if (d2 == 0) {
                    ThrowException();
                    return 0;
                }
                d3 = d1 / d2;
                break;
        }
        return d3;
    }

    void EraseToken() {
        tokens.erase(itb);
        itb = tokens.begin();
        ite = tokens.end();
    }

    /**
     * insert token at the beginning
     * **/
    void InsertToken(Token *token) {
        tokens.insert(tokens.begin(), token);
    }

    /**
     * consume iterator
     * **/
    Token *ConsumeToken() {
        Token *token = nullptr;
        if (reach_last) {
            return nullptr;
        } else {
            token = *itb;
            EraseToken();
            if (itb == ite) {
                reach_last = true;
                predict_reach_last = true;
            } else {
                predict_iterator = itb;
            }
            return token;
        }
    }

    /**
     * predict token
     * **/
    Token *PredictToken() {
        if (predict_reach_last) {
            return nullptr;
        } else {
            Token *token = *predict_iterator;
            if (predict_iterator == ite) {
                predict_reach_last = true;
            } else {
                ++predict_iterator;
            }
            return token;
        }
    }

    static void ThrowException() {
        throw ExpressionFormatException((char *) "Check Expression");
    }
};


#endif //CALCULATOR_BINARYEXPRESSION_H
