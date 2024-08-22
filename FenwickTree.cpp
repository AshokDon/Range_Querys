#include<bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define ll long long
#define pb push_back
#define mp make_pair
using namespace std;
const int N = 1e6 + 5;
const double pi = acos(-1.0);
const long long INF = 1e18;
const int32_t M = 1e9 + 7;
const int32_t MM = 998244353;
int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
int dy[8] = {0, 1, 0, -1, -1, 1, 1, -1};
 
int n , q;
vector<ll>bit;
 
void upDate(ll id, ll val){
    while(id <= n){
        bit[id]+=val;
        id += (id & -id);
    }
}
ll Query(ll id){
    ll sum = 0;
    while(id > 0){
        sum += bit[id];
        id -= (id & -id);
    }
    return sum;
}
int main(){
    cin >> n >> q;
    bit.assign(n+1,0);
    vector<ll>nums(n+1);
    for(int i = 1 ; i <= n ; i++){
        cin >> nums[i];
    }
    for(ll i = 1 ; i <= n ; i++){
        upDate(i,nums[i]);
    }
    while(q--){
        ll s , l , r;
        cin >> s >> l >> r;
        if(s == 1){
            upDate(l,r-nums[l]);
            nums[l] = r;
 
        }
        else{
            cout<<Query(r) - Query(l-1)<<endl;
        }
 
    }
    
 
}
