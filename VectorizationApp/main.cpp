/// Whiteteam
/// \file main.cpp
/// \brief Defines the entry point for the console application.
/// \author Whiteteam authors

#include "stdafx.h"
#include "app\app_const.h"
#include "image_reader.h"

APP_BEGIN_NAMESPACE

int _tmain(int argc, _TCHAR* argv[])
{
    WImageRaster image("test vector.bmp");
    image.saveAsBMP("temp2.bmp");

    return 0;
}

APP_END_NAMESPACE