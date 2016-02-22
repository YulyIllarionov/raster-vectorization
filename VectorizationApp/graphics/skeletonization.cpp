/// Whiteteam
/// \file skeletonization.cpp
/// \brief This file contains skeletonization
/// \author Whiteteam authors

#include "stdafx.h"
#include "skeletonization.h"

APP_BEGIN_NAMESPACE

const int kColorNone = 0;

WSkeletonizer::SkeletonTemplate::SkeletonTemplate(int row, int column, int center_x, int center_y)
  : m_center(std::make_pair<int, int>(center_x, center_y))
{
  m_points.clear();
  m_points.resize(row);
  /*for (int i = 0; i < row; ++i)
  {
    m_points.push_back(TemplateRow(column));
  }*/
}

WSkeletonizer::WSkeletonizer()
{
  InitializeTemplates();
  InitializeTemplatesExt();
}

void WSkeletonizer::InitializeTemplates()
{
  // #1
  // 1 1 y
  // 1 c 0
  // 1 1 y
  {
    SkeletonTemplate _template(3, 3, 1, 1);

    SRow row1, row2, row3;
    row1.push_back(Foreground); row1.push_back(Foreground); row1.push_back(Any); 
    row2.push_back(Foreground); row2.push_back(C);          row2.push_back(Background);
    row3.push_back(Foreground); row3.push_back(Foreground); row3.push_back(Any);

    _template.m_points.push_back(row1);
    _template.m_points.push_back(row2);
    _template.m_points.push_back(row3);

    m_templates.push_back(_template);
  }

  // #2
  // 1 1 1
  // 1 c 1
  // y 0 y
  {
    SkeletonTemplate _template(3, 3, 1, 1);

    SRow row1, row2, row3;
    row1.push_back(Foreground); row1.push_back(Foreground); row1.push_back(Foreground);
    row2.push_back(Foreground); row2.push_back(C);          row2.push_back(Foreground);
    row3.push_back(Any);        row3.push_back(Background); row3.push_back(Any);

    _template.m_points.push_back(row1);
    _template.m_points.push_back(row2);
    _template.m_points.push_back(row3);

    m_templates.push_back(_template);
  }

  // #3
  // y 1 1
  // 0 c 1 1
  // y 1 1
  {
    SkeletonTemplate _template(3, 4, 1, 1);

    SRow row1, row2, row3;
    row1.push_back(Any);        row1.push_back(Foreground); row1.push_back(Foreground);
    row2.push_back(Background); row2.push_back(C);          row2.push_back(Foreground); row2.push_back(Foreground);
    row3.push_back(Any);        row3.push_back(Foreground); row3.push_back(Foreground);

    _template.m_points.push_back(row1);
    _template.m_points.push_back(row2);
    _template.m_points.push_back(row3);

    m_templates.push_back(_template);
  }

  // #4
  // y 0 y
  // 1 c 1
  // 1 1 1
  //   1
  {
    SkeletonTemplate _template(4, 3, 1, 1);

    SRow row1, row2, row3, row4;
    row1.push_back(Any);        row1.push_back(Background); row1.push_back(Any);
    row2.push_back(Foreground); row2.push_back(C);          row2.push_back(Foreground);
    row3.push_back(Foreground); row3.push_back(Foreground); row3.push_back(Foreground);
    row4.push_back(Undefined);  row4.push_back(Foreground);

    _template.m_points.push_back(row1);
    _template.m_points.push_back(row2);
    _template.m_points.push_back(row3);
    _template.m_points.push_back(row4);

    m_templates.push_back(_template);
  }

  // #5
  // x 0 0
  // 1 c 0
  // x 1 x

  // #6
  // x 1 1 
  // 0 c 1
  // 0 0 x

  // #7
  // 0 1 0
  // 0 c 1
  // 0 0 0

  // #8
  // x 1 x
  // 1 c 0
  // x 0 0

  // #9
  // 0 0 x
  // 0 x 1
  // x 1 1

  // #10
  // 0 0 0
  // 0 c 1
  // 0 1 0

  // #11
  // 0 0 0
  // 0 c 0
  // 1 1 1

  // #12
  // 1 0 0
  // 1 c 0
  // 1 0 0

  // #13
  // 1 1 1
  // 0 c 0
  // 0 0 0

  // #14
  // 0 0 1
  // 0 c 1
  // 0 0 1

}

