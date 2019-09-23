//
// Created by Administrator on 2019/9/18 0018.
//

#ifndef CALCULATOR_OPERAND_H
#define CALCULATOR_OPERAND_H

template<typename T> class Operand {
private:
    T value;
public:
    explicit Operand(T t) : value(t) {}

    T GetValue() {
        return value;
    }
};

#endif //CALCULATOR_OPERAND_H
