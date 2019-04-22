#pragma once

#include <string>

#include <pcl/common/projection_matrix.h>
#include <pcl/point_types.h>

namespace snow {
typedef pcl::PointXYZRGB Point;
typedef pcl::PointCloud<pcl::PointXYZRGB> Cloud;
typedef pcl::PointCloud<pcl::PointXYZRGB>::Ptr CloudPtr;

const int invalid_param = -1;
const int ok = 0;

class FileAdaptor {
public:
    struct VertexTemp {
        int red;
        int green;
        int blue;
        double x;
        double y;
        double z;
        double t;
    };

    FileAdaptor(void) {}
    virtual ~FileAdaptor(void) {}
    static int get_cloud_from_file(const std::string& file_path, CloudPtr& cloud_ptr);

    static int output_cloud_to_file();
};

} //end namespace snow;

