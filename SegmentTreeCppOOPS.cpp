#include<bits/stdc++.h>
using namespace std;
class SegmentTree{
    private:
    vector<int>SegTree;
    public:
    SegmentTree(int n){
        SegTree.resize(4*n);
    }

    //Add data 
    void BuildSegTree(int Index, int start , int end, vector<int>&A){
        if(start == end){
            SegTree[Index] = A[start];
            return;
        }
        int mid = (start + end) / 2;
        BuildSegTree(2*Index + 1, start , mid , A);
        BuildSegTree(2*Index + 2, mid + 1, end , A);

        SegTree[Index] = SegTree[2*Index+1] + SegTree[2*Index+2];
 
    }

    //find range Sum (L to R)
    int RangeSum(int Ql, int Qr, int start, int end, int index){
        //no over lap
        if(Ql > end || Qr < start){
            return 0;
        }
        //complete over lap
        if(Ql <= start && Qr >= end){
            return SegTree[index];
        }
        //partial over lap
        int mid = (start + end) / 2;
        int left = RangeSum(Ql , Qr, start , mid , 2*index+1);
        int right = RangeSum(Ql , Qr, mid + 1, end , 2*index+2);
        return left +right;
    }

    // //Update the number in kth index
    void Update(int k , int val , int start , int end, int idx){
        if(start == end){
            SegTree[idx] = val;
            return;
        }
        int mid = (start + end) / 2;
        if(k <= mid){
            Update(k , val , start , mid , 2*idx+1);
        }
        else{
            Update(k, val , mid + 1, end , 2*idx+2);
        }
        SegTree[idx]  = SegTree[2*idx+1] + SegTree[2*idx+2];
    }

};

int main(){
    int n;
    cin >> n;
    vector<int>A(n);
    for(int i = 0 ; i < n ; i++)cin >> A[i];
    SegmentTree SegTree(n);
    SegTree.BuildSegTree(0, 0 , n-1, A);
    int l = 2, r = 4;

    cout <<SegTree.RangeSum(l,r,0,n-1,0);
    SegTree.Update(2,0,0,n-1,0);
    cout <<SegTree.RangeSum(l,r,0,n-1,0);

}
