/// Whiteteam
/// \file vectorization.h
/// \brief This file contains vectorization
/// \author Whiteteam authors

#ifndef _VECTORIZATION_APP_WVECTORIZATION_H_
#define _VECTORIZATION_APP_WVECTORIZATION_H_
#pragma once

// for includes
#include "app\app_const.h"
#include "image_reader.h"
#include "WDxfWriter.h"


APP_BEGIN_NAMESPACE

class WVectorization
{
public:
	WVectorization ();
	WVectorization (WImageRaster* m_imageRaster);
  WVectorization(WImageRaster* skeletImageRaster, WImageRaster* srcImageRaster);
	virtual ~WVectorization(); 
	void onSkeleton();
  void linesToFile(const char *filename);
  void calcLinesWidth();
  // experimental
  void setScaleForAllLines(int scale);
  bool setScaleForLine(int scale, int number);
  //std::vector<std::pair<std::vector<std::pair<int, int>>, int>> getLines();
  std::vector<WLine> getLines() { return m_lines; };

private:
  int helpForCalcLinesWidth(double kperpend, double bperpend, int x3, int y3);
	WImageRaster* m_imageRaster;
	WImageRaster* m_imageRasterTemp;
  WImageRaster* m_srcImageRaster;
	std::vector<WLine> m_lines;
	
};


APP_END_NAMESPACE

#endif // _VECTORIZATION_APP_WVECTORIZATION_H_
