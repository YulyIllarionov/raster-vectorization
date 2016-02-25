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
  m_imageRaster(NULL), m_imageRasterTemp(NULL), m_srcImageRaster(NULL)
{
}

Vectorization::Vectorization(WImageRaster* image) :
  m_imageRaster(image), m_imageRasterTemp(image), m_srcImageRaster(NULL)
{

}

Vectorization::Vectorization(WImageRaster * skeletImageRaster, WImageRaster * srcImageRaster) :
    m_imageRaster(skeletImageRaster), m_imageRasterTemp(skeletImageRaster), m_srcImageRaster(srcImageRaster)
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

                    //currentLine.setColor(color);
                    //currentLine.setScaler(1);
                    //this->m_lines.push_back(currentLine);
                    if (i==0)
                    {
                        fullLine = currentLine;
                        currentLine.clearPoints();
                    }
                    else
                    {
                        fullLine.concat(currentLine);
                    }
                }
                fullLine.setColor(color);
                fullLine.setScaler(5);
                this->m_lines.push_back(fullLine);
            }
		}
	}
}

void Vectorization::linesToFile(const char *filename)
{
    WDxfWriter writer(filename);
    writer.begin();
    for (int i = 0;i < m_lines.size();i++)
    {
        writer.writePolyLine(m_lines.at(i), m_imageRaster->getHeight());
    }
    writer.end();
}

void Vectorization::calcLinesWidth()
{
    if (m_srcImageRaster == NULL) return;

    for (int j = 0;j < m_lines.size();j++)
    {
        int x1 = m_lines.at(j).getPoint(0).x;
        int y1 = m_lines.at(j).getPoint(0).y;
        int x2 = 0, y2 = 0;

        int n = 0;
        int temp_width = 0;
        for (int i = 0;i <  m_lines.at(j).Lenght();i++)
        {
            if ((i + 1) % m_lines.at(j).getScaler() == 0)
            {
                x2= m_lines.at(j).getPoint(i).x;
                y2= m_lines.at(j).getPoint(i).y;
                double k;
                if ((x2 - x1) == 0) k = INT_MAX;
                else k = (double)(y2 - y1) / (double)(x2 - x1);

                int x3 = (x2 + x1) / 2;
                int y3 = (y2 + y1) / 2;


                double kperpend;
                if (k == 0) kperpend = INT_MAX;
                else    kperpend = -1.0 / k;
                double bperpend = y3 - kperpend*x3;
                temp_width += helpForCalcLinesWidth(kperpend, bperpend,x3,y3);
                n++;
                x1 = x2;
                y1 = y2;
            }
        }
        if(n==0) m_lines.at(j).setWidth(1);
        else m_lines.at(j).setWidth(temp_width / n);
    }


}

void Vectorization::setScaleForAllLines(int scale)
{
    for (int i = 0;i < m_lines.size();i++)
    {
        m_lines.at(i).setScaler(scale);
    }
}

int Vectorization::helpForCalcLinesWidth(double kperpend, double bperpend, int x3, int y3)
{
    int n = 0;
    int widthline = 1;
    int image_height = m_imageRaster->getHeight();
    int image_width = m_imageRaster->getWidth();
    WColor **image = m_srcImageRaster->getImagePtr();
    int temp_y;
    int temp_x;
    if (abs(kperpend) > 1.0)
    {
        temp_y = y3;
        while (true)
        {
            temp_y--;
            if (temp_y != 0)
            {
                temp_x = (temp_y-bperpend)/kperpend;

                if (temp_x>0&&temp_x<image_width&&image[temp_y][temp_x] != 255) widthline++;
                else break;
            }
            else break;
        }
        temp_y = y3;
        while (true)
        {
            temp_y++;
            if (temp_y < image_height)
            { 
                temp_x = (temp_y - bperpend) / kperpend;
                if (temp_x>0 && temp_x<image_width&&image[temp_y][temp_x] != 255) widthline++;
                else break;
            }
            else break;
        }
    }
    else
    {
        temp_x = x3;
        while (true)
        {
            temp_x--;
            if (temp_x != 0)
            {
                temp_y = kperpend*temp_x + bperpend;
                
                if (temp_y>0 && temp_y<image_height&&image[temp_y][temp_x] != 255) widthline++;
                else break;
            }
            else break;
        }

        temp_x = x3;
        while (true)
        {
            temp_x++;
            if (temp_x< image_width)
            {
                temp_y = kperpend*temp_x + bperpend;
                if (temp_y>0 && temp_y<image_height&&image[temp_y][temp_x] != 255) widthline++;
                else break;
            }
            else break;
        }
    }

    return widthline;

}

APP_END_NAMESPACE