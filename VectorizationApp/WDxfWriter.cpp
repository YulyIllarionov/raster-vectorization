#include "StdAfx.h"
#include "WDxfWriter.h"


APP_BEGIN_NAMESPACE
WDxfWriter::WDxfWriter(char *filename)
{
    this->filename = filename;
    dw = dxf.out(filename, DL_Codes::AC1015);

}


WDxfWriter::~WDxfWriter()
{
    delete dw;
}
void WDxfWriter::begin()
{
    // section header:
    dxf.writeHeader(*dw);
    dw->sectionEnd();

    // section tables:
    dw->sectionTables();

    // VPORT:
    dxf.writeVPort(*dw);

    // LTYPE:
    dw->tableLinetypes(1);
    dxf.writeLinetype(*dw, DL_LinetypeData("CONTINUOUS", "Continuous", 0, 0, 0.0));
    dxf.writeLinetype(*dw, DL_LinetypeData("BYLAYER", "", 0, 0, 0.0));
    dxf.writeLinetype(*dw, DL_LinetypeData("BYBLOCK", "", 0, 0, 0.0));
    dw->tableEnd();

    // LAYER:
    dw->tableLayers(1);
    dxf.writeLayer(
        *dw,
        DL_LayerData("0", 0),
        DL_Attributes("", DL_Codes::black, 0, 100, "CONTINUOUS")
        );
    dw->tableEnd();

    // STYLE:
    dw->tableStyle(1);
    DL_StyleData style("Standard", 0, 0.0, 1.0, 0.0, 0, 2.5, "txt", "");
    style.bold = false;
    style.italic = false;
    dxf.writeStyle(*dw, style);
    dw->tableEnd();

    // VIEW:
    dxf.writeView(*dw);

    // UCS:
    dxf.writeUcs(*dw);

    // APPID:
    dw->tableAppid(1);
    dxf.writeAppid(*dw, "ACAD");
    dw->tableEnd();

    // DIMSTYLE:
    dxf.writeDimStyle(*dw, 2.5, 0.625, 0.625, 0.625, 2.5);

    // BLOCK_RECORD:
    dxf.writeBlockRecord(*dw);
    dw->tableEnd();

    dw->sectionEnd();

    // ENTITIES:
    dw->sectionEntities();

}

void WDxfWriter::end()
{
    dw->sectionEnd();
    dxf.writeObjects(*dw, "MY_OBJECTS");
    dxf.writeObjectsEnd(*dw);
    dw->dxfEOF();
    dw->close();
    delete dw;
}

void WDxfWriter::writePolyLine(WLine line)
{
    DL_Attributes attr("mainlayer", 7, line.getWidth()*100, "BYLAYER", 1.0);
    int num_points = line.Lenght() % line.getScaler() == 0 ? (line.Lenght() / line.getScaler()): (line.Lenght() / line.getScaler() + 1);
    dxf.writePolyline(*dw, DL_PolylineData(num_points, 0, 0, 0), attr);
    
    for (int i = 0;i < line.Lenght();i++)
    {
        if ((i + 1) % line.getScaler() == 0)
            dxf.writeVertex(*dw, DL_VertexData(line.getPoint(i).x, line.getPoint(i).y, 0, 0));
    }
    dxf.writeVertex(*dw, DL_VertexData(line.getPoint(line.Lenght()-1).x, line.getPoint(line.Lenght() - 1).y, 0, 0));
    dxf.writePolylineEnd(*dw);
}

APP_END_NAMESPACE

