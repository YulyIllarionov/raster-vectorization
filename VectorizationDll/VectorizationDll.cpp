

#include "stdafx.h"
#include <stdexcept>

#include "image_reader.h"
#include "graphics\skeletonization.h"
#include "graphics\vectorization.h"

#include "VectorizationDll.h"

APP_BEGIN_NAMESPACE

Vectorization::Vectorization(std::string input_filename)
//: m_input_filename(input_filename)
//m_src_image(WImageRaster(m_input_filename.c_str()))
{
    WImageRaster image(input_filename.c_str()); //Open input raster image
    WImageRaster image_skelet(image.getWidth(), image.getHeight());
    bool result = WSkeletonizer::Instance().Skeletonize(image, image_skelet); //Skeletonization of input image 
    m_vectorization = new WVectorization(&image_skelet, &image); //Vectorization of skeletonized image
    ((WVectorization*)m_vectorization)->onSkeleton();
    ((WVectorization*)m_vectorization)->calcLinesWidth();  //Ñalculation of the thickness of lines 
    ((WVectorization*)m_vectorization)->setScaleForAllLines(10);
    m_lines = ((WVectorization*)m_vectorization)->getLines();
}

Vectorization::~Vectorization()
{
    delete m_vectorization;
    m_vectorization = nullptr;
}

void Vectorization::SaveSkeletonizedImage(std::string output_filename)
{
    // save
}

void Vectorization::SaveVectorizedImage(std::string output_filename)
{
    ((WVectorization*)m_vectorization)->linesToFile(output_filename.c_str()); //Saving vector image in out.dxf*/
}

APP_END_NAMESPACE