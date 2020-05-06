#include "reader.h"
using namespace GRAPH;

using std::cout;
using std::endl;

namespace READ {

myReader::myReader(const char *structured_file, vector<Graph> *TRANS) {

    ifstream fp_struct(structured_file);
    struct_read(fp_struct, *TRANS);

    cout << "test :: " << (*TRANS).size() << endl;
}

std::istream &myReader::struct_read(std::istream &is, vector<Graph> &TRANS) {

    Graph g(false);
    TRANS = vector<Graph>();

    while(true) {
        g.read(is);
        if(g.empty())
            break;
        TRANS.push_back(g);
    }

    return is;
}

} // namespace READ
