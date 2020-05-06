#include "projected.h"

namespace PROJECT {

    void Projected::push(int graph_id, Edge *edge, PDFS *prev) {
        resize(size() + 1);
        PDFS &d = (*this)[size() - 1];
        d.id = graph_id;
        d.edge = edge;
        d.prev = prev;
    }

}