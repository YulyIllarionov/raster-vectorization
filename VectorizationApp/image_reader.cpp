/// Whiteteam
/// \file image_reader.cpp
/// \brief This file contains image reader
/// \author Whiteteam authors

#include "stdafx.h"
#include "image_reader.h"

APP_BEGIN_NAMESPACE


WImageRaster::~WImageRaster()
{
	for (int i = 0; i<width; i++)
	{
		delete[] image[i];
	}
	delete[] image;
}

WImageRaster::WImageRaster()
{
	image = NULL;
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

int WImageRaster::getDXFColor(int red, int green, int blue) //TODO Возможна замена на WColor
{
    double minimum = 3.0;
    double color = ((double)red / 255) + ((double)green / 255) + ((double)blue / 255);
	int index=0;
	for (int i = 0;i < 256;i++)
	{
        double temp = abs(color- dxfColors[i][0]- dxfColors[i][1]- dxfColors[i][2]);
		if (minimum>=temp)
		{
			index = i;
            minimum = temp;
		}
	}
	return index;
}

<<<<<<< HEAD
WPoint WImageRaster::NeihborClockwise (WPoint point)
{
    int x_=point.x;
    int y_=point.y;
    WPoint neihbor;
    WColor color(image[y_][x_]);
    if (image[--y_][x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    if (image[y_][++x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    if (image[++y_][x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    if (image[++y_][x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    if (image[y_][--x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    if (image[y_][--x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    if (image[--y_][x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    if (image[--y_][x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    return neihbor;
}

WPoint WImageRaster::NeihborCounterClockwise (WPoint point)
{
    int x_=point.x;
    int y_=point.y;
    WPoint neihbor;
    WColor color(image[y_][x_]);
    if (image[--y_][x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    if (image[y_][--x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    if (image[++y_][x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    if (image[++y_][x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    if (image[y_][++x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    if (image[y_][++x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    if (image[--y_][x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    if (image[--y_][x_]==color)
    {
        neihbor.x=x_;
        neihbor.y=y_;
        return neihbor;
    }
    return neihbor;
=======
void WImageRaster::saveAsBMP(char * filename)
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

>>>>>>> zko
}


APP_END_NAMESPACE