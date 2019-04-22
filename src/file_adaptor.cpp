#include "file_adaptor.h"

#include <stdio.h>

namespace snow {
int FileAdaptor::get_cloud_from_file(const std::string& file_path, 
        CloudPtr& cloud_ptr) {
    if (file_path.empty()) {
        return invalid_param;
    }                 

    FILE* fp = fopen(file_path.c_str(), "r");
    if (fp == NULL) {
        return invalid_param;
    }

    cloud_ptr.reset(new Cloud);
    while(!feof(fp)) {
        Point p;
        double time;
        fscanf(fp, "%f %f %f %d %d %d %f", &p.x, &p.y, &p.z, &p.r, &p.g, &p.b, &time);
        cloud_ptr->push_back(p);
    }
    fclose(fp);
    return ok;
}

int FileAdaptor::output_cloud_to_file() {
}

} 