void WSkeletonizer::InitializeTemplatesExt()
{
  // #1 ext left down
  // 1 x 1 x
  // 1 1 x 1
  // 1 c 1 x
  // 0 1 1 1
  {
    SkeletonTemplate _template(4, 4, 1, 2);

    SRow row1, row2, row3, row4;
    row1.push_back(Foreground); row1.push_back(Any);        row1.push_back(Foreground); row1.push_back(Any);
    row2.push_back(Foreground); row2.push_back(Foreground); row2.push_back(Any);        row2.push_back(Foreground);
    row3.push_back(Foreground); row3.push_back(C);          row3.push_back(Foreground); row3.push_back(Any);
    row4.push_back(Background); row4.push_back(Foreground); row4.push_back(Foreground); row4.push_back(Foreground);

    _template.m_points.push_back(row1);
    _template.m_points.push_back(row2);
    _template.m_points.push_back(row3);
    _template.m_points.push_back(row4);

    m_templates_ext.push_back(_template);
  }

  // #2 ext left up
  // 0 1 1 1
  // 1 c 1 x
  // 1 1 x 1
  // 1 x 1 x
  {
    SkeletonTemplate _template(4, 4, 1, 2);

    SRow row1, row2, row3, row4;
    row1.push_back(Background); row1.push_back(Foreground); row1.push_back(Foreground); row1.push_back(Foreground);
    row2.push_back(Foreground); row2.push_back(C);          row2.push_back(Foreground); row2.push_back(Any);
    row3.push_back(Foreground); row3.push_back(Foreground); row3.push_back(Any);        row3.push_back(Foreground);
    row4.push_back(Foreground); row4.push_back(Any);        row4.push_back(Foreground); row4.push_back(Any);

    _template.m_points.push_back(row1);
    _template.m_points.push_back(row2);
    _template.m_points.push_back(row3);
    _template.m_points.push_back(row4);

    m_templates_ext.push_back(_template);
  }


  // #3 ext right up
  // 1 1 1 0
  // x 1 c 1
  // 1 x 1 1
  // x 1 x 1
  {
    SkeletonTemplate _template(4, 4, 1, 2);

    SRow row1, row2, row3, row4;
    row1.push_back(Foreground); row1.push_back(Foreground); row1.push_back(Foreground); row1.push_back(Background);
    row2.push_back(Any);        row2.push_back(Foreground); row2.push_back(C);          row2.push_back(Foreground);
    row3.push_back(Foreground); row3.push_back(Any);        row3.push_back(Foreground); row3.push_back(Foreground);
    row4.push_back(Any);        row4.push_back(Foreground); row4.push_back(Any);        row4.push_back(Foreground);

    _template.m_points.push_back(row1);
    _template.m_points.push_back(row2);
    _template.m_points.push_back(row3);
    _template.m_points.push_back(row4);

    m_templates_ext.push_back(_template);
  }

  // #4 ext right down
  // x 1 x 1
  // 1 x 1 1
  // x 1 c 1
  // 1 1 1 0
  {
    SkeletonTemplate _template(4, 4, 1, 2);

    SRow row1, row2, row3, row4;
    row1.push_back(Any);        row1.push_back(Foreground); row1.push_back(Any);        row1.push_back(Foreground);
    row2.push_back(Foreground); row2.push_back(Any);        row2.push_back(Foreground); row2.push_back(Foreground);
    row3.push_back(Any);        row3.push_back(Foreground); row3.push_back(C);          row3.push_back(Foreground);
    row4.push_back(Foreground); row4.push_back(Foreground); row4.push_back(Foreground); row4.push_back(Background);

    _template.m_points.push_back(row1);
    _template.m_points.push_back(row2);
    _template.m_points.push_back(row3);
    _template.m_points.push_back(row4);

    m_templates_ext.push_back(_template);
  }

}

