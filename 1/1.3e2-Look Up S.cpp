#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
int main(){
    ll t;
    cin>>t;
    vector<ll> h(t+2),ans(t+2);
    deque<ll> dq;
    dq.push_back(t+1);
    for(ll i=1;i<=t;i++)cin>>h[i];
    h[t+1]=1e18;
    for(ll i=t;i>=1;i--){
        while(h[i]>=h[dq.back()])dq.pop_back();
        if(dq.back()==t+1)ans[i]=0;
        else ans[i]=dq.back();
        dq.push_back(i);
    }
    for(ll i=1;i<=t;i++)cout<<ans[i]<<endl;
    return 0;
}