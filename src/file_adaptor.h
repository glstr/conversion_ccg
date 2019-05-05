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

struct ModelPara {
        ModelPara() : 
        a(0.0), 
        b(1.0),
        c(0.0), 
        d(0.0) {}

        float a;         
        float b;
        float c;
        float d;
};

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
    static int get_cloud_from_file(const std::string& file_path, Cloud& cloud);
    static int output_cloud_to_file(const std::string& file_path, 
            const Cloud& cloud);
};

} //end namespace snow;

