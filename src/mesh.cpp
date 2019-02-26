
#include "mesh.h"

#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>
#include <vtkSmartPointer.h>

#include <iostream>

using namespace std;

namespace snow {

void Mesh::meshInfo(std::string& mesh_info) {
    cout << "mesh info: " << mesh_info;     
    vtkSmartPointer<vtkPolyDataReader> reader =
        vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(mesh_info.c_str());
    reader->Update();

    vtkPolyData* data = reader->GetOutput();
    vtkSmartPointer<vtkPolyData> polydata =
        vtkSmartPointer<vtkPolyData>(data);

    //get info of poly data
}  

}
