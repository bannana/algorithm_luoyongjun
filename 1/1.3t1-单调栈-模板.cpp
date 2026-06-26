//单调栈
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
int main(){
    ll n;
    cin>>n;
    vector<ll> ans(n+2),a(n+2);
    deque<ll> dq;
    a[n+1]=1e18;
    dq.push_back(n+1);
    for(ll i=1;i<=n;i++)cin>>a[i];
    for(ll i=n;i>=1;i--){
        while(a[dq.back()]<=a[i])dq.pop_back();
        if(dq.back()==n+1)ans[i]=0;
        else ans[i]=dq.back();
        dq.push_back(i);
    }
    for(ll i=1;i<=n;i++){
        if(i!=1)cout<<" ";
        cout<<ans[i];
    }
    cout<<endl;
    return 0;
}