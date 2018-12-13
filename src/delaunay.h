
#pragma once

#include <string>
#include <vector>

namespace snow {
struct PointXYZ {
    explicit PointXYZ() : _x(0.0), _y(0.0), _z(0.0) {}
    double _x;
    double _y;
    double _z;
};

class Delaunay {
public:
    Delaunay(void);
    virtual ~Delaunay(void);

    enum OpeType {
        VTKType = 0,
        PCLType = 1,
        MType = 2,
    };

    void load(const std::string& file_path);

    void output(const std::string& output_file, OpeType type=VTKType);

    void set_file_path(const std::string& file_path){
        _file_path = file_path;
    }
    const std::string&  get_file_path() {
        return _file_path;
    }
private:
    void dela_impl(const std::string& output_file);
    void dela_impl_pcl(const std::string& output_file);

private:
    std::string _file_path;
    std::vector<PointXYZ> _points;
};   
}
