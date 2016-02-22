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
	WColor** getImagePtr(); //TODO убивает защиту 
	int getWidth();
	int getHeight();
	static int getDXFColor(int red,int green,int blue);
private:
	WColor **image;
	int width;
	int height;
	string filename;
};

