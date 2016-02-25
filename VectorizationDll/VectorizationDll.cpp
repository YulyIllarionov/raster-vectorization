

#include "stdafx.h"
#include <stdexcept>

#include "image_reader.h"
#include "graphics\skeletonization.h"
#include "graphics\vectorization.h"

#include "VectorizationDll.h"

APP_BEGIN_NAMESPACE

Vectorization::Vectorization(std::string input_filename, std::string output_filename)
  : m_input_filename(input_filename), m_output_filename(output_filename)
  //m_src_image(WImageRaster(m_input_filename.c_str()))
{
  m_src_image = new WImageRaster(m_input_filename.c_str());
}

Vectorization::~Vectorization()
{
  delete m_src_image;
  m_src_image = nullptr;
}

/*WVECTORIZEDLL*/ bool Vectorization::Vectorize(int scale/*, std::vector<POINT>& out_points*/)
{

  WImageRaster* src_image = reinterpret_cast<WImageRaster*>(m_src_image);

  WImageRaster image_skelet(src_image->getWidth(), src_image->getHeight());
  //Skeletonization of input image 
  bool result = WSkeletonizer::Instance().Skeletonize(*src_image, image_skelet); 

  //Vectorization of skeletonized image
  WVectorization vectorization(&image_skelet, src_image); 
  vectorization.onSkeleton();

  vectorization.setScaleForAllLines(scale); //Number of missed points. Accuracy is lost with increasing
  vectorization.calcLinesWidth();  //Ñalculation of the thickness of lines 

  
  

  return true;
}

void Vectorization::SaveSkeletonizedImage()
{
  // save
}

void Vectorization::SaveVectorizedImage()
{
  //vectorization.linesToFile("out.dxf"); //Saving vector image in out.dxf*/
}

APP_END_NAMESPACE