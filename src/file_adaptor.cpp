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
        float time;
        int r;
        int g;
        int b;
        fscanf(fp, "%f %f %f %d %d %d %f", &p.x, &p.y, &p.z, 
                &r, &g, &b, &time);
        p.r = r;
        p.g = g;
        p.b = b;
        cloud_ptr->push_back(p);
    }
    fclose(fp);
    return ok;
}

int FileAdaptor::output_cloud_to_file(const std::string& file_path,
        const Cloud* cloud) {
    if (file_path.empty()) {
        return invalid_param;
    }

    FILE* fp = fopen(file_path.c_str(), "w");
    if (fp == NULL) {
        return invalid_param;
    }

    for (size_t i = 0; i < cloud->points.size (); ++i) {
        float time = 1.0;
        fprintf(fp, "%f %f %f %d %d %d %f\n", cloud->points[i].x,
                cloud->points[i].y,
                cloud->points[i].z,
                cloud->points[i].r,
                cloud->points[i].g,
                cloud->points[i].b,
                time);
    }     
    fclose(fp);
    return 0;
}

} //end namespace snow; 
