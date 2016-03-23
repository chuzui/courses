/**
 * File: KDTree.h
 * Author: (your name here)
 * ------------------------
 * An interface representing a kd-tree in some number of dimensions. The tree
 * can be constructed from a set of data and then queried for membership and
 * nearest neighbors.
 */

#ifndef KDTREE_INCLUDED
#define KDTREE_INCLUDED

#include "Point.h"
#include "BoundedPQueue.h"
#include <stdexcept>
#include <cmath>
#include <map>

// "using namespace" in a header file is conventionally frowned upon, but I'm
// including it here so that you may use things like size_t without having to
// type std::size_t every time.
using namespace std;

template <size_t N, typename ElemType>
class KDTree {
public:
    // Constructor: KDTree();
    // Usage: KDTree<3, int> myTree;
    // ----------------------------------------------------
    // Constructs an empty KDTree.
    KDTree();
    
    // Destructor: ~KDTree()
    // Usage: (implicit)
    // ----------------------------------------------------
    // Cleans up all resources used by the KDTree.
    ~KDTree();
    
    // KDTree(const KDTree& rhs);
    // KDTree& operator=(const KDTree& rhs);
    // Usage: KDTree<3, int> one = two;
    // Usage: one = two;
    // -----------------------------------------------------
    // Deep-copies the contents of another KDTree into this one.
    KDTree(const KDTree& rhs);
    KDTree& operator=(const KDTree& rhs);
    
    // size_t dimension() const;
    // Usage: size_t dim = kd.dimension();
    // ----------------------------------------------------
    // Returns the dimension of the points stored in this KDTree.
    size_t dimension() const;
    
    // size_t size() const;
    // bool empty() const;
    // Usage: if (kd.empty())
    // ----------------------------------------------------
    // Returns the number of elements in the kd-tree and whether the tree is
    // empty.
    size_t size() const;
    bool empty() const;
    
    // bool contains(const Point<N>& pt) const;
    // Usage: if (kd.contains(pt))
    // ----------------------------------------------------
    // Returns whether the specified point is contained in the KDTree.
    bool contains(const Point<N>& pt) const;
    
    // void insert(const Point<N>& pt, const ElemType& value);
    // Usage: kd.insert(v, "This value is associated with v.");
    // ----------------------------------------------------
    // Inserts the point pt into the KDTree, associating it with the specified
    // value. If the element already existed in the tree, the new value will
    // overwrite the existing one.
    void insert(const Point<N>& pt, const ElemType& value);
    
    // ElemType& operator[](const Point<N>& pt);
    // Usage: kd[v] = "Some Value";
    // ----------------------------------------------------
    // Returns a reference to the value associated with point pt in the KDTree.
    // If the point does not exist, then it is added to the KDTree using the
    // default value of ElemType as its key.
    ElemType& operator[](const Point<N>& pt) ;
    
    // ElemType& at(const Point<N>& pt);
    // const ElemType& at(const Point<N>& pt) const;
    // Usage: cout << kd.at(v) << endl;
    // ----------------------------------------------------
    // Returns a reference to the key associated with the point pt. If the point
    // is not in the tree, this function throws an out_of_range exception.
    ElemType& at(const Point<N>& pt);
    const ElemType& at(const Point<N>& pt) const;
    
    // ElemType kNNValue(const Point<N>& key, size_t k) const
    // Usage: cout << kd.kNNValue(v, 3) << endl;
    // ----------------------------------------------------
    // Given a point v and an integer k, finds the k points in the KDTree
    // nearest to v and returns the most common value associated with those
    // points. In the event of a tie, one of the most frequent value will be
    // chosen.
    ElemType kNNValue(const Point<N>& key, size_t k) const;

private:
    struct Node
    {
        Point<N> point;
        ElemType value;
        Node* left;
        Node* right;

        Node(const Point<N>& pt, const ElemType& v);
    };

    Node* root_node;

    static const int dim = N;
    int elements_num;

    Node* find_node(const Point<N>& key) const;

    void kNN_search(const Point<N>& key,  
                        Node* curr_node,       
                        BoundedPQueue<Node*>& bpq,       
                        int curr_dim) const;

    void destroy_tree(Node* node);

    Node* clone(Node* node);
    // TODO: Add implementation details here.
};

