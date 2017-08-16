#include "stack.h"
#include <string>
#include <cassert>
#include <unordered_map>
#include "util/StringUtil.h"

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
            res = opnd2 - opnd1; // fix minus bug, second push is 被减数
            break;
        case '*':
            res = opnd1 * opnd2;
            break;
        case '/':
            assert(opnd1 != 0);
            res = opnd2 / opnd1; // fix divide bug, second push is 被除数.
            break;
        default:
            assert(false);
    }
    return res;
}

/*
 * return: INT_MAX when fail.
 */
double evalExpression(const std::string &s) {

    using std::string;

    auto isOper = [](char c) -> bool {
        return (string("+-*/()#").find(c) != string::npos); 
    };

    auto fetchAnElem = [isOper] (const string &s, size_t &index, string &result) {
        result.clear();
        if (index >= s.length() || index < 0) { return; }
        if (isOper(s[index])) {
            result = s[index++];
        }
        else {
            while (index < s.length() && !isOper(s[index])) {
                result.append(1, s[index++]);
            }
        }
    };

    auto testFetch = [&] () {
        string result;
        size_t j(0);
        psln(j);
        while ((fetchAnElem(s, j, result), result != "")) {
            psln(result);
            psln(j);
        }
    };

    Stack<char> operStack;
    Stack<double> opndStack;

    size_t i(0);
    string elem;
    fetchAnElem(s, i, elem);
    assert(elem[0] == '#');
    operStack.push('#');

    fetchAnElem(s, i, elem);
    while (elem != "" && (elem[0] != '#' || operStack.top() != '#')) {
        psln(elem);
        if (!isOper(elem[0])) {
            opndStack.push(StringUtil::stod(elem));
            fetchAnElem(s, i, elem);
        }
        else {
            char oper = elem[0];
            auto top = operStack.top();
            switch (compareOper(top, oper)) {
                case -1:
                    operStack.push(oper);
                    fetchAnElem(s, i, elem);
                    break;
                case 0:
                    operStack.pop();
                    fetchAnElem(s, i, elem);
                    break;
                case 1:
                    auto opnd1 = opndStack.top(); opndStack.pop();
                    auto opnd2 = opndStack.top(); opndStack.pop();
                    opndStack.push(evalBinaryOper(opnd1, top, opnd2));
                    operStack.pop();
                    break;
            }
        }
        opndStack.dump("opndStack: ");
        operStack.dump("operStack: ");
    }

    if (opndStack.empty()) {
        return INT_MAX;
    }
    double ret = opndStack.top();
    opndStack.pop();
    return opndStack.empty() ? ret : INT_MAX;
}


BEGIN_TEST(StackTest, EvalExpression, @@);

// std::string epress("#(1+2+3+4)*2+3*4+10/2+(10+2)*10-100+3-60#");
std::string epress("#(1+2+3*4*(2+3)+10)#");
psln(epress);
psln(evalExpression(epress));

END_TEST;

NS_END(elloop);
