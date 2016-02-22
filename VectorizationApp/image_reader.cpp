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
	image= new WColor*[width];
	for (int i = 0; i < width; i++)
		image[i] = new WColor[height];
	unsigned char* ptr = Cimage.data(0, 0);
	for (int i = 0;i < width;i++)
	{
		for (int j = 0;j < height;j++)
		{
			image[i][j] = getDXFColor((int)ptr[0], (int)ptr[1], (int)ptr[2]);
		}
		ptr += 3;
	}
}

WImageRaster::WImageRaster(const WImageRaster* imageToCopy)
{
	image= new WColor*[width];
	for (int i = 0; i < width; i++)
		image[i] = new WColor[height];
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			this->image[x][y] = imageToCopy->at(x,y);
		}
	}
}

WColor ** WImageRaster::getImagePtr()
{
	return image;
}

int WImageRaster::getDXFColor(int red, int green, int blue) //TODO Возможна замена на WColor
{
	double minRed=1.0, minGreen=1.0, minBlue=1.0;
	int index;
	for (int i = 0;i < 256;i++)
	{
		if (minRed > abs((double)red / 255 - dxfColors[i][0])&&
			minGreen>abs((double)green / 255 - dxfColors[i][1]) &&
			minBlue > abs((double)blue / 255 - dxfColors[i][2]))
		{
			index = i;
			minRed=abs((double)red / 255 - dxfColors[i][0]);
			minGreen = abs((double)green / 255 - dxfColors[i][1]);
			minBlue = abs((double)blue / 255 - dxfColors[i][2]);
		}
	}
	return index;
}


APP_END_NAMESPACE