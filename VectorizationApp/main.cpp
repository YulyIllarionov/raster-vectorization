/// Whiteteam
/// \file main.cpp
/// \brief Defines the entry point for the console application.
/// \author Whiteteam authors

#include "stdafx.h"
#include "app\app_const.h"
#include "image_reader.h"
using namespace white_app;

int _tmain(int argc, _TCHAR* argv[])
{
    WImageRaster image("C:\\temp.bmp");
    CImg<unsigned char> image2(image.getWidth(), image.getHeight(), 1, 3,0);
    unsigned char *ptr2 = image2.data();

    WColor **ptr = image.getImagePtr();

    for (int x = 0; x < image.getWidth(); x++)
    {
        for (int y = 0; y < image.getHeight(); y++)
        {
            *image2.data(x,y,0,0) = ptr[y][x];
            *image2.data(x, y, 0, 1) = ptr[y][x];
            *image2.data(x, y, 0, 2) = ptr[y][x];
            //ptr2[3 * (x + y) + 1] = ptr[y][x];
            //ptr2[3 * (x + y) + 2] = ptr[y][x];
        }
    }
    image2.save("temp2.bmp");

    return 0;
}