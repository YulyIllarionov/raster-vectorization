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

bool WLine::RemovePoint(int idx)
{
	if ((m_pixels.size() > idx) && (!m_pixels.empty()))
	{
		m_pixels.erase(m_pixels.begin() + idx, m_pixels.begin() + idx);
		return true;
	}
	return false;
}

bool WLine::AddPointAt(const WPixel& point, int idx)
{
	if (m_pixels.size() < idx)
		return false;
	m_pixels.insert(m_pixels.begin() + idx, point);
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
	if (this->getPixel(0) != line.getPixel(0))
	{
		return false;
	}
	this->m_pixels.insert( this->m_pixels.begin(), line.getPixels().begin(), line.getPixels().end() );
	return true;
}

APP_END_NAMESPACE