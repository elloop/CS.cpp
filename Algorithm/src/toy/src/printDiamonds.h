#pragma once

#include "include/inc.h"

NS_BEGIN(elloop);

class PrintDiamonds {
public:

    void printNPlus(int n) {
        for (int i=0; i<n; ++i) {
            p("+");
        }
    }

    void printS(int lineWidth, char beginOfChar) {

        int         numOfPlus   = 0;
        int         cursor      = 0;

        cursor      = beginOfChar - 'A';
        beginOfChar = 'A';


        for (int i=1; i<lineWidth; i+=2) {

            numOfPlus = (lineWidth - i) / 2;

            printNPlus(numOfPlus);

            for (int k=0; k<i; ++k, ++cursor) {
                printf("%c", (beginOfChar + (cursor % 26)));
            }

            printNPlus(numOfPlus);

            putchar(10);    // new line.
        }

        for (int i=lineWidth-4; i>=1; i-=2) {
            numOfPlus = (lineWidth - i) / 2;
            printNPlus(numOfPlus);

            for (int k=0; k<i; ++k, ++cursor) {
                printf("%c", (beginOfChar + (cursor % 26)));
            }

            printNPlus(numOfPlus);

            putchar(10);    // new line.

        }
    }

    static void run() {
        PrintDiamonds p;
        p.printS(41, 'X');
    }
};

NS_END(elloop);
