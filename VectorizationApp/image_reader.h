#pragma once
#include "CImg.h"
#include "dl_codes.h"
#include "string"

using namespace cimg_library;
using namespace std;
class ImageReader
{
public:
	ImageReader(char *filename);
	~ImageReader();
	void readImage();
	char **getImagePtr();
	int getWidth();
	int getHeight();
	void deleteImage();
	static int getDXFColor(int red,int green,int blue);
private:
	char **image;
	int width;
	int height;
	string filename;
};

