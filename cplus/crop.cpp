#include <cv.h>
#include <highgui.h>

int main(int argc, char* argv[])
{
    cv::Mat img = cv::imread(argv[1]);
    if (img.empty())
    {
        std::cout << "!!! imread() failed to open target image" << std::endl;
        return -1;        
    }

    /* Set Region of Interest */

    int offset_x = 129;
    int offset_y = 129;

    cv::Rect roi;
    roi.x = offset_x;
    roi.y = offset_y;
    roi.width = img.size().width - (offset_x*2);
    roi.height = img.size().height - (offset_y*2);

    /* Crop the original image to the defined ROI */

    cv::Mat crop = img(roi);
    cv::imshow("crop", crop);
    cv::waitKey(0);

    cv::imwrite("noises_cropped.png", crop);

    return 0;
}
// #include <windows.h>
// #include <tchar.h>
// #include <stdio.h>
// #include <opencv.h>

// int _tmain(int argc, TCHAR *argv[])
// {
//    WIN32_FIND_DATA FindFileData;
//    HANDLE hFind;

//    if( argc != 2 )
//    {
//       _tprintf(TEXT("Usage: %s [target_file]\n"), argv[0]);
//       return 0;
//    }

//    _tprintf (TEXT("Target file is %s\n"), argv[1]);
//    hFind = FindFirstFile(argv[1], &FindFileData);
//    if (hFind == INVALID_HANDLE_VALUE) 
//    {
//       printf ("FindFirstFile failed (%d)\n", GetLastError());
//       return 0;
//    } 
//    else 
//    {
//       _tprintf (TEXT("The first file found is %s\n"), 
//                 FindFileData.cFileName);
//       FindClose(hFind);
//    }
// }

// g++ -std=c++11 crop.cpp -o crop.exe & crop.exe
// g++ crop.cpp -o crop.exe & crop.exe
