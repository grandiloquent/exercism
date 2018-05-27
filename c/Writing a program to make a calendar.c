#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


#define p printf
int main()
{
    int d, y, no_lp, n, i = 1, j, nod[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    p("enter yr:");
    scanf("&#37;d", &y);

    no_lp = (y - 2001) / 4;

    /*no of leap yrs betwen 2001 and the yr*/

    d = (y - 2001 + no_lp) % 7;

    /*the day of 1st month*/

    n = d;

    if (y % 4 == 0)
        nod[2] = 29;

    for (j = 1; j <= 12; j++)
    {

        p("\nm  t  w  t  f  s  s\n");

        while (d-- != 0)
            p("   ");

        while (i <= nod[j])

        {

            if (i < 10)
            {
                p("%d  ", i++);
            } /*formattng for dates with 2 digits*/

            else
            {
                p("%d ", i++);
            }
            n++;

            if (n == 7)
            {
                n = 0;
                p("\n");
            }
        }

        d = n;
        i = 1; /*n will be the 1st day of next month*/
    }

    getch();
    return 0;
}