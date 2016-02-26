/// Whiteteam
/// \file image_reader.h
/// \brief This file contains image reader
/// \author Whiteteam authors

#ifndef _VECTORIZATION_APP_IMAGE_READER_H_
#define _VECTORIZATION_APP_IMAGE_READER_H_
#pragma once


#include "base_types.h"
#include "app\app_const.h"

using namespace std;

APP_BEGIN_NAMESPACE

class WVECTORIZEDLL WImageRaster
{
public:
	WImageRaster();
  WImageRaster(int width, int height);
	WImageRaster(const char *filename);
	WImageRaster(WImageRaster* imageToCopy);
	~WImageRaster();
	
  WColor& at(WPoint point){ return image[point.y][point.x]; }; //TODO проверка выхода за границы
	WColor& at(int x, int y){ return image[y][x]; };
	WColor** getImagePtr(); //TODO убивает защиту 
	int getWidth() { return width; };
	int getHeight() { return height; };
	static int getDXFColor(int red,int green,int blue);

  WPointsContainer NeihborsClockwise(WPoint point);

  void saveAsBMP(const char *filename);

private:
	WColor **image;
	int width;
	int height;
	string filename;
};


APP_END_NAMESPACE

#endif // _VECTORIZATION_APP_IMAGE_READER_H_
