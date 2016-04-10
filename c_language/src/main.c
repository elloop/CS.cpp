#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isalphabetic(char c)
{
    if ( ( c >= 'A' && c <= 'Z' ) || ( c >= 'a' && c <= 'z' ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int findLongWord(char *str)
{
    int i, len = 0, length = 0, place = 0, flag = 1, point;
    for ( i = 0; i <= strlen(str); ++i )
    {
        if ( isalphabetic(str[i]) )
        {
            if ( flag )
            {
                point = i;
                flag = 0;
            }
            else
            {
                ++len;
            }
        }
        else
        {
            flag = 1;
            if ( len >= length )
            {
                length = len;
                len = 0;
                place = point;
            }
        }
    }
    return place;
}

// memory leak check.
#if defined(_MSC_VER) && defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
// with detail description of memory leak.
#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
void turnOnMemroyCheck()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}
#endif

#include "ds/graph_test.h"
int main(void)
{
   /* char str[100];
    int i;
    gets(str);
    printf("word=");

    for ( i = findLongWord(str); isalphabetic(str[i]); ++i )
    {
        printf("%c", str[i]);
    }*/

    mgraph_t g;

    create_mgraph(&g);
    delete_mgraph(&g);

    return 0;
}

