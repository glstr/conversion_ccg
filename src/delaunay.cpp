
#include "delaunay.h"
#include "common.h"

#include <iostream>
#include <stdio.h>

#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkSmartPointer.h>
#include <vtkDelaunay2D.h>
#include <vtkDelaunay3D.h>

using namespace std;

namespace snow {
const int DefaultPointSize = 10000;

Delaunay::Delaunay(void) : _file_path("") {

}

Delaunay::~Delaunay(void) {
}

void Delaunay::load(const std::string& file_path) {
    FILE* fp = fopen(file_path.c_str(), "r");    
    if (fp == NULL)  {
        cout << "errmsg:open file fail" << endl;        
    }

    _points.reserve(DefaultPointSize); 
    while (!feof(fp)) {
        PointXYZ point;
        fscanf(fp, "%lf %lf %lf\n", &point._x, &point._y, &point._z);
        _points.push_back(point);
    }
}

void Delaunay::output(const std::string& file_path, OpeType type) {
    cout << "output file_path:" << file_path << endl;

    if (_points.size() == 0) {
        cout << "errmsg: no points" << endl;
        return; 
    }

    switch (type) {
        case VTKType:
            dela_impl(file_path);
            break;
        default:
            cout << "no type" << endl;;
    }
    return;
}

void Delaunay::dela_impl(const std::string& file_path) {
    vtkSmartPointer<vtkPoints> points = 
        vtkSmartPointer<vtkPoints>::New();
    for (int i = 0; i < _points.size(); ++i) {
        points->InsertNextPoint(_points[i]._x, _points[i]._y, _points[i]._z);
    }
    vtkSmartPointer<vtkPolyData> polydata =
		vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);
 
	vtkSmartPointer<vtkDelaunay2D> del =
		vtkSmartPointer<vtkDelaunay2D>::New();
	del->SetInputData(polydata);
    del->Update();

    vtkSmartPointer<vtkPolyDataWriter> vtkWriter = 
        vtkSmartPointer<vtkPolyDataWriter>::New();
    vtkWriter->SetInputData(del->GetOutput());
    vtkWriter->SetFileName(file_path.c_str());
    vtkWriter->Write();
    return;
}

} 
