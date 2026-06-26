#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
int main(){
    ll n,k;
    cin>>n>>k;
    priority_queue<pll,vector<pll>,greater<>> pq;
    for(ll i=1;i<=n;i++){
        ll w;
        cin>>w;
        pq.push({w,0});
    }
    ll ans=0;
    ll ma=0;
    while((pq.size()-1)%(k-1)!=0)pq.push({0,0});
    while(pq.size()>1){
        ll tmp=0;
        ll h=0;
        for(ll i=0;i<k;i++){
            tmp+=pq.top().first;
            h=max(h,pq.top().second);
            pq.pop();
        }
        ans+=tmp;
        pq.push({tmp,h+1});
    }
    cout<<ans<<endl<<pq.top().second<<endl;
    return 0;
}