#include "grammar/cau_oj.h"
#include <stdio.h>
#include <string.h>
//---------------------- nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn ----------------------

//找一段字符串内的子字符串，输出子字符串重复次数，主函数中输入，并完成输出。被调用函数中完成重复次数计算。
//
//找abcdabcdabcd内abc重复次数
//
//input：
//
//abcdabcdabcd      //源字符串
//
//abc                      //子字符串
//
//output：
//
//3
int find_sub_str(const char * str, const char *sub) {
    int i, j, len1, len2, count, found;
    len1 = strlen(str);
    len2 = strlen(sub);
    if (len2 > len1) {
        return 0;
    }
    count = 0;
    for (i=0; i<len1 - len2 + 1; ++i) {
        found = 1;
        for (j=0; j<len2; ++j) {
            if (str[i+j] != sub[j]) {
                found = 0;
                break;
            }
        }
        if (found) {
            count = count + 1;
        }
    }
    return count;
}

void run_find_sub(void){
    char str[200];
    char sub[200];
    fgets(str, 200, stdin);
    str[strlen(str) - 1] = 0;
    fgets(sub, 200, stdin);
    sub[strlen(sub) - 1] = 0;
    printf("%d", find_sub_str(str, sub));
}


//---------------------- nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn ----------------------
//矩阵转至
void rotate(int a[][3], int row, int column){
    int i,j;
    for (i=0; i<column; ++i) {
        for (j=0; j<row; ++j) {
            printf("%d ", a[j][i]);
        }
        printf("\n");
    }
}

void run_rotate(void) {
    int a[2][3],i,j;
    for (i=0; i<2; ++i) {
        for (j=0; j<3; ++j) {
            scanf("%d,", &a[i][j]);
        }
    }
    rotate(a, 2, 3);
}

//---------------------- nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn ----------------------
//例如输入：abcdefg，按照首尾对应的位置进行位置交换，a和g交换，b和f交换，以此类推。
//
//input : abcdefgh
//
//    output : hgfedcba
void exchange_print(char *str) {
    int i,j,len;
    char temp;
    len = strlen(str);
    for (i=0, j=len-1; i<j; ++i, --j) {
        temp = str[j];
        str[j] = str[i];
        str[i] = temp;
    }
    printf("%s", str);
}

void run_exchange_print(void) {
    char str[200];
    gets(str);
    exchange_print(str);
}

void run_oj(void) {
    //run_find_sub();
    //run_rotate();
    run_exchange_print();
}

