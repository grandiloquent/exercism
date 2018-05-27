
#include <stddef.h>
#include <stdio.h>
#include <windows.h>
#include "tlhelp32.h"
int should_kill(char **excludes, const char *szExeFile)
{

    // int len = sizeof(excludes) / sizeof(excludes[0]);

    // size_t count = 0;
    // while (excludes[count] != NULL)
    //     count++;

    for (size_t i = 0; i < 14; i++)
    {
        if (strnicmp(excludes[i], szExeFile, strlen(excludes[i])) == 0)
        {

            return 0;
        }
    }
    return -1;

    // while (excludes[count] != NULL)
    // {
    //
    //     printf("%s\n",excludes[count]);
    //     count++;
    // }
}
void kill_process(DWORD dwProcessId, UINT uExitCode)
{
    DWORD dwDesiredAccess = PROCESS_TERMINATE;
    BOOL bInheritHandle = FALSE;
    HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
    if (hProcess == NULL)
        return;

    BOOL result = TerminateProcess(hProcess, uExitCode);

    CloseHandle(hProcess);
}
void kill_processes(char **excludes)
{
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
    }
    else
    {
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (!Process32First(hProcessSnap, &pe32))
        {

            CloseHandle(hProcessSnap);
        }
        do
        {

            if (should_kill(excludes, pe32.szExeFile))
            {
                printf("Should Kill %s\n", pe32.szExeFile);
               kill_process(pe32.th32ProcessID, 1);
            }
        } while (Process32Next(hProcessSnap, &pe32));

        CloseHandle(hProcessSnap);
    }
}

int main(int argc, char const *argv[])
{
    char *excludes[] = {"[System Process]",
                        "System",
                        "services",
                        "smss",
                        "csrss",
                        "lsass",
                        "lsm",
                        "svchost",
                        "spoolsv",
                        "winlogon",
                        "wininit",
                        "explorer",
                        "conhost",
                        "Xerp"};
    printf("%d\n", sizeof(excludes) / sizeof(excludes[0]));
    kill_processes(excludes);
    return 0;
}

// gcc kill_process.c & a