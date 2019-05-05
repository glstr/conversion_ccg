#include "planar_finder.h"


#include <iostream>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>

#include "file_adaptor.h"

namespace snow {
int PlanarFinder::get_plane_from_cloud(const std::string& file_input, ModelPara& mp) {
    CloudPtr cloud(new Cloud);
    int ret = FileAdaptor::get_cloud_from_file(file_input, *cloud);
    if (ret != ok) {
        return ret;
    }

    return get_plane_from_cloud(cloud, mp);
}

int PlanarFinder::get_plane_from_cloud(CloudPtr pcloud, ModelPara& mp) {
    pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
    pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
    // Create the segmentation object
    pcl::SACSegmentation<pcl::PointXYZRGB> seg;
    // Optional
    seg.setOptimizeCoefficients (true);
    // Mandatory
    seg.setModelType (pcl::SACMODEL_PLANE);
    seg.setMethodType (pcl::SAC_RANSAC);
    seg.setDistanceThreshold (0.01);
    
    seg.setInputCloud (pcloud);
    seg.segment (*inliers, *coefficients);
    
    if (inliers->indices.size () == 0) {
        PCL_ERROR("Could not estimate a planar model for the given dataset.");
        return (-1);
    }
    return 0;
}

} //end namespace snow;
