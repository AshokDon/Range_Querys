#include <bits/stdc++.h>
using namespace std;
class SegmentTree{
    vector<int>Tree;
    vector<int>Lazy;
    int n;
    void BuildATree(int ss, int se, vector<int>&A,int index){
        //base case
        if(ss == se){
            Tree[index] = A[ss];
            return;
        }
        int mid = (ss + se) / 2;
        BuildATree(ss, mid, A, 2*index);
        BuildATree(mid + 1, se , A, 2*index+1);
        Tree[index] = min(Tree[2*index],Tree[2*index+1]);
        return;
    }
    int Query(int qs, int qe, int ss, int se, int index){
        //no over lap
        if(qs > se || ss > qe){
            return INT_MAX;
        }
        //complete over lap
        if(ss >= qs && se <= qe){
            return Tree[index];
        }
        //partial ovel lap
        int mid = (ss + se) / 2;
        int left = Query(qs, qe, ss, mid, 2*index);
        int right = Query(qs, qe, mid + 1, se, 2*index+1);
        
        return min(left,right);
    }
    void RangeUpdateLazy(int ss, int se, int qs, int qe, int index, int inc){
        if(lazy[index]!=0){
            Tree[index]+=lazy[index];
            if(se!=ss){
                lazy[2*index]+=lazy[index];
                lazy[2*index+1]+=lazy[index];
                
            }
            lazy[index] = 0;
        }
        if(ss > qe || qs > se)return;
        //complete over lap
        if(qs <= ss && se <= qe){
            Tree[index]+=inc;
            if(se!=ss){
                lazy[2*index] += inc;
                lazy[2*index+1] +=inc;
            }
            return;
        }
        
        //partial over lap
        int mid = (ss + se) / 2;
        RangeUpdateLazy(ss, mid , qs, qe,2*index,inc);
        RangeUpdateLazy(mid + 1 , se , qs, qe, 2*index+1 , inc);
        Tree[index] = min(Tree[2*index] , Tree[2*index+1]);
        return;
        
        
    }
    
    public:
    SegmentTree(vector<int>&A){
        n = A.size(); // n 
        //0 n-1
        Tree.resize(4*n,INT_MAX);
        Lazy.resize(4*n,0);
        BuildATree(0,n-1,A,1);
        //cout << "hello\n";
    }
    int Query(int qs,int qe){
        return Query(qs,qe,1,n,1);
        //return 1;
    }
    void RangeUpdateLazy(int qs, int qe, int inc){
        RangeUpdateLazy(0,n-1,qs,qe,1,inc);
    }
    int QueryLazy(int qs, int qe){
        
    }
};

int main() {
	// your code goes here
	int n;
	cin >> n;
	vector<int>A(n);
	for(int i = 0 ; i < n ; i++){
	    cin >> A[i];
	}
	SegmentTree SegTree(A);
	cout << SegTree.Query(4,6) << endl;
	SegTree.RangeUpdateLazy(0,2,10);
	return 0;
}
