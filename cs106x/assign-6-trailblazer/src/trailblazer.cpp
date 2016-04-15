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

    Vector<Vertex*> path;
    return path;
}

Set<Edge*> kruskal(BasicGraph& graph) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty set so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Set<Edge*> mst;
    return mst;
}
