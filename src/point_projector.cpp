#include "point_projector.h"

#include <pcl/ModelCoefficients.h>
#include <pcl/filters/project_inliers.h>

#include <stdio.h>

using namespace std;

namespace snow {
int PointProjector::project_to_a_plane(const std::string& file_input,
        const std::string& file_output, const ModelPara& mp) {
    CloudPtr cloud(new Cloud());       
    int ret = FileAdaptor::get_cloud_from_file(file_input, *cloud);
    if (ret != ok) {
        return invalid_param;
    }       

    Cloud* output_cloud = new Cloud();
    ret = project_to_a_plane(cloud, *output_cloud, mp);
    //if (ret != ok) {
    //    return ret;
    //}

    //CloudPtr ptr_output(output);
    ret = FileAdaptor::output_cloud_to_file(file_output, *output_cloud);
    return ret;
}

int PointProjector::project_to_a_plane(CloudPtr input, 
        Cloud& output, const ModelPara& mp) {
     // Create a set of planar coefficients with X=Y=0,Z=1
    pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients ());
    coefficients->values.resize (4);
    coefficients->values[0] = mp.a;
    coefficients->values[1] = mp.b;
    coefficients->values[2] = mp.c;
    coefficients->values[3] = mp.d;
    
    // Create the filtering object
    pcl::ProjectInliers<pcl::PointXYZRGB> proj;
    proj.setModelType(pcl::SACMODEL_PLANE);
    proj.setInputCloud(input);
    proj.setModelCoefficients(coefficients);
    proj.filter(output);
    return ok;
}

} //end namespace std;
