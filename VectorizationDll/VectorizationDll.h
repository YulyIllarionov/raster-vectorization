//#pragma comment(lib, "setupapi.lib")

#ifdef WVECTORIZEDLL_EXPORTS
#define WVECTORIZEDLL __declspec(dllexport) 
#else
#define WVECTORIZEDLL __declspec(dllimport) 
#endif

#include "app\app_const.h"
#include "image_reader.h"
#include <vector>


APP_BEGIN_NAMESPACE

class WVECTORIZEDLL Vectorization {

public:

  Vectorization(std::string input_filename, std::string output_filename);
  virtual ~Vectorization();

  void SaveSkeletonizedImage();
  void SaveVectorizedImage();
  
  /*WVECTORIZEDLL*/ bool Vectorize(int scale/*, std::vector<POINT>& out_points*/);

private:
  
  
  std::string m_input_filename;
  std::string m_output_filename;

  //void* m_src_image; // for WImageRaster*
  WImageRaster m_src_image;



};

APP_END_NAMESPACE