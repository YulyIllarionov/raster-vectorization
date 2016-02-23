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
class WPoint;

typedef std::vector<WPoint>                WPointsContainer;
typedef std::vector<std::vector<WPixel> >  WMatrix;
typedef unsigned char                      WColor;

#define WCOLOR_WHITE 255

class WPoint
{
public:
	WPoint();
	WPoint(int x_, int y_);
	virtual ~WPoint(); 

	static WPoint Empty() { return WPoint(); };
  bool IsEmpty() { return ((x<0) && (y<0)); };

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
  // is equal
  bool Equal(int color) { return color == m_color; };

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
  void setColor(WColor color) { m_color = color; };
  WColor getColor() { return m_color; };

  // points
  void AddPoint(const WPoint& point) { m_points.push_back(point); };
  bool AddPointAt(const WPoint& point, size_t idx);
  WPoint getPoint(size_t idx) { return m_points.size() > idx ? m_points[idx] : WPoint::Empty(); };
  bool RemovePoint(size_t idx);
  int Lenght(){ return m_points.size(); }; 
  WPointsContainer getPoints() { return m_points; }
  bool Concat(WLine line); //TODO перейти к двум параметрам 

  int getScaler() { return m_scaler; };
  void setScaler(int scaler);

private:
  double            m_width;
  WPointsContainer  m_points;
  int m_scaler;
  WColor m_color;
};


APP_END_NAMESPACE

#endif // _VECTORIZATION_APP_BASE_TYPES_H_
