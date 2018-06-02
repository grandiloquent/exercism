#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <wchar.h>
#include <cmath>
#include <limits>
#include <tchar.h>
#include <exception>
#include <string>
#include "utils.h"

using namespace Gdiplus;
using namespace std;

bool AreSame(double a, double b)
{
    return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
}
const wchar_t *GetWC(const char *c)
{
    const size_t cSize = strlen(c) + 1;
    wchar_t *wc = new wchar_t[cSize];
    mbstowcs(wc, c, cSize);

    return wc;
}
int GetEncoderClsid(const WCHAR *format, CLSID *pClsid)
{
    UINT num = 0;  // number of image encoders
    UINT size = 0; // size of the image encoder array in bytes

    Gdiplus::ImageCodecInfo *pImageCodecInfo = NULL;

    Gdiplus::GetImageEncodersSize(&num, &size);
    if (size == 0)
        return -1; // Failure

    pImageCodecInfo = (Gdiplus::ImageCodecInfo *)(malloc(size));
    if (pImageCodecInfo == NULL)
        return -1; // Failure

    GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT j = 0; j < num; ++j)
    {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j; // Success
        }
    }

    free(pImageCodecInfo);
    return -1; // Failure
}
float RoundUp(float var)
{
    // 37.66666 * 100 =3766.66
    // 3766.66 + .5 =37.6716    for rounding off value
    // then type cast to int so value is 3766
    // then divided by 100 so the value converted into 37.66
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}
int CropImage(const wchar_t *filename)
{
    Image *bitmap = new Image(filename);
    REAL rw = bitmap->GetHorizontalResolution();
    REAL rh = bitmap->GetHorizontalResolution();
    const int W24 = 6096;
    const int W30 = 7620;
    int w = 0, h = 0, t = 0, c = 0;
    int tw = 0;
    int th = 0;
    int ox = 0;
    int oy = 0;

    if (AreSame(rw, 254.0))
    {
        w = bitmap->GetWidth();
        h = bitmap->GetHeight();
    }
    else
    {
        w = round((bitmap->GetWidth() / rw * 2.539999918) / 2.539999918 * 254);
        h = round((bitmap->GetHeight() / rh * 2.539999918) / 2.539999918 * 254);
    }

    while (t < W24)
    {
        t += w;
        c++;

        if (t > W24 && (t - W24) / c < c * 100)
        {
            // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // SetConsoleTextAttribute(hConsole, 11);
            th = h;
            tw = w - (round((t - W24) / (double)c));
            ox = (t - W24) / c / 2;
            cout << t << " - " << ox << endl;
        }
    }
    if (tw == 0)
    {
        t = 0;
        c = 0;
        while (t < W24)
        {
            t += h;
            c++;

            if (t > W24 && (t - W24) / c < c * 100)
            {
                // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                // SetConsoleTextAttribute(hConsole, 11);
                SetConsoleInformation();
                tw = w;
                th = h - (round((t - W24) / (double)c));
                oy = (t - W24) / c / 2;
                cout << t << " - " << oy << endl;
            }
        }
    }
    if (tw == 0)
    {
        while (t < W30)
        {
            t += w;
            c++;

            if (t > W30 && (t - W30) / c < c * 100)
            {
                // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                // SetConsoleTextAttribute(hConsole, 11);
                th = h;
                tw = w - (round((t - W30) / (double)c));
                ox = (t - W30) / c / 2;
                cout << t << " - " << ox << endl;
            }
        }
    }
    if (tw == 0)
    {
        t = 0;
        c = 0;
        while (t < W30)
        {
            t += h;
            c++;

            if (t > W30 && (t - W30) / c < c * 100)
            {
                // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                // SetConsoleTextAttribute(hConsole, 11);
                tw = w;
                th = h - (round((t - W30) / (double)c));
                oy = (t - W30) / c / 2;
                cout << t << " - " << oy << endl;
            }
        }
    }

    if (tw == 0)
    {
        return -1;
    }

    Bitmap *im = new Bitmap(tw, th, bitmap->GetPixelFormat());
    im->SetResolution(254, 254);

    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms534453(v=vs.85).aspxt
    Graphics g(im);

    cout << w << "X" << h << endl;

    g.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    g.SetInterpolationMode(InterpolationModeHighQualityBicubic);
    g.SetSmoothingMode(SmoothingModeHighQuality);
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms536053(v=vs.85).aspx
    g.DrawImage(bitmap, 0, 0, ox, oy, tw, th, Gdiplus::Unit::UnitPixel);
    g.Flush();

    delete bitmap;

    CLSID encoderClsid;
    Status stat;
    EncoderParameters encoderParameters;
    ULONG quality;

    GetEncoderClsid(L"image/jpeg", &encoderClsid);

    encoderParameters.Count = 1;
    encoderParameters.Parameter[0].Guid = EncoderQuality;
    encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
    encoderParameters.Parameter[0].NumberOfValues = 1;

    quality = 95;
    encoderParameters.Parameter[0].Value = &quality;

    stat = im->Save(filename, &encoderClsid, &encoderParameters);

    if (stat == Ok)
    {
        wcout << L"成功：" << filename << endl;
    }
    else
    {
        wcout << L"保存失败重试:" << filename << endl;
        // delete im;
        CropImage(filename);
    }

    delete im;
    return 0;
}
int main()
{

    wchar_t **szArglist;
    int nArgs;
    int i;

    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    // Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    // ---
    for (int i = 0; i < nArgs; i++)
    {

        if (i == 0 || !IsJpgFile(szArglist[i]))
            continue;

        try
        {
            CropImage(szArglist[i]);
        }
        catch (exception &e)
        {
        }
    }

    // GetDPI(image);

    // Bitmap *bitmap = new Bitmap(500, 500, image->GetPixelFormat());
    // Graphics g(bitmap);
    // g.DrawImage(bitmap, 0, 0, 500, 500);

    // Close GDI+
    GdiplusShutdown(gdiplusToken);
    // ---

    cin.get();
    return 0;
}

// g++ i.cpp -lgdiplus && a
// g++ i.cpp utils.cpp  -lgdiplus