#include "projected.h"

using std::cout;
using std::endl;

namespace PROJECT {

const RMPath &DFSCode::buildRMPath() {

    rmpath.clear();
    int old_from = -1; // old_fromってなんだ?
    int dfs_last_idx = size() - 1;
    for(int i = dfs_last_idx; i >= 0; --i) {
        if((*this)[i].from < (*this)[i].to &&
           (rmpath.empty() || old_from == (*this)[i].to)) {
            rmpath.push_back(i);
            old_from = (*this)[i].from;
        }
    }

    return rmpath;
}

void History::build(Graph &graph, PDFS *e) {
    // first build history
    clear();
    edge.clear();
    edge.resize(graph.edge_size());
    vertex.clear();
    vertex.resize(graph.size());

    if(e) {
        push_back(e->edge);
        edge[e->edge->id] = vertex[e->edge->from] = vertex[e->edge->to] = 1;

        for(PDFS *p = e->prev; p; p = p->prev) {
            push_back(p->edge); // this line eats 8% of overall instructions(!)
            edge[p->edge->id] = vertex[p->edge->from] = vertex[p->edge->to] = 1;
        }
        std::reverse(begin(), end());
    }
}

bool get_forward_rmpath(Graph &graph, Edge *e, int minlabel, History &history,
                        EdgeList &result) {
    result.clear();
    assert(e->to >= 0 && e->to < graph.size());
    assert(e->from >= 0 && e->from < graph.size());
    int tolabel = graph[e->to].label;

    for(Vertex::edge_iterator it = graph[e->from].edge.begin();
        it != graph[e->from].edge.end(); ++it) {
        int tolabel2 = graph[it->to].label;
        if(e->to == it->to || minlabel > tolabel2 || history.hasVertex(it->to))
            continue;
        if(e->elabel < it->elabel ||
           (e->elabel == it->elabel && tolabel <= tolabel2))
            result.push_back(&(*it));
    }

    return (!result.empty());
}

bool get_forward_pure(Graph &graph, Edge *e, int minlabel, History &history,
                      EdgeList &result) {
    result.clear();

    assert(e->to >= 0 && e->to < graph.size());

    for(auto &edg : graph[e->to].edge) {
        if(minlabel > graph[edg.to].label || history.hasVertex(edg.to)) {
            continue;
        }
        result.push_back(&edg);
    }

    return (!result.empty());
}

bool get_forward_root(Graph &g, Vertex &v, EdgeList &result) {

    result.clear();
    for(auto &edg : v.edge) {
        assert(edg.to >= 0 && edg.to < g.size());
        if(v.label <= g[edg.to].label) {
            result.push_back(&edg);
        }
    }
    return (!result.empty());
}

Edge *get_backward(Graph &graph, Edge *e1, Edge *e2, History &history) {
    if(e1 == e2)
        return 0;

    assert(e1->from >= 0 && e1->from < graph.size());
    assert(e1->to >= 0 && e1->to < graph.size());
    assert(e2->to >= 0 && e2->to < graph.size());

    for(Vertex::edge_iterator it = graph[e2->to].edge.begin();
        it != graph[e2->to].edge.end(); ++it) {
        if(history.hasEdge(it->id))
            continue;

        if((it->to == e1->from) &&
           ((e1->elabel < it->elabel) ||
            (e1->elabel == it->elabel) &&
                (graph[e1->to].label <= graph[e2->to].label))) {
            return &(*it);
        }
    }

    return 0;
}

void builderEdge(Graph &g) {

    char buf[512];
    std::map<std::string, unsigned int> tmp;
    unsigned int id = 0;

    for(int from = 0; from < (int)g.size(); ++from) {
        for(Vertex::edge_iterator it = g[from].edge.begin();
            it != g[from].edge.end(); ++it) {
            if(g.directed || from <= it->to)
                std::sprintf(buf, "%d %d %d", from, it->to, it->elabel);
            else
                std::sprintf(buf, "%d %d %d", it->to, from, it->elabel);

            // Assign unique id's for the edges.
            if(tmp.find(buf) == tmp.end()) {
                it->id = id;
                tmp[buf] = id;
                ++id;
            } else {
                it->id = tmp[buf];
            }
        }
    }

    g.__registerEdge_size(id);
}

Graph *DFS2Graph(DFSCode &dfs) {

    Graph g;

    int max_id = 0;
    for(int i = 0; i < (int)dfs.size(); ++i) {
        if(dfs[i].from > max_id) {
            max_id = dfs[i].from;
        }

        if(dfs[i].to > max_id) {
            max_id = dfs[i].to;
        }
    }

    g.resize(max_id + 1);

    unsigned int fid, tid;
    for(int i = 0; i < (int)dfs.size(); ++i) {
        fid = dfs[i].from;
        tid = dfs[i].to;

        g[fid].label = dfs[i].fromlabel;
        g[fid].push(fid, tid, dfs[i].elabel);
        g[tid].label = dfs[i].tolabel;
        g[tid].push(tid, fid, dfs[i].elabel);
    }

    builderEdge(g);

    return &g;
}

} // namespace PROJECT
