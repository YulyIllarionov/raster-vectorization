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

void Vectorization::onSkeleton()
{
	for (int x=0; x<imageRasterTemp.getWidth(); x++)
	{
		for (int y=0; y<imageRasterTemp.getHeight(); y++)
		{
			if(imageRasterTemp.at(x,y)!=WCOLOR_WHITE)
			{

			}
		}
	}
}


APP_END_NAMESPACE