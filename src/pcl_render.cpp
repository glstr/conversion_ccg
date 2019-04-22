#include "pcl_render.h"

#include <iostream>

#include <pcl/visualization/cloud_viewer.h>

#include "file_adaptor.h"

using namespace std;

namespace snow {
void PCLRender::render(const std::string& file_path) {
    CloudPtr cloud_ptr;
    cout << "render:" << endl;
    int ret = FileAdaptor::get_cloud_from_file(file_path, cloud_ptr);
    if (ret != 0) {
        cout << "ret:" << ret;
        return;
    }
    
    pcl::visualization::CloudViewer viewer("cloud");
    viewer.showCloud(cloud_ptr);

    while(!viewer.wasStopped()) {
     
    }
}

} //end namespace snow;

