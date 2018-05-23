#include <Magick++.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace Magick;

int main( int argc, char **argv )
{
    InitializeMagick(*argv);

    Image oImage;
    oImage.read( "test.jpg" );
    oImage.zoom( Geometry("200x200") );
    oImage.read( "test_out.jpg" );
    return 0;
}
// g++ main.cpp -o m.exe -I "C:\Program Files\ImageMagick-7.0.7-Q16\include" -L "C:\Program Files\ImageMagick-7.0.7-Q16\lib"  