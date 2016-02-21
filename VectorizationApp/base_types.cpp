/// Whiteteam
/// \file base_types.cpp
/// \brief This file contains base types
/// \author Whiteteam authors

#include "stdafx.h"
#include "base_types.h"

APP_BEGIN_NAMESPACE

WPoint::WPoint() :
  m_color(0 /*TODO: init by palette color default */), m_isInitialized(true)
{
}

WPoint::WPoint(WColor color) : 
  m_color(color), m_isInitialized(true)
{
}

WPoint::~WPoint(void)
{
}

APP_END_NAMESPACE