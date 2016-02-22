/// Whiteteam
/// \file skeletonization.h
/// \brief This file contains skeletonization
/// \author Whiteteam authors

#ifndef _VECTORIZATION_APP_SKELETONIZATION_H_
#define _VECTORIZATION_APP_SKELETONIZATION_H_
#pragma once

#include "..\app\app_const.h"
#include "base_types.h"
#include <vector>

using namespace std;

APP_BEGIN_NAMESPACE


class WSkeletonizer
{

  enum PointTypeEnum
  {
    Undefined = 0x0,
    Background = 0x1,
    Foreground = 0x2,
    Any = Background | Foreground,  // Background or foreground
    C = 0x4,                        // Could be deleted
    Marked = 0x8                    // Marked
  };

  typedef unsigned char    SPoint;
  typedef vector<SPoint>   SRow;
  typedef vector<SRow>     WSkeleton;


  class SkeletonTemplate
  {
  public:

    SkeletonTemplate(int row, int column, int center_x, int center_y);
    WSkeleton m_points;
    std::pair<int, int> m_center;
 
  private:

    SkeletonTemplate() {};
  };


public:
  WSkeletonizer();
  
  // Initialize main templates
  void InitializeTemplates();

  // Initialize extended templates
  void InitializeTemplatesExt();

  bool Skeletonize(/*const*/ WMatrix& raster, WMatrix& skeleton);


private:


  bool InitializeSkeletonByRaster(/*const*/ WMatrix& raster, WSkeleton& skeleton);

  // pattern matching 
  // [out] index of matched pattern
  int MatchPatterns(WSkeleton& skeleton, int coord_x, int coord_y);

  // try matching certain pattern
  static bool MatchPattern(SkeletonTemplate& _template, WSkeleton& skeleton, 
    int coord_x, int coord_y);

  // is pattern could be checked
  //static bool IsPatternCouldBeChecked(SkeletonTemplate& _template, WSkeleton& skeleton, 
  //  int coord_x, int coord_y);

  // iû concave corner pixel
  bool IsConcaveCornelPixel(WSkeleton& skeleton, int coord_x, int coord_y);
  // is candidate for concave corner pixel
  bool IsCandidateConcaveCornelPixel(WSkeleton& skeleton, int coord_x, int coord_y, int pattern_num);


  vector<SkeletonTemplate> m_templates;
  vector<SkeletonTemplate> m_templates_ext;

};


APP_END_NAMESPACE

#endif // _VECTORIZATION_APP_SKELETONIZATION_H_
