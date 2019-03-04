
#pragma once

#include <string>

namespace snow {
class CGALOperator {
public:
    enum OpCode {
        UnKnown = 0,
        PolyhedronOpe = 1,
        HelloWorld = 2,
        ShowExample,
    };

    CGALOperator(const std::string& file_in, const std::string& file_out, 
            const std::string& flag) : 
        _file_in(file_in),
        _flag(flag) {}
    virtual ~CGALOperator(void) {} 

    void process();

private:
    OpCode get_opcode();
    void polyhedron_ope();
    void hello_world();
    void usage();

    //example 
    void show_example();

    //polyhedra example
    void poly_simple();
    

    std::string _file_in;
    std::string _file_out;
    std::string _flag;
};

} //end namespace snow;


