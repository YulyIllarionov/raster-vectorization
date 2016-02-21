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

class WPoint;

typedef std::vector<WPoint>                WPointsContainer;
typedef std::vector<std::vector<WPoint> >  WMatrix;
typedef unsigned char                      WColor;

class WPoint
{
public:
  WPoint();
  WPoint(WColor color);
  virtual ~WPoint();

  // return Empty WPoint
  static WPoint Empty() { return WPoint(); };
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
  void set_Width();
  double get_Width();

  // points
  void AddPoint(const WPoint& point) { m_points.push_back(point); };
  WPoint get_Point(int idx) { return m_points.size() > idx ? m_points[idx] : WPoint::Empty(); };
  bool RemovePoint(int idx);


private:
  double            m_width;
  WPointsContainer  m_points;
};


APP_END_NAMESPACE

#endif // _VECTORIZATION_APP_BASE_TYPES_H_
