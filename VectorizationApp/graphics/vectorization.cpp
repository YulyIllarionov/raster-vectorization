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

void Vectorization::calcLinesWidth()
{
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
                else k = (double)(y2 - y1) / (x2 - x1);

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
        // здесь бы добавить еще пару строк, но это посмотрим (если не кратно scaler, то последняя точка не будет считаться)
        m_lines.at(j).setScaler(temp_width / n);
    }


}

int Vectorization::helpForCalcLinesWidth(double kperpend, double bperpend, int x3, int y3)
{
    int n = 0;
    int width = 1;
    if ((int)kperpend == INT_MAX)
    {
        int temp_y = y3;
        while (true)
        {
            if (temp_y != 0)
            {
                temp_y--;
                if (m_imageRaster->getImagePtr()[temp_y][x3] != 255) width++;
                else break;
            }
            else break;
            
        }
        temp_y = y3;
        while (true)
        {
            if (temp_y != m_imageRaster->getHeight())
            {
                temp_y++;
                if (m_imageRaster->getImagePtr()[temp_y][x3] != 255) width++;
                else break;
            }
            else break;
        }
    }
    else
    {
        int temp_y = y3;
        int temp_x = x3;
        while (true)
        {
            if (temp_x != 0)
            {
                temp_x--;
                temp_y = kperpend*temp_x + bperpend;
                if (m_imageRaster->getImagePtr()[temp_y][temp_x] != 255) width++;
                else break;
            }
            else break;
        }
        temp_y = y3;
        temp_x = x3;
        while (true)
        {
            if (temp_y != m_imageRaster->getWidth())
            {
                temp_x++;
                temp_y = kperpend*temp_x + bperpend;
                if (m_imageRaster->getImagePtr()[temp_y][x3] != 255) width++;
                else break;
            }
            else break;
        }
    }

    return width;

}

APP_END_NAMESPACE