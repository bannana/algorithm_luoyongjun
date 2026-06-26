//注意不要越界和while循环
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    ll n,k;
    cin>>n>>k;
    vector<ll> num(n+5);
    for(ll i=1;i<=n;i++)cin>>num[i];
    deque<ll> dq;
    for(ll i=1;i<=n;i++){
        while(!dq.empty()&&num[dq.back()]<num[i])dq.pop_back();
        dq.push_back(i);
        if(i>=k){
            while(!dq.empty()&&i-dq.front()>=k)dq.pop_front();
            cout<<num[dq.front()]<<'\n';
        }
    }
    return 0;
}