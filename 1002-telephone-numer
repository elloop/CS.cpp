#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 电话号码结果体：号码、重复次数、下一个号码的链接.
typedef struct Phone {
    char phoneNumber[256];
    int repeatCount;
    struct Phone * link;
} *TelephoneItemPtr, TelephoneItem;

// 标准化电话号码.
char* standardizePhoneNumber(char * phone) {
    static char phoneCharMap[] = "2223334445556667077888999";
    char * result = phone;
    char copy[256];
    int i, j;
    strcpy(copy, phone);
    i = 0;
    j = 0;
    for (i=0; i<strlen(copy); ++i) {
        if (copy[i] == '-') {
            continue;
        } else if (copy[i] < 'A') {
            result[j++] = copy[i];
        } else {
            result[j++] = phoneCharMap[copy[i]-'A'];
        }
        if (j == 3) {
            result[j++] = '-';
        }
    }
    result[j] = 0;
    return result;
}

// 释放内存.
void freePhones(TelephoneItemPtr head) {
    TelephoneItemPtr p = head;
    TelephoneItemPtr q = p;
    while (p) {
        q = p->link;
        free(p);
        p = q;
    }
}

// 打印计算结果.
void printResult(TelephoneItemPtr head, int duplicate) {
    if (duplicate) {
        TelephoneItemPtr p = head;
        while (p) {
            if (p->repeatCount > 1) {
                printf("%s %d\n", p->phoneNumber, p->repeatCount);
            }
            p = p->link;
        }
    }
    else {
        printf("No duplicates.\n");
    }
}

// 打印电话号码列表.
void printPhoneList(TelephoneItemPtr head) {
    TelephoneItemPtr p = head;
    printf("===================== list begin =======================\n");
    while (p) {
        printf("%s\n", p->phoneNumber);
        p = p->link;
    }
    printf("===================== list end =======================\n");

}

int main(void) {
    int recordNum = 0;
    TelephoneItemPtr head = NULL;
    TelephoneItemPtr tail = NULL;
    TelephoneItemPtr tmp = NULL;

    int duplicate = 0;
    char temp[256];
    scanf("%d", &recordNum);
    getchar();

    while (recordNum--) {
        TelephoneItemPtr p = head;
        TelephoneItemPtr q = NULL;
        char * standardForm = NULL;

        // 读取号码，并标准化,
        gets(temp);
        standardForm = standardizePhoneNumber(temp);

        // 寻找合适的插入位置。
        // 1. 新号码 == 已存在的号码，则给已存在的号码重复数加1.
        // 2. 按照升序查找合适的插入位置，for 循环将在找到第一个大于新号码的地方停下来，此时：
        // p 指向了第一个大于新号码的地址，q 是p前面的节点。那么将新节点插在q之后就好了.
        // 3. 需要考虑，新号码小于所有号码，和大于所有号码的可能.
        for (; p && (strcmp(p->phoneNumber, standardForm) == -1); q=p, p=p->link) ;

        if (!p) {
            // 新号码大于所有号码.
            tmp = (TelephoneItemPtr) malloc(sizeof (TelephoneItem));
            if (NULL == tmp) {
                exit(0);
            }
            strcpy(tmp->phoneNumber, standardForm);
            tmp->repeatCount = 1;
            tmp->link = NULL;
            if (!head) {
                head = tmp;
                tail = tmp;
            }
            else {
                tail->link = tmp;
                tail = tmp;
            }
        }
        else if (strcmp(p->phoneNumber, standardForm) == 0) {
            // 新号码和p所指向的号码一样.
            duplicate = 1;
            p->repeatCount += 1;
        } else {
            // 新号码不大于所有号码.
            tmp = (TelephoneItemPtr) malloc(sizeof (TelephoneItem));
            if (NULL == tmp) {
                exit(0);
            }
            strcpy(tmp->phoneNumber, standardForm);
            tmp->repeatCount = 1;
            tmp->link = p;
            if (!q) {
                // 新号码小于所有号码.
                head = tmp;
            } else {
                // 新号码插入到中间位置.
                q->link = tmp;
            }
        }
    }
    //printPhoneList(head);
    // 打印结果.
    printResult(head, duplicate);
    // 释放内存.
    freePhones(head);
    return 0;
}
