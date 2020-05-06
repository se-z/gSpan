#ifndef PRJ_H
#define PRJ_H

#include <cassert>
#include <cfloat>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <vector>

#include "graph.h"
using namespace GRAPH;

using std::map;
using std::string;
using std::vector;

namespace PROJECT {

class DFS {
  public:
    int from;      // id?
    int to;        // id?
    int fromlabel; // nodoの種類?
    int elabel;    // 接続する本数?
    int tolabel;   // nodoの種類?

    friend bool operator==(const DFS &d1, const DFS &d2) {
        return (d1.from == d2.from && d1.to == d2.to &&
                d1.fromlabel == d2.fromlabel && d1.elabel == d2.elabel &&
                d1.tolabel == d2.tolabel);
    }

    friend bool operator!=(const DFS &d1, const DFS &d2) {
        return (!(d1 == d2));
    }

    DFS() : from(0), to(0), fromlabel(0), elabel(0), tolabel(0){};

    DFS(int f, int to, int fl, int el, int tol)
        : from(f), to(to), fromlabel(fl), elabel(el), tolabel(tol){};
};

typedef std::vector<int> RMPath; // Right Most Path

struct DFSCode : public std::vector<DFS> {
  private:
    RMPath rmpath;

  public:
    const RMPath &buildRMPath();
    // 単体のDFSCodeが今どの展開ノードにいるかどうかをみるポインタ
    int ptr;
    int depth;
    int inner_value;

    bool toGraph(Graph &);
    // void fromGraph(Graph &);
    void toAdjancyMatrix(vector<vector<bool>> &, map<int, int> &);
    unsigned int nodeCount(void);
    void push(int from, int to, int fromlabel, int elabel, int tolabel);
    void pop();

    std::ostream &write(std::ostream &) const; // write
    std::ostream &writeCode(std::ostream &) const;
    std::ostream &writeCodeOrder(std::ostream &) const;

    friend std::ostream &operator<<(std::ostream &, const DFSCode &);

    std::string toString() const;
    void normalizeRM(DFSCode &);
    void findFTlabel(int, int, int &, int &);
    void inner(DFSCode &);
    std::ostream &innerOut(DFSCode &, std::ostream &);
};

struct PDFS {
    unsigned int id; // ID of the original input graph
    // Edge *edge;
    Edge *edge;
    PDFS *prev;

    PDFS() : id(0), edge(0), prev(0){};
};

class History : public std::vector<Edge *> {

  private:
    std::vector<int> edge;
    std::vector<int> vertex;

  public:
    bool hasEdge(unsigned int id) { return (bool)edge[id]; }

    bool hasVertex(unsigned int id) { return (bool)vertex[id]; }
    void build(Graph &, PDFS *);

    History(){};

    History(Graph &g, PDFS *p) { build(g, p); }
};

class Projected : public std::vector<PDFS> {
  public:
    void push(int graph_id, Edge *edge, PDFS *prev);
};

typedef std::vector<Edge *> EdgeList;
bool get_forward_pure(Graph &, Edge *, int, History &, EdgeList &);
bool get_forward_rmpath(Graph &, Edge *, int, History &, EdgeList &);
bool get_forward_root(Graph &, Vertex &, EdgeList &);
Edge *get_backward(Graph &, Edge *, Edge *, History &);
Graph *DFS2Graph(DFSCode &);
void builderEdge(Graph &);

typedef map<int, map<int, map<int, Projected>>> Projected_map3;
typedef map<int, map<int, Projected>> Projected_map2;
typedef map<int, Projected> Projected_map1;
typedef map<int, map<int, map<int, Projected>>>::iterator Projected_iterator3;
typedef map<int, map<int, Projected>>::iterator Projected_iterator2;
typedef map<int, Projected>::iterator Projected_iterator1;
typedef map<int, map<int, map<int, Projected>>>::reverse_iterator
    Projected_riterator3;

class gTraverse {
  protected:
    bool is_min();
    DFSCode DFS_CODE;
    DFSCode MAX_DFS_CODE;

  private:
    std::vector<std::vector<DFSCode>> WS_DFS_MTX;
    std::vector<DFSCode> TRAIN_MIN_DFS_MTX;

    DFSCode DFS_CODE_IS_MIN;
    Graph GRAPH_IS_MIN;

    unsigned int TRAVERSAL_ID;
    double MAX_DFS_LENGTH;

    bool directed;
    int KERNEL_MAX_DEPTH;
    Projected projected;

    bool project_is_min(Projected &);

    bool is_min_state(DFSCode &);
    bool project_is_min_state(Projected &, DFSCode &);

    void init();
    void __traverse();

  public:
    void traverse();
};

}; // namespace PROJECT

#endif // PRJ_H