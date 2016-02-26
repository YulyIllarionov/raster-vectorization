//#pragma comment(lib, "setupapi.lib")

#ifdef WVECTORIZEDLL_EXPORTS
#define WVECTORIZEDLL __declspec(dllexport) 
#else
#define WVECTORIZEDLL __declspec(dllimport) 
#endif

#include "app\app_const.h"
//#include "image_reader.h"
#include <vector>


APP_BEGIN_NAMESPACE

class WVECTORIZEDLL Vectorization {

public:

    Vectorization(std::string input_filename);
    virtual ~Vectorization();

    void SaveSkeletonizedImage(std::string output_filename);
    void SaveVectorizedImage(std::string output_filename);
    std::vector<APP_NAMESPACE::WLine> GetLines() { return m_lines; };
    //std::vector<std::pair<std::vector<std::pair<int, int>>, int>> GetLines() { return m_lines; };


private:

    // std::string m_input_filename;

    void* m_vectorization; // for WImageRaster*

    std::vector<APP_NAMESPACE::WLine> m_lines;
    //std::vector<std::pair<std::vector<std::pair<int, int>>, int>> m_lines;


};

APP_END_NAMESPACE