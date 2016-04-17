// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include "queue.h"
#include "stack.h"
#include "pqueue.h"
#include <map>
#include "disjointset.h"

// TODO: include any other headers you need; remove this comment
using namespace std;

Vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Vector<Vertex*> path;
    Stack<Vertex*> q;
    q.push(start);
    start->visited = true;

    while(!q.isEmpty())
    {
        Vertex* v = q.pop();

        if (v == end)
            break;

        for (auto edge : v->edges)
        {
            Vertex* next_v = edge->finish;
            if (!next_v->visited)
            {
                q.push(next_v);
                next_v->previous = v;
                next_v->visited = true;
            }
        }
    }

    Vertex* path_v = end;
    while (path_v && path_v->visited)
    {
        path.insert(0, path_v);
        path_v = path_v->previous;
    }
    return path;
}

Vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Vector<Vertex*> path;
    Queue<Vertex*> q;
    q.enqueue(start);
    start->visited = true;

    while(!q.isEmpty())
    {
        Vertex* v = q.dequeue();

        if (v == end)
            break;

        for (auto edge : v->edges)
        {
            Vertex* next_v = edge->finish;
            if (!next_v->visited)
            {
                q.enqueue(next_v);
                next_v->previous = v;
                next_v->visited = true;
            }
        }
    }

    Vertex* path_v = end;
    while (path_v && path_v->visited)
    {
        path.insert(0, path_v);
        path_v = path_v->previous;
    }
    return path;
}

Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    PriorityQueue<Vertex*> pqueue;
    Vector<Vertex*> path;

    pqueue.enqueue(start, 0);
    start->cost = 0.0;
    start->setColor(YELLOW);

    while(!pqueue.isEmpty())
    {
        Vertex* v = pqueue.dequeue();
        v->setColor(GREEN);

        if (v == end)
            break;

        for (auto edge : v->edges)
        {
            Vertex* next_v = edge->finish;
            if (next_v->getColor() == 0)
            {
                next_v->setColor(YELLOW);
                double next_cost = v->cost + edge->cost;
                next_v->previous = v;
                next_v->cost = next_cost;
                pqueue.enqueue(next_v, next_cost);
            }
            else if (next_v->getColor() == YELLOW)
            {
                double next_cost = v->cost + edge->cost;
                if (next_cost < next_v->cost)
                {
                    next_v->cost = next_cost;
                    next_v->previous = v;
                    pqueue.changePriority(next_v, next_v->cost);
                }
            }
        }
    }

    if (end->getColor() == GREEN)
    {
        Vertex* path_v = end;
        while (path_v->previous)
        {
            path.insert(0, path_v);
            path_v = path_v->previous;
        }
        path.insert(0, path_v);
    }
    return path;
}

Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    PriorityQueue<Vertex*> pqueue;
    Vector<Vertex*> path;

    pqueue.enqueue(start, 0 + heuristicFunction(start, end));
    start->cost = 0.0;
    start->setColor(YELLOW);

    while(!pqueue.isEmpty())
    {
        Vertex* v = pqueue.dequeue();
        v->setColor(GREEN);

        if (v == end)
            break;

        for (auto edge : v->edges)
        {
            Vertex* next_v = edge->finish;
            if (next_v->getColor() == 0)
            {
                next_v->setColor(YELLOW);
                double next_cost = v->cost + edge->cost;
                next_v->previous = v;
                next_v->cost = next_cost;
                pqueue.enqueue(next_v, next_cost + heuristicFunction(next_v, end));
            }
            else if (next_v->getColor() == YELLOW)
            {
                double next_cost = v->cost + edge->cost;
                if (next_cost < next_v->cost)
                {
                    next_v->cost = next_cost;
                    next_v->previous = v;
                    pqueue.changePriority(next_v, next_v->cost + heuristicFunction(next_v, end));
                }
            }
        }
    }

    if (end->getColor() == GREEN)
    {
        Vertex* path_v = end;
        while (path_v->previous)
        {
            path.insert(0, path_v);
            path_v = path_v->previous;
        }
        path.insert(0, path_v);
    }
    return path;
}

Set<Edge*> kruskal(BasicGraph& graph) {
    Set<Vertex*> vertexs = graph.getVertexSet();
    Set<Edge*> edges = graph.getEdgeSet();
    map<Vertex*, int> vet_index;
    PriorityQueue<Edge*> pqueue;

    for (Edge* edge : edges)
        pqueue.enqueue(edge, edge->cost);

    int N = vertexs.size();
    DisjointSet union_set(N);

    int i = 0;
    for (Vertex* vert : vertexs)
    {
        vet_index[vert] = i;
        ++i;
    }

    Set<Edge*> mst;

    while (union_set.count() > 1)
    {
        Edge* edge = pqueue.dequeue();
        int p = vet_index[edge->start];
        int q = vet_index[edge->finish];

        if (!union_set.connected(p, q))
        {
            union_set.connect(p, q);
            mst.add(edge);
        }

    }

    return mst;
}
