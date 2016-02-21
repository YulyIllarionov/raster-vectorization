
#include "stdafx.h"
#include "image_reader.h"



ImageReader::ImageReader(char *filename)
{
	this->filename = filename;
	image = NULL;
}


ImageReader::~ImageReader()
{
}

void ImageReader::readImage()
{
	CImg<unsigned char> Cimage(filename.c_str());
	width = Cimage.width();
	height = Cimage.height();
	image= new char*[width];
	for (int i = 0; i < width; i++)
		image[i] = new char[height];
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

char ** ImageReader::getImagePtr()
{
	return image;
}

int ImageReader::getWidth()
{
	return width;
}

int ImageReader::getHeight()
{
	return height;
}

void ImageReader::deleteImage()
{
	for (int i = 0; i<width; i++)
	{
		delete[] image[i];
	}
	delete[] image;
}

int ImageReader::getDXFColor(int red, int green, int blue)
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
