/// Whiteteam
/// \file math_utils.h
/// \brief This file contains math utils
/// \author Whiteteam authors


#ifndef _VECTORIZATION_APP_MATH_UTILS_H_
#define _VECTORIZATION_APP_MATH_UTILS_H_
#pragma once

#include "..\app\app_const.h"

APP_BEGIN_NAMESPACE

class MathUtils
{
  // return maximum of two values
  template<typename T> static T Max(T val1, T val2);
  // return minimum of two values
  template<typename T> static T Min(T val1, T val2);

};

APP_END_NAMESPACE


#endif // _VECTORIZATION_APP_MATH_UTILS_H_
