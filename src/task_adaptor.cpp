#include "task_adaptor.h"

#include "common_flag.h"
#include "cgal_operator.h"
#include "delaunay.h"
#include "fileconv.h"
#include "renderwin.h"
#include "pcl_render.h"
#include "point_projector.h"

using namespace std;
namespace snow {
int TaskAdaptor::init() {
    method_task["todela"] = dela_convert_task;
    method_task["tom"] = NULL;
    method_task["render"] = render_task;
    method_task["vtkToM"] = file_conv_task;
    method_task["pcl"] = pcl_task;
    method_task["cgal"] = cgal_task;
    return 0;
}

TaskAdaptor::TaskFunc TaskAdaptor::get_ope_code(const std::string& ope_name) {
    auto search = method_task.find(ope_name);
    if (search != method_task.end()) {
        return search->second;
    } else {
        return NULL;
    }
}

int TaskAdaptor::accept_task(const std::string& method, TaskOption& options) {
    auto task = get_ope_code(method);
    if (task != NULL) {
        int ret = task(options);
        return ret;
    } else {
        return -1;
    }
}

int TaskAdaptor::dela_convert_task(TaskOption& options) {
    Delaunay dela;
    std::string file_in(options.file_in);
    std::string file_out(options.file_out);
    cout << "input file:" <<  file_in << endl;
    cout << "output file:" << file_out << endl;
    dela.load(file_in);
    if (options.arg == "vtk") {
        dela.output(file_out, Delaunay::VTKType);    
    }
    else if (options.arg == "pcl"){
        dela.output(file_out, Delaunay::PCLType);    
    }
    else {
        dela.output(file_out, Delaunay::MType);
    }
    //dela.output(file_out);
    return 0;
}

int TaskAdaptor::render_task(TaskOption& options) {
    std::string file_in(options.file_in);
    PCLRender::render(file_in); 
    return 0;
}

int TaskAdaptor::pcl_task(TaskOption& options) {
    PointProjector pp;
    std::string file_in(options.file_in);
    std::string file_out(options.file_out);
    ModelPara mp;
    int ret = pp.project_to_a_plane(file_in, file_out, mp);
    cout << ret << endl;
    return ret;
}

int TaskAdaptor::cgal_task(TaskOption& options) {
    std::string file_in(options.file_in);
    std::string file_out(options.file_out);
    std::string arg(options.arg);
    CGALOperator cgal_ope(file_in, file_out, arg);
    cgal_ope.process();
    return 0;
}

int TaskAdaptor::file_conv_task(TaskOption& options) {
    std::string file_in(options.file_in);
    std::string file_out(options.file_out);
    cout << "input file:" << file_in << endl;
    cout << "output file:" << file_out << endl;
    FileConv::vtkToM(file_in, file_out);
    return 0;
}


} // end namespace snow;
