#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <wchar.h>
#include <cmath>
#include <limits>

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
int CropImage(Image *bitmap, int width, int height, PixelFormat pixelFormat)
{

    REAL rw = bitmap->GetHorizontalResolution();
    REAL rh = bitmap->GetHorizontalResolution();

    int w, h;
    if (AreSame(rw, 254.0))
    {
    }
    else
    {
        w=round((bitmap->GetWidth() / rw * 2.539999918)/2.539999918*254);
        cout<<w<<endl;
    
    }
    return 0;
}
int main(int argc, const char *argv[])
{

    for (int i = 0; i < argc; i++)
    {
        cout << argv[i] << endl;
    }

    // Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    cout << "1" << endl;

    Image *image = new Image(L"Crayons.jpg");
   
   CropImage(image,100,100,image->GetPixelFormat());
    // GetDPI(image);

    // Bitmap *bitmap = new Bitmap(500, 500, image->GetPixelFormat());
    // Graphics g(bitmap);
    // g.DrawImage(bitmap, 0, 0, 500, 500);
    delete image;

    // Close GDI+
    GdiplusShutdown(gdiplusToken);

    return 0;
}

// g++ i.cpp -lgdiplus