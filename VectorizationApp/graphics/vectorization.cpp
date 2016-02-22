/// Whiteteam
/// \file vectorization.cpp
/// \brief This file contains vectorization
/// \author Whiteteam authors

#include "stdafx.h"
#include "vectorization.h"

APP_BEGIN_NAMESPACE

Vectorization::~Vectorization ()
{
}

Vectorization::Vectorization ():
imageRaster(NULL), imageRasterTemp(NULL) //TODO не уверен в NULL, инициализация lines
{
}

Vectorization::Vectorization (WImageRaster* image):
imageRaster(image), imageRasterTemp(image)
{

}

APP_END_NAMESPACE