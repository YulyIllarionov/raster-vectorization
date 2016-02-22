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

Vectorization::Vectorization() :
  m_imageRaster(NULL), m_imageRasterTemp(NULL) //TODO не уверен в NULL, инициализация m_lines
{
}

Vectorization::Vectorization(WImageRaster* image) :
  m_imageRaster(image), m_imageRasterTemp(image)
{

}

void Vectorization::onSkeleton()
{
	for (int x = 0; x < m_imageRasterTemp->getWidth(); x++)
	{
		for (int y = 0; y < m_imageRasterTemp->getHeight(); y++)
		{ 
			if(m_imageRasterTemp->at(x,y) != WCOLOR_WHITE)
			{
        WLine lineClockwise;
        WPoint current(x,y);
        WPoint previous;
        while(!current.IsEmpty())
        {
          lineClockwise.AddPoint(current);
          previous = current;
          if(m_imageRasterTemp->NeihborClockwise(current) == 1)
            m_imageRasterTemp->at(previous)=WCOLOR_WHITE;
        }
        WLine lineCounterClockwise;
        current = WPoint(x,y);
        while(!current.IsEmpty())
        {
          lineCounterClockwise.AddPoint(current);
          previous = current;
          if(m_imageRasterTemp->NeihborCounterClockwise(current) == 1)
              m_imageRasterTemp->at(previous) = WCOLOR_WHITE;
        }
        lineClockwise.Concat(lineCounterClockwise);
        m_lines.push_back(lineClockwise);
			}
		}
	}
}


APP_END_NAMESPACE