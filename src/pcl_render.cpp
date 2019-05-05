#include "pcl_render.h"

#include <iostream>

#include <pcl/visualization/pcl_visualizer.h>

#include "file_adaptor.h"

using namespace std;

namespace snow {
void PCLRender::render(const std::string& file_path) {
    CloudPtr cloud(new Cloud);
    cout << "render:" << endl;
    int ret = FileAdaptor::get_cloud_from_file(file_path, *cloud);
    if (ret != 0) {
        cout << "ret:" << ret;
        return;
    }
    
    pcl::visualization::PCLVisualizer viewer;
    viewer.addPointCloud(cloud);

    while(!viewer.wasStopped()) {
        viewer.spinOnce(); 
    }
}

} //end namespace snow;

