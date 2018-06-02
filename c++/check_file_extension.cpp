#include <iostream>
#include <string>

using namespace std;
int main()
{
    std::wstring f(L"1.jpg");
    std::string::size_type idx = f.find_last_of(L".");
    wstring s = f.substr(idx + 1);
    wcout << s << endl;

    return 0;
}
// g++ check_file_extension.cpp