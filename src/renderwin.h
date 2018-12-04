
#pragma once

#include <string>

namespace snow {
class RenderWin {
public:
    RenderWin(void);
    virtual ~RenderWin(void);

    static void start(const std::string& file_path);
};

}
