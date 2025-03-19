#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<int> tree, lazy;
    int n;

    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start]; // Leaf node
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node]; // Apply lazy value
            if (start != end) { 
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0; // Clear lazy value
        }
    }

    int query(int node, int start, int end, int L, int R) {
        propagate(node, start, end);
        if (R < start || L > end) return INT_MAX; // No overlap
        if (L <= start && end <= R) return tree[node]; // Full overlap

        int mid = (start + end) / 2;
        return min(query(2 * node + 1, start, mid, L, R),
                   query(2 * node + 2, mid + 1, end, L, R));
    }

    void pointUpdate(int node, int start, int end, int idx, int value) {
        propagate(node, start, end);
        if (start == end) {
            tree[node] = value; // Update leaf node
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) 
                pointUpdate(2 * node + 1, start, mid, idx, value);
            else 
                pointUpdate(2 * node + 2, mid + 1, end, idx, value);
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    void rangeUpdate(int node, int start, int end, int L, int R, int value) {
        propagate(node, start, end);
        if (R < start || L > end) return; // No overlap

        if (L <= start && end <= R) { // Full overlap
            lazy[node] += value;
            propagate(node, start, end);
            return;
        }

        int mid = (start + end) / 2;
        rangeUpdate(2 * node + 1, start, mid, L, R, value);
        rangeUpdate(2 * node + 2, mid + 1, end, L, R, value);
        tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
    }

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.assign(4 * n, INT_MAX);
        lazy.assign(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }

    int query(int L, int R) {
        return query(0, 0, n - 1, L, R);
    }

    void pointUpdate(int idx, int value) {
        pointUpdate(0, 0, n - 1, idx, value);
    }

    void rangeUpdate(int L, int R, int value) {
        rangeUpdate(0, 0, n - 1, L, R, value);
    }
};

// Driver Code
int main() {
    vector<int> arr = {5, 2, 6, 3, 8, 7, 4, 1, 9};
    SegmentTree st(arr);

    cout << "Min in range [2, 6]: " << st.query(2, 6) << endl; // 3
    st.pointUpdate(3, 10); // Update index 3 to 10
    cout << "Min in range [2, 6]: " << st.query(2, 6) << endl; // 4
    st.rangeUpdate(1, 4, -2); // Decrease values in [1,4] by 2
    cout << "Min in range [2, 6]: " << st.query(2, 6) << endl; // 1

    return 0;
}
