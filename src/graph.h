#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using std::map;
using std::vector;

namespace GRAPH {

struct Edge {
    int from;
    int to;
    int elabel;
    unsigned int id;
    Edge() : from(0), to(0), elabel(0), id(0){};
};

class Vertex {
  public:
    typedef std::vector<Edge>::iterator edge_iterator;
    int label;
    std::vector<Edge> edge;
    void push(int from, int to, int elabel);
};

class Graph : public std::vector<Vertex> {

  private:
    unsigned int edge_size_;

  public:
    typedef std::vector<Vertex>::iterator vertex_iterator;
    Graph(bool _directed);
    bool directed;
    std::string mol_id;

    unsigned int edge_size() { return edge_size_; }
    unsigned int edge_size() const { return edge_size_; }

    void __registerEdge_size(int edge_size);
    unsigned int vertex_size();
    void buildEdge();

    std::istream &read(std::istream &);
    std::ostream &write(std::ostream &); // write
    void check(void);
    Graph() : edge_size_(0), directed(false){};
};

}; // namespace GRAPH

#endif // GSPAN_H
