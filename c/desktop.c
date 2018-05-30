#include <sys/types.h>
#include <sys/stat.h>
#include <wchar.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <locale.h>

#include <windows.h>
#include <wchar.h>

const wchar_t *get_extension(wchar_t *filename)
{
    const wchar_t *dot = wcsrchr(filename, '.');
    if (!dot || dot == filename)
        return L"";
    return dot;
}
wchar_t *toupper_str(const wchar_t *src)
{
    int i = 1;
    wchar_t *dst = malloc(wcslen(src) - 1);
    while (src[i])
    {
        dst[i - 1] = towupper(src[i]);
        i++;
    }
    dst[wcslen(src) - 1] = '\0';
    return dst;
}
int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "");
    wchar_t c[MAX_PATH];
     _wgetcwd(c, MAX_PATH);
    wprintf(L"%s\n", c);

    _WDIR *dir;
    struct _wdirent *ent;
    struct stat statbuf;
    wchar_t *path = c; // L"C:/Users/Administrator/Desktop";
    if ((dir = _wopendir(path)) != NULL)
    {
        while ((ent = _wreaddir(dir)) != NULL)
        {
            if (wcscmp(L".", ent->d_name) != 0 || wcscmp(L"..", ent->d_name) != 0)
            {
                wchar_t f[MAX_PATH];
                wsprintfW(f, L"%s/%s", path, ent->d_name);
                if (wstat(f, &statbuf) == 0 && S_ISREG(statbuf.st_mode))
                {
                    const wchar_t *e = get_extension(ent->d_name);
                    wprintf(L"%s %d\n", e, wcslen(e));
                    wchar_t d[MAX_PATH];
                    wsprintfW(d, L"%s/%s", path, toupper_str(e));
                    wprintf(L"%s %d\n", d, wcslen(d));
                    _wmkdir(d);

                    wchar_t df[MAX_PATH];
                    wsprintfW(df, L"%s/%s", d, ent->d_name);
                    _wrename(f, df);
                    //  wchar_t ext[wcslen(e)];

                    // for (size_t i = 0; i < wcslen(e); i++)
                    // {
                    //      wprintf(L"%s\n", e++);
                    // }
                }
            }
        }

        _wclosedir(dir);
    }
    perror("");
    return EXIT_FAILURE;
}
// gcc desktop.c -D_FILE_OFFSET_BITS=64 & a
