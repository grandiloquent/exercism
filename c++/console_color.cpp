#include <windows.h>
#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char const *argv[])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (size_t i = 0; i < 256; i++)
    {
        SetConsoleTextAttribute(hConsole, i);
        cout << i << endl;
        /* code */
    }

    return 0;
}
// g++ console_color.cpp