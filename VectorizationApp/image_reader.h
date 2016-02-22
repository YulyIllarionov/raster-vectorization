#pragma once
#include "CImg.h"
#include "dl_codes.h"
#include "base_types.h"

using namespace cimg_library;
using namespace std;
using namespace white_app;


class WImageRaster
{
public:
	WImageRaster();
	WImageRaster(char *filename);
	WImageRaster(const WImageRaster* imageToCopy);
	~WImageRaster();
	WColor& at(WPoint point){ return image[point.y][point.x]; }; //TODO проверка выхода за границы
	WColor& at(int x, int y){ return image[y][x]; };
	WColor** getImagePtr(); //TODO убивает защиту 
	int getWidth() { return width; };
	int getHeight() { return height; };
	static int getDXFColor(int red,int green,int blue);
private:
	WColor **image;
	int width;
	int height;
	string filename;
};

