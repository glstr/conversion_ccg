#pragma once

#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>

#include "file_adaptor.h"

namespace snow {
class PlanarFinder {
public:
    PlanarFinder(void) {}
    virtual ~PlanarFinder(void) {}

    int get_plane_from_cloud(const std::string& file_input, ModelPara& mp);

private:
    int get_plane_from_cloud(CloudPtr pcloud, ModelPara& mp);
};

} //end namespace snow;