/** KDTree class implementation details */

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree():elements_num(0) 
{
    root_node = nullptr;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree(const KDTree& rhs): elements_num(rhs.elements_num)
{
    root_node = clone(rhs.root_node);
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>& KDTree<N, ElemType>::operator=(const KDTree& rhs)
{
    if (this != &rhs)
    {
        destroy_tree(root_node);
        elements_num = rhs.elements_num;
        root_node = clone(rhs.root_node);
    }

    return *this;
}

template <size_t N, typename ElemType>
typename KDTree<N, ElemType>::Node* KDTree<N, ElemType>::clone(Node* node)
{
    Node* clone_node = nullptr;
    if(node)
    {
        clone_node = new Node(node->point, node->value);
        clone_node->left = clone(node->left);
        clone_node->right = clone(node->right);
    }

    return clone_node;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::~KDTree() {
    destroy_tree(root_node);
}



template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::dimension() const {
    return dim;
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::size() const
{
    return elements_num;
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::empty() const
{
    return elements_num == 0;
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::contains(const Point<N>& pt) const
{
    return find_node(pt) != nullptr;
}
    
template <size_t N, typename ElemType>
void KDTree<N, ElemType>::insert(const Point<N>& pt, const ElemType& value)
{

    if (!root_node)
    {
        root_node = new Node(pt, value);
        elements_num = 1;
        return;
    }

    Node* curr_node = root_node;
    Node* parent_node = nullptr;
    int curr_dim = 0;

    while (curr_node && curr_node->point != pt)
    {
        parent_node = curr_node;
        if (pt[curr_dim] < curr_node->point[curr_dim])
        {   
            curr_node = curr_node->left;
        }
        else
        {
            curr_node = curr_node->right;
        }

        curr_dim = (curr_dim + 1) % dim;
    }

    if (curr_node != nullptr)
    {
        curr_node->value = value;
    }
    else
    {
        curr_dim = (curr_dim -1 + dim) % dim;
        if (pt[curr_dim] < parent_node->point[curr_dim])
        {   
            parent_node->left = new Node(pt, value);
        }
        else
        {
            parent_node->right = new Node(pt, value);
        }

        ++elements_num;
    }
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::operator[](const Point<N>& pt)
{
    Node* node = find_node(pt);
    if (!node)
    {
        ElemType v;
        insert(pt, v);
    }
    return find_node(pt)->value;
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::at(const Point<N>& pt)
{
    const KDTree& constThis = *this;
    return const_cast<ElemType&>(constThis.at(pt));
}

template <size_t N, typename ElemType>
const ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) const
{
    Node* node = find_node(pt);

    if (!node)
    {
        throw std::out_of_range("Can't find this point");
    }
    cout << node->value;
    return node->value; 
}

template <size_t N, typename ElemType>
ElemType KDTree<N, ElemType>::kNNValue(const Point<N>& key, size_t k) const
{
    BoundedPQueue<Node*> bpq(k);

    kNN_search(key, root_node, bpq, 0);

    map<ElemType, int> frequent;

    while (!bpq.empty())
    {
        Node* node = bpq.dequeueMin();
        frequent[node->value] += 1;
    }

    ElemType max_value;
    int max_num = 0;

    for (auto& item : frequent)
    {
        if (item.second > max_num)
        {
            max_num = item.second;
            max_value = item.first;
        }
    }
    return max_value;

}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::kNN_search(const Point<N>& key,  
                                         Node* curr_node,       
                                         BoundedPQueue<Node*>& bpq,       
                                         int curr_dim) const
{
    if (!curr_node)
    {
        return;
    }

    double dis = Distance(curr_node->point, key);
    bpq.enqueue(curr_node, dis);
    int next_dim = (curr_dim + 1) % dim;

    Node* other_node;
    if (key[curr_dim] < curr_node->point[curr_dim])
    {
        kNN_search(key, curr_node->left, bpq, next_dim);
        other_node = curr_node->right;
    }
    else
    {
        kNN_search(key, curr_node->right, bpq, next_dim);
        other_node = curr_node->left;
    }

    double highestPriority = bpq.worst();
    double diff = fabs(curr_node->point[curr_dim] - key[curr_dim]);

    if ((bpq.size() < bpq.maxSize()) || diff < highestPriority)
    {
        kNN_search(key, other_node, bpq, next_dim);
    }

}

//praivate
template <size_t N, typename ElemType>
void KDTree<N, ElemType>::destroy_tree(Node* node)
{
    if(node)
    {
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }
}

template <size_t N, typename ElemType>
typename KDTree<N, ElemType>::Node* KDTree<N, ElemType>::find_node(const Point<N>& pt) const
{
    Node* curr_node = root_node;
    int curr_dim = 0;

    while (curr_node && curr_node->point != pt)
    {
        if (pt[curr_dim] < curr_node->point[curr_dim])
            curr_node = curr_node->left;
        else
            curr_node = curr_node->right;

        curr_dim = (curr_dim + 1) % dim;
    }

    return curr_node;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::Node::Node(const Point<N>& pt, const ElemType& v)
{
    point = pt;
    value = v;
    left = nullptr;
    right = nullptr;
}

// TODO: finish the implementation of the rest of the KDTree class

#endif // KDTREE_INCLUDED
