
#include "common_flag.h"
#include "cgal_operator.h"
#include "delaunay.h"
#include "fileconv.h"
#include "renderwin.h"
#include "pcl_render.h"

#include <iostream>
#include <string>

using namespace std;
using namespace snow;

enum OpeCode {
    TOVTM = 0,
    TOM = 1,
    RENDER = 2,
    VTKTOM = 3,
    PCL = 4,
    CGAL = 5,
    };

int get_ope_code(const std::string& ope_name) {
    if (ope_name == "todela") {
        return TOVTM;
    } else if (ope_name == "tom") {
        return TOM;
    } else if (ope_name == "render") {
        return RENDER;
    } else if (ope_name == "vtkToM") {
        return VTKTOM;
    } else if (ope_name == "pcl") {
        return PCL;
    } else if (ope_name == "cgal") {
        return CGAL;
    }
    return -1;
}

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    cout << "enter" << endl;        
    int ope_code = get_ope_code(FLAGS_ope);
    std::string file_in(FLAGS_in);
    std::string file_out(FLAGS_out);
    Delaunay dela;
    CGALOperator cgal_ope(file_in, file_out, FLAGS_arg);
    switch (ope_code) {
        case TOVTM:
            cout << "input file:" <<  file_in << endl;
            cout << "output file:" << file_out << endl;
            dela.load(file_in);
            if (FLAGS_arg == "vtk") {
                dela.output(file_out, Delaunay::VTKType);    
            }
            else if (FLAGS_arg == "pcl"){
                dela.output(file_out, Delaunay::PCLType);    
            }
            else {
                dela.output(file_out, Delaunay::MType);
            }
            //dela.output(file_out);
            break;
        case TOM:
            cout << "to vtk" << endl;
            break;
        case RENDER:
            cout << "render" << endl;
            //RenderWin::start(file_in);
            PCLRender::render(file_in); 
            break;
        case PCL:
            cout << "pcl" << endl;
            break; 
        case CGAL:
            cout << "cgal" << endl;
            cgal_ope.process();
            break;
        case VTKTOM:
            cout << "input file:" << file_in << endl;
            cout << "output file:" << file_out << endl;
            FileConv::vtkToM(file_in, file_out);
            break; 
        default:
            cout << "hello world" << endl;
            break;
    } 
    return 1;
}

