/// Whiteteam
/// \file image_reader.cpp
/// \brief This file contains image reader
/// \author Whiteteam authors

#include "stdafx.h"
#include "image_reader.h"

APP_BEGIN_NAMESPACE


WImageRaster::~WImageRaster()
{
	for (int i = 0; i<height; i++)
	{
		delete[] image[i];
	}
	delete[] image;
}

WImageRaster::WImageRaster()
{
	image = NULL;
}

WImageRaster::WImageRaster(int width, int height)
{
    this->width = width;
    this->height=height;
    image = new WColor*[height];
    for (int i = 0; i < height; i++)
        image[i] = new WColor[width];
}

WImageRaster::WImageRaster(char *filename)
{
	CImg<unsigned char> Cimage(filename);
	width = Cimage.width();
	height = Cimage.height();
	image= new WColor*[height];
	for (int i = 0; i < height; i++)
		image[i] = new WColor[width];
	unsigned char* ptr = Cimage.data(0, 0);
	for (int i = 0;i < height;i++)
	{
		for (int j = 0;j < width;j++)
		{
			image[i][j] = getDXFColor((int)*Cimage.data(j,i,0,0), (int)*Cimage.data(j, i, 0, 1), (int)*Cimage.data(j, i, 0, 2));
		}
		ptr += 3;
	}
}

WImageRaster::WImageRaster( WImageRaster* imageToCopy)
{
	image = new WColor*[imageToCopy->getHeight()];
	for (int i = 0; i < imageToCopy->getHeight(); i++)
		image[i] = new WColor[imageToCopy->getWidth()];
 for (int x = 0; x < imageToCopy->getWidth(); x++)
  {
    for (int y = 0; y < imageToCopy->getHeight(); y++)
    {
      this->image[y][x] = imageToCopy->at(x, y);
    }
  }
	 this->width = imageToCopy->getWidth();
	 this->height = imageToCopy->getHeight();

}

WColor ** WImageRaster::getImagePtr()
{
	return image;
}

int WImageRaster::getDXFColor(int red, int green, int blue) //TODO �������� ������ �� WColor
{
    double minRed = (double)red / 255 + 0.075, minGreen = (double)green / 255 + 0.075, minBlue = (double)blue / 255 + 0.075;
    int index;
    for (int i = 0;i < 256;i++)
    {
        if (minRed >= abs((double)red / 255 - dxfColors[i][0]) &&
            minGreen >= abs((double)green / 255 - dxfColors[i][1]) &&
            minBlue >= abs((double)blue / 255 - dxfColors[i][2]))
        {
            index = i;
            minRed = abs((double)red / 255 - dxfColors[i][0]);
            minGreen = abs((double)green / 255 - dxfColors[i][1]);
            minBlue = abs((double)blue / 255 - dxfColors[i][2]);
        }
    }
    return index;
}


WPointsContainer WImageRaster::NeihborsClockwise(WPoint point)
{
    WPointsContainer neighbors;
    int x_ = point.x;
    int y_ = point.y;
    WColor color(image[y_][x_]);
    if (image[--y_][x_] == color)
    {
        neighbors.push_back(WPoint(x_,y_));
    }
    if (image[y_][++x_] == color)
    {
        neighbors.push_back(WPoint(x_,y_));
    }
    if (image[++y_][x_] == color)
    {
        neighbors.push_back(WPoint(x_,y_));
    }
    if (image[++y_][x_] == color)
    {
        neighbors.push_back(WPoint(x_,y_));
    }
    if (image[y_][--x_] == color)
    {
        neighbors.push_back(WPoint(x_,y_));
    }
    if (image[y_][--x_] == color)
    {
        neighbors.push_back(WPoint(x_,y_));
    }
    if (image[--y_][x_] == color)
    {
        neighbors.push_back(WPoint(x_,y_));
    }
    if (image[--y_][x_] == color)
    {
        neighbors.push_back(WPoint(x_,y_));
    }
    return neighbors;
}

void WImageRaster::saveAsBMP(const char * filename)
{
    CImg<unsigned char> imageBMP(width, height, 1, 1, 0);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y <height; y++)
        {
            *imageBMP.data(x, y, 0, 0) = image[y][x];
        }
    }
    imageBMP.save(filename);
}


APP_END_NAMESPACE