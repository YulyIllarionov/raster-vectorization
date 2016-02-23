/// Whiteteam
/// \file base_types.cpp
/// \brief This file contains base types
/// \author Whiteteam authors

#include "stdafx.h"
#include "base_types.h"

APP_BEGIN_NAMESPACE

WPoint::~WPoint(void) 
{
}

WPoint::WPoint(void) : 
  x(-1),y(-1)
{
}

WPoint::WPoint(int x_, int y_)
{
	x = x_;
	y = y_;
}

WPoint& WPoint::operator=(const WPoint& other)
{
	this->x=other.x;
	this->y=other.y;
  return *this;
}

bool WPoint::operator==(const WPoint& other) //TODO возможно inline 
{
  return (this->x == other.x) && (this->y == other.y);
	/*if ((this->x==other.x)&&(this->y==other.y))
	{
		return true;
	}
	return false;*/
}

bool WPoint::operator!=(const WPoint& other)
{
	if (*this==other)
	{
		return false;
	}
	return true;
}

WPixel::~WPixel(void)
{
}

WPixel::WPixel() :
  WPoint(), m_color(WCOLOR_WHITE /*TODO: init by palette color default */), 
  m_isInitialized(true)
{

}

WPixel::WPixel(WColor color, int x_, int y_) :
  WPoint (x_, y_), m_color(color), m_isInitialized(true)
{

}

WLine::WLine(void) :
  m_scaler(1), m_width(-1)  
{
}
WLine::~WLine()
{

}

bool WLine::RemovePoint(size_t idx)
{
	if ((m_points.size() > idx) && (!m_points.empty()))
	{
		m_points.erase(m_points.begin() + idx, m_points.begin() + idx);
		return true;
	}
	return false;
}

bool WLine::AddPointAt(const WPoint& point, size_t idx)
{
	if (m_points.size() < idx)
		return false;
	m_points.insert(m_points.begin() + idx, point);
	return true;
} 

void WLine::setWidth(double width)
{
	m_width = width;
}

void WLine::setScaler(int scaler)
{
	m_scaler = scaler;
}


bool WLine::Concat(WLine line)
{
	if (this->getPoint(0) != line.getPoint(0))
	{
		return false;
	}
    //line.RemovePoint(0);
	this->m_points.insert( this->m_points.begin(), line.getPoints().begin(), line.getPoints().end() );
	return true;
}

APP_END_NAMESPACE