bool WSkeletonizer::InitializeSkeletonByRaster(/*const*/ WMatrix& raster, WSkeleton& skeleton)
{
  skeleton.reserve(raster.size());
  for (int i = 0; i < raster.size(); i++)
  {
    skeleton[i].reserve(raster[i].size());
    for (int j = 0; j < raster[i].size(); j++)
    {
      skeleton[i][j] = raster[i][j].Equal(kColorNone) ? Background : Foreground;
    }
  }
  return true;
}

int WSkeletonizer::MatchPatterns(WSkeleton& skeleton, int coord_x, int coord_y)
{
  for (int i = 0; i < m_templates.size(); i++)
  {
    if (MatchPattern(m_templates[i], skeleton, coord_x, coord_y))
      return i;
  }
  return -1;
}

//bool WSkeletonizer::IsPatternCouldBeChecked(SkeletonTemplate& _template, WSkeleton& skeleton,
//  int coord_x, int coord_y)
//{
//  int center_x = _template.m_center.first;
//  int center_y = _template.m_center.second;
//
//  int width = 0;
//  int height = _template.m_points.size();
//
//  for (int i = 0; i < _template.m_points.size(); i++)
//  {
//    for (int j = 0; j < _template.m_points[i].size(); j++)
//    {
//      if (width < _template.m_points[i].size())
//        width = _template.m_points[i].size();
//    }
//  }
//
//  return false;
//}

bool WSkeletonizer::MatchPattern(SkeletonTemplate& _template, WSkeleton& skeleton, 
  int coord_x, int coord_y)
{
  //if (IsPatternCouldBeChecked(_template, skeleton, coord_x, coord_y))
  //  return false;

  int center_x = _template.m_center.first;
  int center_y = _template.m_center.second;

  for (int i = 0; i < _template.m_points.size(); i++)
  {
    for (int j = 0; j < _template.m_points[i].size(); j++)
    {
      // is pattern could be checked
      if (coord_x - center_x + i < 0
        || coord_x - center_x + i >= _template.m_points[i].size()
        || coord_y - center_y + j < 0
        || coord_y - center_y + j >= _template.m_points.size())
      {
        continue;
      }

      if (skeleton[coord_x - center_x + i][coord_y - center_y + j]
        & _template.m_points[i][j] == 0)
      {
        return false;
      }
    }
  }
}

bool WSkeletonizer::IsConcaveCornelPixel(WSkeleton& skeleton, int coord_x, int coord_y)
{
  // only 1 of P(8) pixel is foreground.
  // p5 p6 p7
  // p4 p  p0
  // p3 p2 p1

  if (coord_x - 1 < 0 || coord_x + 1 >= skeleton[0].size()
    || coord_y - 1 < 0 || coord_y + 1 >= skeleton.size())
  {
    return false;
  }

  int background_pixels = 0;

  if (skeleton[coord_x + 1][coord_y] & Background != 0)
    background_pixels++;

  if (skeleton[coord_x + 1][coord_y - 1] & Background != 0)
    background_pixels++;

  if (skeleton[coord_x][coord_y - 1] & Background != 0)
    background_pixels++;

  if (skeleton[coord_x - 1][coord_y - 1] & Background != 0)
    background_pixels++;

  if (skeleton[coord_x - 1][coord_y] & Background != 0)
    background_pixels++;

  if (skeleton[coord_x - 1][coord_y + 1] & Background != 0)
    background_pixels++;

  if (skeleton[coord_x][coord_y + 1] & Background != 0)
    background_pixels++;

  if (skeleton[coord_x + 1][coord_y + 1] & Background != 0)
    background_pixels++;

  return background_pixels == 1;
}

