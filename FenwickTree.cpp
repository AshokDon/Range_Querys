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
// find min value between l and r for Q queries using fenwick tree
vector<ll>bit;


ll N , Q;

void upDate(ll id, ll val){
    while(id <= N){
        if(val < bit[id]){
            bit[id] = val;
        }
        id += (id & -id);
    }
}
ll Query(ll id, ll i){
    ll ans = INT_MAX;
    while(id >= i){
        ans = min(ans, bit[id]);
        id -= (id & -id);
    }
    return ans;
}
int main(){
    fast_io;
    cin >> N >> Q;
    bit.assign(N+1,INT_MAX);
    vector<ll>arr(N+1);
    for(ll i = 1 ; i <= N ; i++){
        cin >> arr[i];
    }
    for(ll i = 1 ; i <= N ; i++){
            upDate(i,arr[i]);
    }
    while(Q--){
        ll type;
        cin >> type;
        if(type == 1){
            ll l , r;
            cin >> l >> r;
            cout<<Query(r,l)<<"\n";
        }
        else{
            ll id , val;
            cin >> id >> val;
            upDate(id,val);
        }

    }

}
