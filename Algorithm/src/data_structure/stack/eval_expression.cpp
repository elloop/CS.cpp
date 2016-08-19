#include "stack.h"
#include <string>
#include <cassert>
#include <unordered_map>

NS_BEGIN(elloop);

/*
 *
 *  1  : oper1 > oper2
 *  0  : oper1 == oper2
 *  -1 : oper1 < oper2
 *
 */
int compareOper(char oper1, char oper2) {
    using OperMap = std::unordered_map<char, std::unordered_map<char, int>>;

    OperMap operMap;

    operMap['+']['+'] = 1;   operMap['-']['+'] = 1;   operMap['*']['+'] = 1; 
    operMap['+']['-'] = 1;   operMap['-']['-'] = 1;   operMap['*']['-'] = 1; 
    operMap['+']['*'] = -1;  operMap['-']['*'] = -1;  operMap['*']['*'] = 1; 
    operMap['+']['/'] = -1;  operMap['-']['/'] = -1;  operMap['*']['/'] = 1; 
    operMap['+']['('] = -1;  operMap['-']['('] = -1;  operMap['*']['('] = -1;
    operMap['+'][')'] = 1;   operMap['-'][')'] = 1;   operMap['*'][')'] = 1; 
    operMap['+']['#'] = 1;   operMap['-']['#'] = 1;   operMap['*']['#'] = 1; 
                                                   
                                                      operMap['/']['+'] = 1;                                                      
                                                      operMap['/']['-'] = 1; 
                                                      operMap['/']['*'] = 1; 
                                                      operMap['/']['/'] = 1; 
                                                      operMap['/']['('] = -1;
                                                      operMap['/'][')'] = 1; 
                                                      operMap['/']['#'] = 1; 

                                                      operMap['#']['+'] = -1;
                                                      operMap['#']['-'] = -1;
                                                      operMap['#']['*'] = -1;
                                                      operMap['#']['/'] = -1;
                                                      operMap['#']['('] = -1;
                                                      operMap['#'][')'] = 2;
                                                      operMap['#']['#'] = 0;

                                                      operMap[')']['+'] = 1;
                                                      operMap[')']['-'] = 1;
                                                      operMap[')']['*'] = 1;
                                                      operMap[')']['/'] = 1;
                                                      operMap[')']['('] = 2;
                                                      operMap[')'][')'] = 1;
                                                      operMap[')']['#'] = 1;

                                                      operMap['(']['+'] = -1; 
                                                      operMap['(']['-'] = -1; 
                                                      operMap['(']['*'] = -1; 
                                                      operMap['(']['/'] = -1; 
                                                      operMap['(']['('] = -1; 
                                                      operMap['('][')'] = 0;  
                                                      operMap['(']['#'] = 1;  
    return operMap[oper1][oper2];

    // auto isSpecial = [ ](char c) -> bool { return (coperMap['(']['#'] = 2;   == ')' || c == '(' || c == '#'); };
    // auto isAdvance = [ ](char c) -> bool { return (c == '*' || c == '/'); };
    // auto isNormal  = [ ](char c) -> bool { return (c == '+' || c == '-'); };

    // if (oper1 == oper2) {
    //     if (!isSpecial(oper1)) {
    //         return 1;
    //     }
    //     else {
    //         if (oper1 == '(') {
    //             return -1;
    //         }
    //         else if (oper1 == ')') {
    //             return 1;
    //         }
    //         else if (oper1 == '#') {
    //             return 0;
    //         }
    //         else {
    //             // should be unreachable.
    //             assert(false);
    //         }
    //     }
    // }
    // else {

    // }
}

double evalBinaryOper(double opnd1, char oper, double opnd2) {
    double res(0);
    switch (oper) {
        case '+':
            res = opnd1 + opnd2;
            break;
        case '-':
            res = opnd1 - opnd2;
            break;
        case '*':
            res = opnd1 * opnd2;
            break;
        case '/':
            assert(opnd2 != 0);
            res = opnd1 / opnd2;
            break;
        default:
            assert(false);
    }
    return 0;
}


double evalExpression(const std::string &s) {
    double res(0);

    Stack<double> operStack;
    Stack<char> opndStack;
    operStack.push('#');

    auto isOper = [](char c) -> bool {
        return (std::string("+-*/()#").find(c) != std::string::npos); 
    };

    auto fetchAnElem = [isOper] (const std::string &s, size_t &index, std::string &ret) -> bool {
        ret.clear();
        if (index >= s.length() || index < 0) { return false; }
        if (isOper(s[index])) {
            ret = s[index++];
        }
        else {
            while (index < s.length() && !isOper(s[index])) {
                ret.append(1, s[index++]);
            }
        }
        return true;
    };

    auto testFetch = [&] () {
        std::string ret;
        size_t j(0);
        psln(j);
        while (fetchAnElem(s, j, ret)) {
            psln(ret);
            psln(j);
        }
    };

    size_t i(0);
    std::string ret;
    while (fetchAnElem(s, i, ret)  && ret != '#' && operStack.top() != '#') {
        if (!isOper(ret[0])) {
            // opndStack.push(folly::convertToDoulbe(ret));
        }
        else {
            auto top = operStack.top();
            switch (compareOper(top, s[i])) {
                case -1:
                    operStack.push(s[i]);
                    break;
                case 0:
                    operStack.pop();
                    break;
                case 1:
                    auto opnd1 = opndStack.top(); opndStack.pop();
                    auto opnd2 = opndStack.top(); opndStack.pop();
                    opndStack.push(evalBinaryOper(opnd1, top, opnd2));
                    operStack.pop();
                    break;
            }
        }
    }
    return res;
}


RUN_GTEST(StackTest, EvalExpression, @@);

std::string epress("(1+2+3+4)*2+3*4+10/2");
psln(evalExpression(epress));

END_TEST;

NS_END(elloop);
