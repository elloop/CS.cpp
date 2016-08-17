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

    operMap['+']['+'] = 1;                          operMap['*']['+'] = 1; 
    operMap['+']['-'] = 1;                          operMap['*']['-'] = 1; 
    operMap['+']['*'] = -1;                         operMap['*']['*'] = 1; 
    operMap['+']['/'] = -1;                         operMap['*']['/'] = 1; 
    operMap['+']['('] = -1;                         operMap['*']['('] = -1;
    operMap['+'][')'] = 1;                          operMap['*'][')'] = 1; 
    operMap['+']['#'] = 1;                          operMap['*']['#'] = 1; 

                            operMap['-']['+'] = 1;                        
                            operMap['-']['-'] = 1;                        
                            operMap['-']['*'] = -1;                       
                            operMap['-']['/'] = -1;                       
                            operMap['-']['('] = -1;                       
                            operMap['-'][')'] = 1;                        
                            operMap['-']['#'] = 1;                        

     operMap[')']['+'] = 1;                         operMap['#']['+'] = -1;
     operMap[')']['-'] = 1;                         operMap['#']['-'] = -1;
     operMap[')']['*'] = 1;                         operMap['#']['*'] = -1;
     operMap[')']['/'] = 1;                         operMap['#']['/'] = -1;
     operMap[')']['('] = 2;                         operMap['#']['('] = -1;
     operMap[')'][')'] = 1;                         operMap['#'][')'] = 2;
     operMap[')']['#'] = 1;                         operMap['#']['#'] = 0;


     operMap['/']['+'] = 1;                          operMap['(']['+'] = -1;
     operMap['/']['-'] = 1;                          operMap['(']['-'] = -1;
     operMap['/']['*'] = 1;                          operMap['(']['*'] = -1;
     operMap['/']['/'] = 1;                          operMap['(']['/'] = -1;
     operMap['/']['('] = -1;                         operMap['(']['('] = -1;
     operMap['/'][')'] = 1;                          operMap['('][')'] = 0; 
     operMap['/']['#'] = 1;                          operMap['(']['#'] = 2; 

    // auto isSpecial = [ ](char c) -> bool { return (c == ')' || c == '(' || c == '#'); };
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

double evalExpression(const std::string &s) {
    double res(0);

    Stack<char> operStack;
    Stack<char> opndStack;
    operStack.push('#');

    auto isOper = [](char c) -> bool {
        return (std::string("+-*/()#").find(c) != std::string::npos); 
    }

    size_t i(0);
    while (s[i] != '#' && operStack.top() != '#') {
        if (!isOper(s[i])) {
            opndStack.push(s[i]);
        }
        else {

        }
    }
    return res;
}


RUN_GTEST(StackTest, EvalExpression, @@);

std::string epress("(1+2+3+4)*2+3*4+10/2");
psln(evalExpression(epress));

END_TEST;

NS_END(elloop);
    // auto isSpecial = [ ](char c) -> bool { return (c == ')' || c == '(' || c == '#'); };
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

double evalExpression(const std::string &s) {
    double res(0);

    Stack<char> operStack;
    Stack<char> opndStack;
    operStack.push('#');

    auto isOper = [](char c) -> bool {
        return (std::string("+-*/()#").find(c) != std::string::npos); 
    }

    size_t i(0);
    while (s[i] != '#' && operStack.top() != '#') {
        if (!isOper(s[i])) {
            opndStack.push(s[i]);
        }
        else {

        }
    }
    return res;
}


RUN_GTEST(StackTest, EvalExpression, @@);

std::string epress("(1+2+3+4)*2+3*4+10/2");
psln(evalExpression(epress));

END_TEST;

NS_END(elloop);
