#pragma once

#include <string>

namespace snow {
class Polygon {
public:
    Polygon(void) {}
    virtual ~Polygon(void) {}

    struct Vertex {
        int32_t r;
        int32_t g;
        int32_t b;            
        double x;
        double y;
        double z;
    };

    void setVertex();
    void setLine();
    void setFace();

    void getVertex();
    void getLine();
    void getFace();
private:
};   


class ObjAdpator {
public:
    ObjAdpator(void) {}
    virtual ~ObjAdpator(void) {}
    static int output(const std::string& file_path, const Polygon& polygon); 
};

} //end namespace snow;

