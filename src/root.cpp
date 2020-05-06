
#include "root.h"
#include "string.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::map;
using std::max;
using std::pow;
using std::stod;
using std::string;
using std::stringstream;
using std::to_string;
using std::vector;

namespace INIT_SPACE {

ROOT::ROOT(const char *structured_file, std::string out_root_dir,
           int minimum_support, int max_depth)
    : myreader(structured_file, &ALL_TRANS), OutDirRootPath(out_root_dir),
      traverser(&ALL_TRANS, minimum_support, max_depth){};

// void INIT_SPACE::init() {
//     auto score_dir = OutDirRootPath;
//     return;
// }

void ROOT::traverse() { traverser.traverse(); }
} // namespace INIT_SPACE
