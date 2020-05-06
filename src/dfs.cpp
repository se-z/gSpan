#include "projected.h"

using namespace std;

namespace PROJECT {

bool DFSCode::toGraph(Graph &g) {
    g.clear();

    for(DFSCode::iterator it = begin(); it != end(); ++it) {
        g.resize(std::max(it->from, it->to) + 1);

        if(it->fromlabel != -1)
            g[it->from].label = it->fromlabel;
        if(it->tolabel != -1)
            g[it->to].label = it->tolabel;

        g[it->from].push(it->from, it->to, it->elabel);
        if(!g.directed)
            g[it->to].push(it->to, it->from, it->elabel);
    }
    g.buildEdge();
    return true;
}

unsigned int DFSCode::nodeCount(void) {
    unsigned int nodecount = 0;

    for(DFSCode::iterator it = begin(); it != end(); ++it)
        nodecount =
            std::max(nodecount, (unsigned int)(std::max(it->from, it->to) + 1));

    return nodecount;
}

std::ostream &DFSCode::write(std::ostream &os) const {
    if(empty())
        return os;

    os << "(" << (*this)[0].fromlabel << ") " << (*this)[0].elabel << " (0f"
       << (*this)[0].tolabel << ")";

    for(unsigned int i = 1; i < size(); ++i) {
        if((*this)[i].from < (*this)[i].to)
            os << " " << (*this)[i].elabel << " (" << (*this)[i].from << "f"
               << (*this)[i].tolabel << ")";
        else
            os << " " << (*this)[i].elabel << " (b" << (*this)[i].to << ")";
    }
    return os;
}

std::ostream &DFSCode::writeCode(std::ostream &os) const {
    if(empty())
        return os;

    os << "v " << (*this)[0].from << " " << (*this)[0].fromlabel << endl
       << "e " << (*this)[0].from << " " << (*this)[0].to << " "
       << (*this)[0].elabel << endl
       << "v " << (*this)[0].to << " " << (*this)[0].tolabel << endl;

    for(unsigned int i = 1; i < size(); ++i) {
        if((*this)[i].from < (*this)[i].to) {
            os << "e " << (*this)[i].from << " " << (*this)[i].to << " "
               << (*this)[i].elabel << endl
               << "v " << (*this)[i].to << " " << (*this)[i].tolabel << endl;
        } else {
            os << "e " << (*this)[i].from << " " << (*this)[i].to << " "
               << (*this)[i].elabel << endl;
        }
    }
    os << endl;

    return os;
}

std::ostream &DFSCode::writeCodeOrder(std::ostream &os) const {

    if(empty())
        return os;

    if(size() == 1) {
        os << "v " << (*this)[0].from << " " << (*this)[0].fromlabel << endl;
        os << "v " << (*this)[0].to << " " << (*this)[0].tolabel << endl;
        os << "e " << (*this)[0].from << " " << (*this)[0].to << " "
           << (*this)[0].elabel << endl;
        return os;
    }

    map<int, int> vertexes;
    for(unsigned int i = 0; i < size(); ++i) {
        vertexes[(*this)[i].from] = (*this)[i].fromlabel;
        vertexes[(*this)[i].to] = (*this)[i].tolabel;
    }

    for(const auto &[id, label] : vertexes) {
        os << "v " << id << " " << label << endl;
    }

    for(unsigned int i = 0; i < size(); ++i) {
        os << "e " << (*this)[i].from << " " << (*this)[i].to << " "
           << (*this)[i].elabel << endl;
    }

    return os;
}

void DFSCode::normalizeRM(DFSCode &normalizeDFS) {

    normalizeDFS.clear();

    int from, to, flabel, elabel, tolabel;
    std::map<int, int> id2lable;
    for(unsigned int i = 0; i < size(); ++i) {
        from = (*this)[i].from;
        to = (*this)[i].to;
        flabel = (*this)[i].fromlabel;
        tolabel = (*this)[i].tolabel;

        if(flabel != -1) {
            if(!id2lable.count(from)) {
                id2lable[from] = flabel;
            }
        }

        if(tolabel != -1) {
            if(!id2lable.count(to)) {
                id2lable[to] = tolabel;
            }
        }
    }

    for(unsigned int i = 0; i < size(); ++i) {
        from = (*this)[i].from;
        to = (*this)[i].to;
        elabel = (*this)[i].elabel;
        DFS dfs(from, to, id2lable[from], elabel, id2lable[to]);
        normalizeDFS.push_back(dfs);
    }
}

void DFSCode::findFTlabel(int fromID, int toID, int &fromlabel, int &tolabel) {

    std::map<int, int> id2label;
    for(unsigned int i = 0; i < size(); ++i) {
        int from, to, flabel, elabel, tolabel;
        from = (*this)[i].from;
        to = (*this)[i].to;
        flabel = (*this)[i].fromlabel;
        tolabel = (*this)[i].tolabel;

        if(flabel != -1) {
            if(!id2label.count(from)) {
                id2label[from] = flabel;
            }
        }

        if(tolabel != -1) {
            if(!id2label.count(to)) {
                id2label[to] = tolabel;
            }
        }
    }

    fromlabel = id2label[fromID];
    tolabel = id2label[toID];
}

std::ostream &operator<<(std::ostream &os, const DFSCode &dfs) {
    dfs.writeCodeOrder(os);
    return os;
}

std::string DFSCode::toString() const {
    std::stringstream ss;
    this->write(ss);
    return std::string(ss.str());
}

void DFSCode::inner(DFSCode &dfs) {

    DFSCode normalizeDFS;
    int from, to, flabel, elabel, tolabel;
    std::map<int, int> id2lable;
    for(unsigned int i = 0; i < size(); ++i) {
        from = (*this)[i].from;
        to = (*this)[i].to;
        flabel = (*this)[i].fromlabel;
        tolabel = (*this)[i].tolabel;

        if(flabel != -1) {
            if(!id2lable.count(from)) {
                id2lable[from] = flabel;
            }
        }

        if(tolabel != -1) {
            if(!id2lable.count(to)) {
                id2lable[to] = tolabel;
            }
        }
    }

    for(unsigned int i = 0; i < dfs.size(); ++i) {
        from = (*this)[i].from;
        to = (*this)[i].to;
        elabel = (*this)[i].elabel;
        DFS dfs(from, to, id2lable[from], elabel, id2lable[to]);
        normalizeDFS.push_back(dfs);
    }

    int inner_ctr = 0;
    for(int i = 0; (int)i < dfs.size(); ++i) {
        if(dfs[i] != normalizeDFS[i]) {
            break;
        }
        inner_ctr++;
    }

    dfs.inner_value = inner_ctr;
    return;
}

std::ostream &DFSCode::innerOut(DFSCode &dfs, std::ostream &os) {

    DFSCode normalizeDFS;
    int from, to, flabel, elabel, tolabel;
    std::map<int, int> id2lable;
    for(unsigned int i = 0; i < size(); ++i) {
        from = (*this)[i].from;
        to = (*this)[i].to;
        flabel = (*this)[i].fromlabel;
        tolabel = (*this)[i].tolabel;

        if(flabel != -1) {
            if(!id2lable.count(from)) {
                id2lable[from] = flabel;
            }
        }

        if(tolabel != -1) {
            if(!id2lable.count(to)) {
                id2lable[to] = tolabel;
            }
        }
    }

    for(unsigned int i = 0; i < dfs.size(); ++i) {
        from = (*this)[i].from;
        to = (*this)[i].to;
        elabel = (*this)[i].elabel;
        DFS dfs(from, to, id2lable[from], elabel, id2lable[to]);
        normalizeDFS.push_back(dfs);
    }

    int inner_ctr = 0;
    for(int i = 0; (int)i < dfs.size(); ++i) {
        if(dfs[i] != normalizeDFS[i]) {
            break;
        }

        cout << normalizeDFS[i].from << ", " << normalizeDFS[i].to << ", "
             << normalizeDFS[i].fromlabel << ", " << normalizeDFS[i].elabel
             << ", " << normalizeDFS[i].tolabel << endl;
        inner_ctr++;
    }

    dfs.inner_value = inner_ctr;
    return os;
}

void DFSCode::push(int from, int to, int fromlabel, int elabel, int tolabel) {
    resize(size() + 1);
    DFS &d = (*this)[size() - 1];

    d.from = from;
    d.to = to;
    d.fromlabel = fromlabel;
    d.elabel = elabel;
    d.tolabel = tolabel;
}

void DFSCode::pop() { resize(size() - 1); }

} // namespace PROJECT
