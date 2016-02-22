/// Whiteteam
/// \file vectorization.h
/// \brief This file contains vectorization
/// \author Whiteteam authors

#ifndef _VECTORIZATION_APP_VECTORIZATION_H_
#define _VECTORIZATION_APP_VECTORIZATION_H_
#pragma once

// for includes
#include "..\app\app_const.h"
#include "..\image_reader.h"

APP_BEGIN_NAMESPACE

class Vectorization
{
public:
	Vectorization ();
	Vectorization (WImageRaster* imageRaster);
	virtual ~Vectorization(); 
	void onSkeleton();

private:
	WImageRaster* imageRaster;
	WImageRaster* imageRasterTemp;
	std::vector<WLine> lines;
	
};


APP_END_NAMESPACE

#endif // _VECTORIZATION_APP_VECTORIZATION_H_
