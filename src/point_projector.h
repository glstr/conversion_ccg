#pragma once

#include <pcl/point_types.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/filters/project_inliers.h>

#include "file_adaptor.h"

namespace snow {

class PointProjector {
public:
    PointProjector(void) {}
    virtual ~PointProjector(void) {}

    int project_to_a_plane(const std::string& file_input, 
            const std::string& file_output, const ModelPara& mp);
    int project_to_a_plane(CloudPtr input, Cloud& output, 
            const ModelPara& mp);
private:
};

} //end namespace snow;