bool WSkeletonizer::IsCandidateConcaveCornelPixel(WSkeleton& skeleton, 
  int coord_x, int coord_y, int pattern_num)
{
  switch (pattern_num)
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 8:
      return true;
    default:
      break;
  }

  return false;
}


bool WSkeletonizer::Skeletonize(/*const*/ WMatrix& raster, WMatrix& _skeleton)
{
  _skeleton.clear();

  // resize out skeleton
  _skeleton.resize(raster.size());
  for (int i = 0; i < raster.size(); i++)
  {
    _skeleton[i].resize(raster[i].size());
  }
  
  WSkeleton next_skeleton;
  if (!InitializeSkeletonByRaster(raster, next_skeleton))
    return false;

  WSkeleton curr_skeleton;
  bool pixel_was_deleted = false;
  do {
    curr_skeleton = next_skeleton; // ???
    for (int i = 0; i < curr_skeleton.size(); i++)
    {
      for (int j = 0; j < curr_skeleton[i].size(); j++)
      {
        if (curr_skeleton[i][j] == Foreground )
        {
          int pattern_num = MatchPatterns(curr_skeleton, i, j);
          if (pattern_num == -1)
            continue;
        
          next_skeleton[i][j] = Background;
          pixel_was_deleted = true;

          // every of 4 bound pixels
          // left down corner
          if (IsCandidateConcaveCornelPixel(curr_skeleton, i - 1, j - 1, pattern_num))
          {
            // check if marked
            if (curr_skeleton[i - 1][j - 1] & Marked == 0)
            {
              next_skeleton[i - 1][j - 1] |= Marked; // if not then mark
            }
            else if (MatchPattern(m_templates_ext[0], curr_skeleton, i - 1, j - 1))
            {
              next_skeleton[i - 1][j - 1] = Background;
            }
          }
          // left up corner
          if (IsCandidateConcaveCornelPixel(curr_skeleton, i - 1, j + 1, pattern_num))
          {
            // check if marked
            if (curr_skeleton[i - 1][j + 1] & Marked == 0)
            {
              next_skeleton[i - 1][j + 1] |= Marked; // if not then mark
            }
            else if (MatchPattern(m_templates_ext[1], curr_skeleton, i - 1, j + 1))
            {
              next_skeleton[i - 1][j + 1] = Background;
            }
          }
          // right up corner
          if (IsCandidateConcaveCornelPixel(curr_skeleton, i + 1, j + 1, pattern_num))
          {
            // check if marked
            if (curr_skeleton[i + 1][j + 1] & Marked == 0)
            {
              next_skeleton[i + 1][j + 1] |= Marked; // if not then mark
            }
            else if (MatchPattern(m_templates_ext[2], curr_skeleton, i + 1, j + 1))
            {
              next_skeleton[i + 1][j + 1] = Background;
            }
          }
          // right down corner
          if (IsCandidateConcaveCornelPixel(curr_skeleton, i + 1, j - 1, pattern_num))
          {
            // check if marked
            if (curr_skeleton[i + 1][j - 1] & Marked == 0)
            {
              next_skeleton[i + 1][j - 1] |= Marked; // if not then mark
            }
            else if (MatchPattern(m_templates_ext[3], curr_skeleton, i + 1, j - 1))
            {
              next_skeleton[i + 1][j - 1] = Background;
            }
          }
        }
      }
      
    }
  } while (pixel_was_deleted);

  for (int i = 0; i < next_skeleton.size(); i++)
  {
    for (int j = 0; j < next_skeleton[i].size(); j++)
    {
      if (next_skeleton[i][j] & Background)
        _skeleton[i][j] = raster[i][j];
    }
  }

  return false;
}



APP_END_NAMESPACE


