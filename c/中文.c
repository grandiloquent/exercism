#include "Shlobj.h"
#include <stdio.h>
#include <sys/stat.h>
#include <locale.h>
#include "tchar.h"
#include <wchar.h>

typedef int bool;
#define true 1
#define false 0

int main(int argc, char const *argv[])
{

    setlocale(LC_ALL, "chs");

    wchar_t *p = L"月";
    wprintf(L"%s\n", p);
    //_wmkdir(p);

    wchar_t buf[MAX_PATH];
    wsprintfW(buf, L"%d%s", 5, p);

    wprintf(L"%s", buf);
    return 0;
}
// gcc c.c