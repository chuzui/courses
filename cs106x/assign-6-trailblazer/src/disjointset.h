#ifndef _DISJOINTSET_H
#define _DISJOINTSET_H

#include <vector>
using namespace std;

class DisjointSet
{
public:
    DisjointSet (int n): comp_count(n), parents(n)
    {
        for (int i = 0; i < n; ++i)
            parents[i] = i;
    };

    int find (int p)
    {
        while (p != parents[p])
            p = parents[p];
        return p;
    };

    bool connected (int p, int q)
    {
        return find(p) == find(q);
    };

    void connect (int p, int q)
    {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) return;

        parents[rootQ] = rootP;
        --comp_count;
    };

    int count()
    {
        return comp_count;
    };

private:
    int comp_count;
    vector<int> parents;
};

#endif
