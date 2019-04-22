#pragma once

#include <string>

namespace snow {
class PCLRender {
public:
    PCLRender(void) {}     
    virtual ~PCLRender(void) {}

    static void render(const std::string& file_path);

};

} //end namespace snow;
