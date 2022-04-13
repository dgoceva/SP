// splint_c.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
int main()
{
    char c;
    while (c != 'x');
    {
        c = getchar();
        if (c = 'x')
            return 0;
        switch (c) {
        case '\n':
        case '\r':
            printf("Newline\n");
        default:
            printf("%c",c);
        }
    }
    return 0;
}

