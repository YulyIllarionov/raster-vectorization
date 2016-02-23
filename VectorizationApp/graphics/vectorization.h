/// Whiteteam
/// \file vectorization.h
/// \brief This file contains vectorization
/// \author Whiteteam authors

#ifndef _VECTORIZATION_APP_VECTORIZATION_H_
#define _VECTORIZATION_APP_VECTORIZATION_H_
#pragma once

// for includes
#include "app\app_const.h"
#include "image_reader.h"
#include "WDxfWriter.h"


APP_BEGIN_NAMESPACE

class Vectorization
{
public:
	Vectorization ();
	Vectorization (WImageRaster* m_imageRaster);
	virtual ~Vectorization(); 
	void onSkeleton();
    void linesToFile(const char *filename);
    void calcLinesWidth();
    // experimental
    void setScaleForAllLines(int scale);
private:
    int helpForCalcLinesWidth(double kperpend, double bperpend, int x3, int y3);
	WImageRaster* m_imageRaster;
	WImageRaster* m_imageRasterTemp;
	std::vector<WLine> m_lines;
	
};


APP_END_NAMESPACE

#endif // _VECTORIZATION_APP_VECTORIZATION_H_
