
#include "common_flag.h"
#include "delaunay.h"
#include "fileconv.h"
#include "renderwin.h"


#include <iostream>
#include <string>

using namespace std;
using namespace snow;

enum OpeCode {
    TOVTM = 0,
    TOM = 1,
    RENDER = 2,
    VTKTOM = 3,
};

int get_ope_code(const std::string& ope_name) {
    if (ope_name == "tovtk") {
        return 0;
    } else if (ope_name == "tom") {
        return 1;
    } else if (ope_name == "render") {
        return 2;
    } else if (ope_name == "vtkToM") {
        return 3;
    }
    return -1;
}

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
        
    int ope_code = get_ope_code(FLAGS_ope);
    std::string file_in(FLAGS_in);
    std::string file_out(FLAGS_out);
    Delaunay dela;
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
            RenderWin::start(file_in);
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
    //delete dela;
    
    //string flag(argv[1]); 
    //if (flag == "-tovtk") {
    //    std::string input_file(argv[2]);
    //    std::string output_file(argv[3]);
    //    cout << "input file:" <<  input_file << endl;
    //    cout << "output file:" << output_file << endl;
    //    Delaunay *dela = new Delaunay;
    //    dela->load(input_file);
    //    dela->output(output_file);
    //    delete dela;
    //} else if (flag == "-tom") {
    //    cout << "to vtk" << endl;
    //} else if (flag == "-render") {
    //    std::string file_path(argv[2]);
    //    RenderWin::start(file_path);
    //} else if (flag == "-vtkToM") {
    //    std::string input_file(argv[2]);
    //    std::string output_file(argv[3]);
    //    cout << "input file:" <<  input_file << endl;
    //    cout << "output file:" << output_file << endl;
    //    FileConv::vtkToM(input_file, output_file);
    //}
    //else {
    //    cout << "hello world" << endl;
    //}
    return 1;
}

