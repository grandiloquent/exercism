#include "utils.h"

void SetConsoleInformation()
{
    // https://docs.microsoft.com/en-us/windows/console/getstdhandle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // https://docs.microsoft.com/en-us/windows/console/setconsoletextattribute
    //https://docs.microsoft.com/en-us/windows/console/console-screen-buffers#_win32_font_attributes
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
}

bool IsJpgFile(const wchar_t *filename)
{

    std::wstring f = filename;
    std::string::size_type idx = f.find_last_of(L".");
    std::wstring s = f.substr(idx + 1);
    return (s == L"jpg") || (s == L"JPG") || (s == L"jpeg") || (s == L"JPEG");
}