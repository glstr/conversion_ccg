
#include "fileconv.h"

#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>
#include <vtkSmartPointer.h>

#include <iostream>

using namespace std;

namespace snow {
FileConv::FileConv(void) {
}

FileConv::~FileConv(void) {
}

void FileConv::vtkToM(const std::string& file_in, const std::string& file_out) {
    cout << "file in:" << file_in << endl;
    cout << "file out:" << file_out << endl;
    
    vtkSmartPointer<vtkPolyDataReader> reader = 
        vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(file_in.c_str());
    reader->Update();
    
    vtkPolyData* data = reader->GetOutput();
    //获取点
    vtkPoints* points = data->GetPoints();
    //获取三角形
    vtkCellArray* cell_array = data->GetPolys();
    //vtkCellArray* cell_array = data->GetStrips();
        
    //输出m文件
    FILE* fp = fopen(file_out.c_str(), "w");
    //输出点
    if (fp == NULL) {
        cout << "open file error" << endl;
    }
    vtkIdType num = points->GetNumberOfPoints();
    double point[3];
    for (int i = 0; i < (int)num; ++i){
        points->GetPoint(i, point);
        fprintf(fp, "Vertex %d %lf %lf %lf\r\n", i, point[0], point[1], point[2]);
    }
    //输出面
    //cell_array->InitTraversal();
    vtkSmartPointer<vtkIdList> list =
        vtkSmartPointer<vtkIdList>::New();
    int i = 0;
    while (cell_array->GetNextCell(list)) {
        cout << list << endl;
        int a = (int)list->GetId(0);
        int b = (int)list->GetId(1);
        int c = (int)list->GetId(2);
        fprintf(fp, "Face %d %d %d %d\r\n", i, a, b, c);
        ++i;
    } 
    fclose(fp);
}

}
