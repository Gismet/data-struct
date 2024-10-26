#include <ios>
#include <iostream>
#include <vector>
#include <climits>

#define ll long long
#define vv std::vector

template <typename T>
struct SegTree
{
    const T ID = (T)INT_MAX; // Identity for minimum
    int size;
    vv<T> tree, lazy;

    inline T cmb(T &a, T &b)
    {
        return (a < b ? a : b);
    }

    void init(int n)
    {
        for (size = 1; size < n;)
            size *= 2;
        tree.assign(2 * size, ID);
        lazy.assign(2 * size, 0); // Initialize lazy with 0 (no pending updates)
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

    void apply_lazy(int node, int left, int right)
    {
        if (lazy[node] != 0) // if there is a pending update
        {
            tree[node] += lazy[node]; // Apply the update
            if (left != right) // propagate the update to children if not a leaf
            {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0; // Clear the lazy value for current node
        }
    }

    void set(int l, int r, int val, int node, int left, int right)
    {
        apply_lazy(node, left, right); // Ensure all updates are applied before proceeding

        if (right < l || r < left) // No overlap
            return;
        if (l <= left && right <= r) // Complete overlap
        {
            lazy[node] += val; // Mark the lazy update
            apply_lazy(node, left, right); // Apply immediately
            return;
        }

        // Partial overlap
        int mid = left + (right - left) / 2;
        set(l, r, val, 2 * node + 1, left, mid);
        set(l, r, val, 2 * node + 2, mid + 1, right);
        tree[node] = cmb(tree[2 * node + 1], tree[2 * node + 2]);
    }

    T get(int l, int r, int node, int left, int right)
    {
        apply_lazy(node, left, right); // Apply any pending updates

        if (right < l || r < left) // No overlap
            return ID;

        if (l <= left && right <= r) // Complete overlap
            return tree[node];

        // Partial overlap
        int mid = left + (right - left) / 2;
        T x1 = get(l, r, 2 * node + 1, left, mid);
        T x2 = get(l, r, 2 * node + 2, mid + 1, right);
        return cmb(x1, x2);
    }

    void set(int l, int r, int value)
    {
        set(l, r, value, 0, 0, size - 1);
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
