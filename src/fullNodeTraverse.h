#ifndef FULLN_T_H
#define FULLN_T_H

#include "projected.h"

using PROJECT::DFSCode;
using PROJECT::EdgeList;
using PROJECT::get_backward;
using PROJECT::get_forward_pure;
using PROJECT::get_forward_rmpath;
using PROJECT::get_forward_root;
using PROJECT::gTraverse;
using PROJECT::History;
using PROJECT::PDFS;
using PROJECT::Projected;
using PROJECT::Projected_map2;
using PROJECT::Projected_map3;
using PROJECT::RMPath;

using std::cout;
using std::endl;
using std::string;

namespace FULL_TRAVERSE {

class gFullNodeTraverser : gTraverse {

  private:
    void __traverse(int, Projected &);
    const int DATA_SIZE;
    const int MAX_DEPTH;
    const int MIN_SUP;
    vector<Graph> *TRANSACTION;

  public:
    void traverse();
    double traverse_space_size;
    gFullNodeTraverser(vector<Graph> *TRANS, int min_sup, int max_depth);
};

} // namespace FULL_TRAVERSE

#endif