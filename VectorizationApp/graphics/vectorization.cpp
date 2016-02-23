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
    for (int y = 0; y < m_imageRasterTemp->getHeight(); y++)
	{
        for (int x = 0; x < m_imageRasterTemp->getWidth(); x++)
		{ 
			if(m_imageRasterTemp->at(x,y) != WCOLOR_WHITE)
			{
                WPoint firstPoint(x,y);
                WPointsContainer firstNeighbors = m_imageRasterTemp->NeihborsClockwise(firstPoint);
                if (firstNeighbors.size()>2)
                {
                    continue;
                }
                WColor color = m_imageRasterTemp->at(firstPoint);
                WLine currentLine;
                WLine fullLine;
                currentLine.AddPoint(firstPoint);
                m_imageRasterTemp->at(firstPoint) = WCOLOR_WHITE;
                if (firstNeighbors.size()==0)
                {
                    m_lines.push_back(currentLine);
                    continue;
                }
                for (int i=0; i<2; i++)
                {
                    WPoint currentPoint;
                    if (i==0)
                    {
                        currentPoint = firstNeighbors.at(0);
                    }
                    else
                    {
                        if (firstNeighbors.size()<2)
                        {
                            break;
                        }
                        currentPoint = firstNeighbors.at(1);
                    }
                    WPointsContainer neighbors;
                    WPointsContainer previousNeighbors;
                    do
                    {
                        currentLine.AddPoint(currentPoint);
                        neighbors = m_imageRasterTemp->NeihborsClockwise(currentPoint);
                        previousNeighbors;
                        if (neighbors.size()==0)
                        {
                            m_imageRasterTemp->at(currentPoint) = WCOLOR_WHITE;
                            break;
                        }
                        if (neighbors.size()==1)
                        {
                            m_imageRasterTemp->at(currentPoint) = WCOLOR_WHITE;
                            currentPoint = neighbors.at(0); 
                        }
                        if (neighbors.size()==2)
                        {
                            m_imageRasterTemp->at(currentPoint) = WCOLOR_WHITE;
                            currentPoint = neighbors.at(0); 
                        }
                        if (neighbors.size()==3)
                        {
                            if(((neighbors.at(0).x==neighbors.at(1).x)&&(neighbors.at(1).x==neighbors.at(2).x))||
                                ((neighbors.at(0).y==neighbors.at(1).y)&&(neighbors.at(1).y==neighbors.at(2).y)))
                            {
                                currentLine.AddPoint(currentPoint);
                                m_imageRasterTemp->at(currentPoint) = WCOLOR_WHITE;
                                break;
                            }
                            else
                            {
                                m_imageRasterTemp->at(currentPoint) = WCOLOR_WHITE;
                                WPoint previousPoint(currentPoint);
                                currentPoint = neighbors.at(1);
                                neighbors = m_imageRasterTemp->NeihborsClockwise(currentPoint);
                                m_imageRasterTemp->at(currentPoint) = WCOLOR_WHITE;
                                m_imageRasterTemp->at(previousPoint) = color;
                                if (neighbors.size()==0)
                                {
                                    break;
                                }
                                else
                                {
                                    currentLine.AddPoint(previousPoint);
                                    currentLine.AddPoint(currentPoint);
                                    currentPoint = neighbors.at(0);
                                }
                            }
                        }
                    }while(neighbors.size()>0);
                    if (i==0)
                    {
                        fullLine = currentLine;
                        currentLine.clearPoints();
                    }
                    else
                    {
                        currentLine.concat(fullLine);
                    }
                }
                this->m_lines.push_back(fullLine);
            }
		}
	}
}

void Vectorization::linesToFile(char *filename)
{
    WDxfWriter writer(filename);
    writer.begin();
    for (int i = 0;i < m_lines.size();i++)
    {
        writer.writePolyLine(m_lines.at(i));
    }
    writer.end();
}


APP_END_NAMESPACE