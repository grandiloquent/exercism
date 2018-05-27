#include "Shlobj.h"
#include <stdio.h>
#include <sys/stat.h>
#include <locale.h>
#include "tchar.h"
#include "wchar.h"

typedef int bool;
#define true 1
#define false 0

/*
 任何一年的4、6、9、10月有30天，除2月以外其他月份有31天。如果年能够整除4且不能整除100，或能整除400，当年为闰年，2月有29天，否则2月有28天。

 比喻 2016÷4=54 2016/100=20.16 2016÷400=5.04 所以 2016为闰年，2月有29天
*/
int GetDaysInMonth(int year, int month)
{
    int numberOfDays;

    if (month == 4 || month == 6 || month == 9 || month == 11)
        numberOfDays = 30;
    else if (month == 2)
    {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

        if (isLeapYear)
            numberOfDays = 29;
        else
            numberOfDays = 28;
    }
    else
        numberOfDays = 31;

    return numberOfDays;
}
void combine(char *destination, const char *path1, const char *path2)
{
    if (path1 == NULL && path2 == NULL)
    {
        strcpy(destination, "");
        ;
    }
    else if (path2 == NULL || strlen(path2) == 0)
    {
        strcpy(destination, path1);
    }
    else if (path1 == NULL || strlen(path1) == 0)
    {
        strcpy(destination, path2);
    }
    else
    {
        char directory_separator[] = "/";
#ifdef WIN32
        directory_separator[0] = '\\';
#endif
        const char *last_char = path1;
        while (*last_char != '\0')
            last_char++;
        int append_directory_separator = 0;
        if (strcmp(last_char, directory_separator) != 0)
        {
            append_directory_separator = 1;
        }
        strcpy(destination, path1);
        if (append_directory_separator)
            strcat(destination, directory_separator);
        strcat(destination, path2);
    }
}
// char *itoa(int i, char b[])
// {
//     char const digit[] = "0123456789";
//     char *p = b;
//     if (i < 0)
//     {
//         *p++ = '-';
//         i *= -1;
//     }
//     int shifter = i;
//     do
//     { //Move to where representation ends
//         ++p;
//         shifter = shifter / 10;
//     } while (shifter);
//     *p = '\0';
//     do
//     { //Move back, inserting digits as u go
//         *--p = digit[i % 10];
//         i = i / 10;
//     } while (i);
//     return b;
// }

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "");
    char desktop[MAX_PATH];

    SHGetSpecialFolderPath(NULL, desktop, CSIDL_DESKTOP, 1);

    int year = 2018;

    wchar_t wdesktop[MAX_PATH];
    swprintf(wdesktop, MAX_PATH, L"%hs", desktop);

    wchar_t dir[MAX_PATH];
    // wchar_t d[MAX_PATH];
    // _itow(year, d, 10);

    wsprintfW(dir, L"%s\\%d", wdesktop, year);

    wprintf(L"%s\n", dir);
    _wmkdir(dir);
    // mkdir(dir);
    for (size_t i = 1; i <= 12; i++)
    {
        int days = GetDaysInMonth(year, i);

        wchar_t cmdir[MAX_PATH];
        wchar_t cmd[MAX_PATH];

        wsprintfW(cmd, L"%02d%s", i, L"月");
        wsprintfW(cmdir, L"%s\\%s", dir, cmd);
        _wmkdir(cmdir);
        for (size_t j = 1; j <= days; j++)
        {
            wchar_t td[MAX_PATH];
            // wchar_t p[MAX_PATH];
            // _itow(j, p, 10);
            wsprintfW(td,  L"%s\\%d%02d%02d", cmdir, year,i,j);
            _wmkdir(td);
        }
    }

    //printf(desktop);
    return 0;
}
// gcc calendar.c