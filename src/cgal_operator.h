
#pragma once

#include <string>

namespace snow {
class CGALOperator {
public:
    enum OpCode {
        UnKnown = 0,
        Default = 1,
    };

    CGALOperator(const std::string& file_in, const std::string& flag) : 
        _file_in(file_in),
        _flag(flag) {}
    virtual ~CGALOperator(void) {} 

    void process();
private:
    OpCode get_opcode();

    std::string _file_in;
    std::string _flag;
};

}


