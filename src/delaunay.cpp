
#include "delaunay.h"
#include "common.h"

#include <iostream>
#include <stdio.h>

#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>

#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkSmartPointer.h>
#include <vtkDelaunay2D.h>
#include <vtkDelaunay3D.h>

using namespace std;

namespace snow {
const int DefaultPointSize = 100000;

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
    fclose(fp);
}

void Delaunay::output(const std::string& output_file, OpeType type) {
    cout << "output file_path:" << output_file << endl;

    if (_points.size() == 0) {
        cout << "errmsg: no points" << endl;
        return; 
    }

    switch (type) {
        case VTKType:
            dela_impl(output_file);
            break;
        case PCLType:
            dela_impl_pcl(output_file);
            cout << "pcl" << endl;
            break;
        default:
            cout << "no type" << endl;;
    }
    return;
}

void Delaunay::dela_impl(const std::string& output_file) {
    std::string file_path(output_file);
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

void Delaunay::dela_impl_pcl(const std::string& output_file) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>); 
    cloud->reserve(DefaultPointSize); 
    for (int i = 0; i < _points.size(); ++i) {
        pcl::PointXYZ point;
        point.x = _points[i]._x;
        point.y = _points[i]._y;
        point.z = _points[i]._z;
        cloud->push_back(point);
    }
    cout << cloud->size();

    // Normal estimation*
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
    pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud (cloud);
    n.setInputCloud (cloud);
    n.setSearchMethod (tree);
    n.setKSearch (20);
    n.compute (*normals);
    //* normals should not contain the point normals + surface curvatures
    
    // Concatenate the XYZ and normal fields*
    pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals (new pcl::PointCloud<pcl::PointNormal>);
    pcl::concatenateFields (*cloud, *normals, *cloud_with_normals);
    //* cloud_with_normals = cloud + normals
    
    // Create search tree*
    pcl::search::KdTree<pcl::PointNormal>::Ptr tree2 (new pcl::search::KdTree<pcl::PointNormal>);
    tree2->setInputCloud (cloud_with_normals);
    
    // Initialize objects
    pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
    pcl::PolygonMesh triangles;
    
    // Set the maximum distance between connected points (maximum edge length)
    gp3.setSearchRadius (0.025);
    
    // Set typical values for the parameters
    gp3.setMu (3);
    gp3.setMaximumNearestNeighbors (200);
    gp3.setMaximumSurfaceAngle(M_PI/4); // 45 degrees
    gp3.setMinimumAngle(M_PI/18); // 10 degrees
    gp3.setMaximumAngle(2*M_PI/3); // 120 degrees
    gp3.setNormalConsistency(false);
    
    // Get result
    gp3.setInputCloud (cloud_with_normals);
    gp3.setSearchMethod (tree2);
    gp3.reconstruct (triangles);

    //output 
    pcl::io::saveVTKFile(output_file, triangles);
    cout << "done" << endl;
}

} 
