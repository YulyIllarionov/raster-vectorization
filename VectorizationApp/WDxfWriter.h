#ifndef _WDXFWRITER_H_
#define _WDXFWRITER_H_
#pragma once
#include "base_types.h"
#include "libs\dl_dxf.h"
using namespace std;

APP_BEGIN_NAMESPACE
class WDxfWriter
{
public:
    WDxfWriter(const char *filename);
    ~WDxfWriter();
    void begin();
    void end();
    void writePolyLine(WLine line, int height);
    DL_Dxf dxf;
    DL_WriterA* dw;
private:
    string filename;
};
APP_END_NAMESPACE
#endif