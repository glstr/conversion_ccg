
#pragma once

#include <string>

namespace snow {
class FileConv {
public:
    FileConv(void);
    virtual ~FileConv(void);

    static void vtkToM(const std::string& file_in, const std::string& file_out);

private:
    void _vtkToM();
};

}
