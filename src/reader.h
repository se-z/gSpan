#ifndef RED_H
#define RED_H

#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <vector>

#include "graph.h"
using namespace GRAPH;

using std::cout;
using std::endl;
using std::ifstream;
using std::stod;
using std::string;
using std::stringstream;
using std::to_string;
using std::vector;

namespace READ {
struct myReader {
  public:
    std::ifstream &property_read(std::ifstream &, vector<vector<double>> &);
    std::istream &struct_read(std::istream &, vector<Graph> &);

    myReader(const char *structured_file, vector<Graph> *TRAN);
};
} // namespace READ
#endif