#include <ios>
#include <iostream>
#include <vector>
#include <climits>
 
#define ll long long
#define vv std::vector
 
 //min
template <typename T>
struct SegTree
{
    const T ID = (T)INT_MAX; // initialize
    int size;
    vv<T> tree;
 
    inline T cmb(T &a, T &b)
    {
        return (a < b ? a : b);
    }
 
    void init(int n)
    {
        for (size = 1; size < n;)
            size *= 2;
        tree.assign(2 * size, ID);
    }
 
    void build(vv<T> &A, int node, int left, int right)
    {
        if (left == right)
        {
            if (left < (int)A.size()) // if valid index in A
                tree[node] = A[left];
            return;
        }
 
        int mid = left + (right - left) / 2;
 
        build(A, 2 * node + 1, left, mid);
        build(A, 2 * node + 2, mid + 1, right);
        tree[node] = cmb(tree[2 * node + 1], tree[2 * node + 2]);
    }
 
    void set(int index, int val, int node, int left, int right)
    {
        if (left == right)
        {
            tree[node] = val;
            return;
        }
 
        int mid = left + (right - left) / 2;
        if (index <= mid)
            set(index, val, 2 * node + 1, left, mid);
        else
            set(index, val, 2 * node + 2, mid + 1, right);
 
        // combine
        tree[node] = cmb(tree[2 * node + 1], tree[2 * node + 2]);
    }
 
    T get(int l, int r, int node, int left, int right)
    {
        if (right < l || r < left)
            return ID;
 
        if (l <= left && right <= r)
            return tree[node];
 
        int mid = left + (right - left) / 2;
        T x1 = get(l, r, 2 * node + 1, left, mid);
        T x2 = get(l, r, 2 * node + 2, mid + 1, right);
        return cmb(x1, x2);
    }
 
    void set(int index, int value)
    {
        set(index, value, 0, 0, size - 1);
    }
 
    T get(int l, int r)
    {
        return get(l, r, 0, 0, size - 1);
    }
 
    void build(vv<T> &A)
    {
        build(A, 0, 0, size - 1);
    }
};