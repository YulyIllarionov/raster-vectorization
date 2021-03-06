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

int _tmain(int argc, char* argv[])
{
  std::cout << " [input file is test_vector.bmp]" << std::endl;
  std::cout << " [output file is out.dxf]" << std::endl;
  std::cout << " please stand by ";

  WImageRaster image("test vector.bmp"); //Open input raster image
  WImageRaster image_skelet(image.getWidth(),image.getHeight());
  bool result = WSkeletonizer::Instance().Skeletonize(image, image_skelet); //Skeletonization of input image 

  //image.saveAsBMP("out.bmp"); //Saving result of skeletonization

  WVectorization vectorization(&image_skelet, &image); //Vectorization of skeletonized image
  vectorization.onSkeleton();
  
  vectorization.setScaleForAllLines(10); //Number of missed points. Accuracy is lost with increasing
  vectorization.calcLinesWidth();  //Ņalculation of the thickness of lines 

  vectorization.linesToFile("out.dxf"); //Saving vector image in out.dxf

  return 0;
}
