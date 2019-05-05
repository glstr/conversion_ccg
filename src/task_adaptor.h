#pragma once

#include <map>
#include <string>

namespace snow {
struct TaskOption {
    std::string file_in;
    std::string file_out;
    std::string arg;
};

enum OpeCode {
    INVALID_METHOD = -1,
    TOVTM = 0,
    TOM = 1,
    RENDER = 2,
    VTKTOM = 3,
    PCL = 4,
    CGAL = 5,
};

class TaskAdaptor {
public:
    TaskAdaptor(void) {}
    virtual ~TaskAdaptor(void) {}

    typedef int (*TaskFunc) (TaskOption& options);
    int init();

    int accept_task(const std::string& method, TaskOption& options);
private:
    TaskFunc get_ope_code(const std::string& ope_name);

    static int dela_convert_task(TaskOption& options);
    static int render_task(TaskOption& options);
    static int pcl_task(TaskOption& options); 
    static int cgal_task(TaskOption& options);
    static int file_conv_task(TaskOption& options);


    std::map<std::string, TaskFunc> method_task;
};

} //end namespace snow;
