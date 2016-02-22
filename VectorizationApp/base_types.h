/// Whiteteam
/// \file base_types.h
/// \brief This file contains base types
/// \author Whiteteam authors

#ifndef _VECTORIZATION_APP_BASE_TYPES_H_
#define _VECTORIZATION_APP_BASE_TYPES_H_
#pragma once

#include "app\app_const.h"

#include <vector>

APP_BEGIN_NAMESPACE

class WPixel;

typedef std::vector<WPixel>                WPixelsContainer;
typedef std::vector<std::vector<WPixel> >  WMatrix;
typedef unsigned char                      WColor;

#define WCOLOR_WHITE 0

class WPoint
{
public:
	WPoint();
	WPoint(int x_, int y_);
	virtual ~WPoint(); 

	static WPoint Empty() { return WPoint(); };

	WPoint& operator=(const WPoint& other);
	bool operator==(const WPoint& other);
	bool operator!=(const WPoint& other);



	int x;
	int y;
};

class WPixel : public WPoint
{
public:

  WPixel();
  WPixel(WColor color, int x_ = -1, int y_ = -1);
  virtual ~WPixel();

  // return Empty WPixel
  static WPixel Empty() { return WPixel(); };
  // check if point is empty
  bool IsEmpty() { return m_isInitialized; };

private:

  bool m_isInitialized;
  WColor m_color;
};

class WLine
{
public:
  WLine();
  virtual ~WLine();

  // line width
  void setWidth(double width);
  double getWidth() {return m_width; };

  // points
  void AddPoint(const WPixel& point) { m_pixels.push_back(point); };
  bool AddPointAt(const WPixel& point, int idx);
  WPixel getPixel(int idx) { return m_pixels.size() > idx ? m_pixels[idx] : WPixel::Empty(); };
  bool RemovePoint(int idx);
  int Lenght(){ return m_pixels.size(); }; 
  WPixelsContainer getPixels() { return m_pixels; }
  bool Concat(WLine line); //TODO перейти к двум параметрам 

  int getScaler() { return m_scaler; };
  void setScaler(int scaler);

private:
  double            m_width;
  WPixelsContainer  m_pixels;
  int m_scaler;
};


APP_END_NAMESPACE

#endif // _VECTORIZATION_APP_BASE_TYPES_H_
