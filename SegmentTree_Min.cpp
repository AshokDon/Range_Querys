#include<bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define ll  long long
#define pb push_back
#define mp make_pair
using namespace std;
//const int N = 1e6 + 5;
const double pi = acos(-1.0);
const long long INF = 1e18;
const int32_t M = 1e9 + 7;
const int32_t MM = 998244353;
int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
int dy[8] = {0, 1, 0, -1, -1, 1, 1, -1};
 
//segment tree
 
void BuildTree(vector<ll>&arr, vector<ll>&st, ll start, ll end, ll node){
    if(start == end){
        st[node] = arr[start];
        return;
    }
    ll mid = (start + end)/2;
    BuildTree(arr,st,start,mid,2*node);
    BuildTree(arr,st,mid+1,end,2*node+1);
    //store the minimum of the two children
    st[node] = min(st[2*node],st[2*node+1]);
    return;
 
}
ll Query(vector<ll>&st, ll start, ll end, ll l, ll r, ll node){
    //no overlap
    if(start > r || end < l){
        return INT_MAX;
    }
    //complete overlap
    if(start >= l && end <= r){
        return st[node];
    }
    //partial overlap
    ll mid = (start + end)/2;
    ll left = Query(st,start,mid,l,r,2*node);
    ll right = Query(st,mid+1,end,l,r,2*node+1);
    return min(left,right);
}
 
int main(){
    ll n, q;
    cin >> n >> q;
    vector<ll>arr(n);
    for(ll i = 0 ; i < n ; i++){
        cin >> arr[i];
    }
    vector<ll>st(4*n);
    BuildTree(arr,st,0,n-1,1);
    for(ll i = 0 ; i < q ; i++){
        ll l,r;
        cin >> l >> r;
        ll ans = Query(st,0,n-1,l-1,r-1,1);
        cout<<ans<<endl;
        
    }
}
