/// Whiteteam
/// \file main.cpp
/// \brief Defines the entry point for the console application.
/// \author Whiteteam authors

#include "stdafx.h"
#include "app\app_const.h"
#include "image_reader.h"
#include "graphics\skeletonization.h"
#include "graphics\vectorization.h"

using namespace APP_NAMESPACE;

int _tmain(int argc, _TCHAR* argv[])
{
    WImageRaster image("test vector.bmp");
    
    bool result = WSkeletonizer::Instance().Skeletonize(image, image);

    image.saveAsBMP("temp2.bmp");
    return 0;
}
