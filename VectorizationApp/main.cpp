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
    image.saveAsBMP("temp2.bmp");

    return 0;
}