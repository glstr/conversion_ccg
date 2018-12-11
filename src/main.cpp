
#include "common_flag.h"
#include "delaunay.h"
#include "fileconv.h"
#include "renderwin.h"


#include <iostream>
#include <string>

using namespace std;
using namespace snow;

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    if (FLAGS_big_menu) {
        cout << "right" << endl;
    }

    if (argc < 3) {
        cout << "param error" << endl; 
        return 1;
    }

    string flag(argv[1]); 
    if (flag == "-tovtk") {
        std::string input_file(argv[2]);
        std::string output_file(argv[3]);
        cout << "input file:" <<  input_file << endl;
        cout << "output file:" << output_file << endl;
        Delaunay *dela = new Delaunay;
        dela->load(input_file);
        dela->output(output_file);
        delete dela;
    } else if (flag == "-tom") {
        cout << "to vtk" << endl;
    } else if (flag == "-render") {
        std::string file_path(argv[2]);
        RenderWin::start(file_path);
    } else if (flag == "-vtkToM") {
        std::string input_file(argv[2]);
        std::string output_file(argv[3]);
        cout << "input file:" <<  input_file << endl;
        cout << "output file:" << output_file << endl;
        FileConv::vtkToM(input_file, output_file);
    }
    else {
        cout << "hello world" << endl;
    }
    return 1;
}

