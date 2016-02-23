//#pragma comment(lib, "setupapi.lib")

#ifdef WVECTORIZEDLL_EXPORTS
#define WVECTORIZEDLL __declspec(dllexport) 
#else
#define WVECTORIZEDLL __declspec(dllimport) 
#endif

#include "app\app_const.h"

#include <vector>

APP_BEGIN_NAMESPACE

class Vectorizer
{
public:
  static WVECTORIZEDLL bool Vectorize(std::string in, std::string out);

private:
};

APP_END_NAMESPACE