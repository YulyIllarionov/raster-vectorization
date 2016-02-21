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

WPoint::WPoint() : 
x(-1),y(-1)
{
}

WPoint& WPoint::operator=(const WPoint& other)
{
	this->x=other.x;
	this->y=other.y;
}

WPoint::WPoint(int x_, int y_)
{
	x=x_;
	y=y_;
}

WPixel::~WPixel(void)
{
}

WPixel::WPixel() :
m_color(0 /*TODO: init by palette color default */), m_isInitialized(true)
{
}

WPixel::WPixel(WColor color, int x_ = -1, int y_ = -1) :
m_isInitialized(true)
{

}

bool WLine::RemovePoint(int idx)
{
	if ((m_points.size() > idx)&&(!m_points.empty()))
	{
		m_points.erase(m_points.begin()+idx,m_points.begin()+idx);
		return true;
	}
	return false;
}

bool WLine::AddPointAt(const WPixel& point, int idx)
{
	if (m_points.size() < idx)
		return false;
	m_points.insert(m_points.begin()+idx, point);
	return true;
} 

void WLine::setWidth(double width)
{
	m_width = width;
}


APP_END_NAMESPACE