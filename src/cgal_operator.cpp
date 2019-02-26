
#include "cgal_operator.h"

namespace snow {
void CGALOperator::process() {
    int op_code = get_opcode();
    switch (op_code) {
        case Default:
            
    } 
}

CGALOperator::OpCode CGALOperator::get_opcode() {
    if (_flag == "default") {
        return Default;
    }
    return UnKnown;
}

}

