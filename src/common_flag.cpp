
#include "common_flag.h"

DEFINE_bool(big_menu, true, "Include 'advanced' options in the menu listing");
DEFINE_string(ope, "", "make delaunay and output with vtk file");
DEFINE_string(arg, "vtk", "vtk or pcl");
DEFINE_string(in, "", "input file");
DEFINE_string(out, "", "output file");
