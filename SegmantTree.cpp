#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    vector<int> arr;
    int n;

    void build(int index, int l, int r) {
        if (l == r) {
            tree[index] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * index, l, mid);
        build(2 * index + 1, mid + 1, r);
        tree[index] = tree[2 * index] + tree[2 * index + 1];
    }

    int query(int index, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0;       // No overlap
        if (ql <= l && r <= qr) return tree[index]; // Total overlap

        int mid = (l + r) / 2;
        int left = query(2 * index, l, mid, ql, qr);
        int right = query(2 * index + 1, mid + 1, r, ql, qr);
        return left + right;
    }

    void update(int index, int l, int r, int pos, int val) {
        if (l == r) {
            tree[index] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid)
            update(2 * index, l, mid, pos, val);
        else
            update(2 * index + 1, mid + 1, r, pos, val);

        tree[index] = tree[2 * index] + tree[2 * index + 1];
    }

public:
    SegmentTree(const vector<int>& input) {
        arr = input;
        n = arr.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    int rangeSum(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    void updateValue(int pos, int val) {
        update(1, 0, n - 1, pos, val);
    }
};

int main() {
    vector<int> input = {2, 1, 5, 3, 4};
    SegmentTree seg(input);

    cout << "Sum from 1 to 3: " << seg.rangeSum(1, 3) << endl;  // 1+5+3 = 9
    seg.updateValue(2, 6); // Update index 2 to 6
    cout << "Sum from 1 to 3 after update: " << seg.rangeSum(1, 3) << endl; // 1+6+3 = 10

    return 0;
}
