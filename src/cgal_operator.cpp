
#include "cgal_operator.h"

#include <iostream>

#include <CGAL/Polyhedron_3.h>
#include <CGAL/Simple_cartesian.h>

namespace snow {
typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef Polyhedron::Halfedge_handle Halfedge_handle;

using namespace std;

void CGALOperator::process() {
    int op_code = get_opcode();
    switch (op_code) {
        case PolyhedronOpe:
            polyhedron_ope();
            break;        
        case HelloWorld:
            hello_world();
            break;
        case ShowExample:
            show_example();
            break;
        case MakePolyhedron:
            make_polyhedron();
        default:
            usage();
    } 
    return;
}

CGALOperator::OpCode CGALOperator::get_opcode() {
    if (_flag == "default") {
        return PolyhedronOpe;
    } else if (_flag == "helloworld") {
        return HelloWorld;
    } else if (_flag == "polyhedron_ope") {
        return PolyhedronOpe;
    } else if (_flag == "show_example") {
        return ShowExample;
    } else if (_flag == "make_polyhedron") {
        return MakePolyhedron;
    }
    return UnKnown;
}

void CGALOperator::polyhedron_ope() {
        
}

void CGALOperator::hello_world() {
    Point_2 p(1, 1), q(10, 10);            
    std::cout << "p=" << p << std::endl; 
    std::cout << "q = " << q.x() << " " << q.y() << std::endl;
}

void CGALOperator::show_example() {
    //poly simple
    poly_simple();    
}

void CGALOperator::poly_simple() {
    //Polyhedron p;
    //Halfedge_handle h = p.make_tetrahedron();    
    //if (p.is_tetrahedron(h)) {
    //    cout << "0" << endl;
    //    CGAL::draw(p);
    //    return;
    //}
}

void CGALOperator::make_polyhedron() {

}

void CGALOperator::usage() {
    cout << "hello world" << endl;
}

} //end namespace snow;

