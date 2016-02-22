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
#include "..\WDxfWriter.h"


APP_BEGIN_NAMESPACE

class Vectorization
{
public:
	Vectorization ();
	Vectorization (WImageRaster* m_imageRaster);
	virtual ~Vectorization(); 
	void onSkeleton();
    void linesToFile(char *filename);
    std::vector<WLine> m_lines;
private:
	WImageRaster* m_imageRaster;
	WImageRaster* m_imageRasterTemp;
	//std::vector<WLine> m_lines;
	
};


APP_END_NAMESPACE

#endif // _VECTORIZATION_APP_VECTORIZATION_H_
