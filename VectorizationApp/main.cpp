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
    //WImageRaster image("test vector.bmp");
    
    //bool result = WSkeletonizer::Instance().Skeletonize(image, image);

    //image.saveAsBMP("temp2.bmp");
   /* Vectorization vc;
    WLine line1;
    line1.AddPoint(WPoint(0, 0));
    line1.AddPoint(WPoint(40, 40));
    line1.AddPoint(WPoint(20, 40));
    line1.setColor(DL_Codes::red);
    line1.setWidth(3);
    line1.setScaler(1);

    WLine line2;
    line2.AddPoint(WPoint(60, 60));
    line2.AddPoint(WPoint(70,0));
    line2.setColor(DL_Codes::black);
    line2.setWidth(10);
    line2.setScaler(1);
    vc.m_lines.push_back(line1);
    vc.m_lines.push_back(line2);
    vc.linesToFile("temp.dxf");*/
    return 0;
}
