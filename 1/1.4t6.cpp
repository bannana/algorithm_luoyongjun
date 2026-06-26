#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
vector<ll> v;
vector<ll> tree;
unordered_map<ll,pll> mp;
ll count(ll x){
    if(x==-1)return 0;
    ll l=mp[x].first;
    ll r=mp[x].second;
    tree[x]=count(l)+count(r)+1;
    return tree[x];
}
bool mirror(ll x,ll y){
    if(x==-1&&y==-1)return true;
    if(x==-1||y==-1)return false;
    if(v[x]!=v[y])return false;
    return mirror(mp[x].first,mp[y].second)&&mirror(mp[x].second,mp[y].first);
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    ll n;
    cin>>n;
    tree.resize(n+1);
    v.resize(n+1);
    for(ll i=1;i<=n;i++)cin>>v[i];
    for(ll i=1;i<=n;i++){
        cin>>mp[i].first>>mp[i].second;
    }
    ll ans=0;
    count(1);
    for(ll i=1;i<=n;i++){
        if(mirror(i,i))ans=max(ans,tree[i]);
    }
    cout<<ans<<endl;
    return 0;
}