#include "include/FirstOverview.h"
#include "include/FileSystemTest.h"

void printNPlus(int n) {
    for (int i=0; i<n; ++i) {
        printf("+");
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

int main(int argc, char* argv[]) {

    //overviewTest(argc, argv);

    //testFileSystem();
    //printS(41, 'X');

    // testFileSystem();
    testPthread();

    exit(0);
}


