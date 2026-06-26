//注意密集使用到endl，就需要像以下这样加速
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    ll n,m;
    cin>>n>>m;
    vector<ll> a(n+1);
    deque<ll> dq;
    cout<<0<<'\n';
    for(ll i=1;i<=n;i++)cin>>a[i];
    for(ll i=1;i<n;i++){
        while(!dq.empty()&&a[dq.back()]>a[i])dq.pop_back();
        dq.push_back(i);
        while(!dq.empty()&&i-dq.front()>=m)dq.pop_front();
        cout<<a[dq.front()]<<'\n';
    }
    return 0;
}