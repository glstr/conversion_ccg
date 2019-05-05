
#include "common_flag.h"
#include "task_adaptor.h"

#include <iostream>
#include <string>

using namespace std;
using namespace snow;

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    //int ope_code = get_ope_code(FLAGS_ope);
    std::string file_in(FLAGS_in);
    std::string file_out(FLAGS_out);
    std::string arg(FLAGS_arg);
    TaskAdaptor ta;
    int ret = ta.init();
    if (ret != 0) {
        cout << "task adaptor init fail" << endl;
        return -1;  
    }         
    TaskOption options;
    options.file_in = file_in;
    options.file_out = file_out;
    options.arg = arg;
    ret = ta.accept_task(FLAGS_ope, options);
    cout << "method: " << FLAGS_ope << endl
        << "ret: " << ret; 
    return 1;
}

