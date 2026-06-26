#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
queue<ll> qq;
vector<ll> hh(1010,0);
int main(){
    ll m,n;
    cin>>m>>n;
    ll cnt=0;
    for(ll i=0;i<n;i++){
        ll t;
        cin>>t;
        if(!hh[t]){
            hh[t]=1;
            qq.push(t);
            cnt++;
            while(qq.size()>m){
                hh[qq.front()]=0;
                qq.pop();
            }
        }
    }
    cout<<cnt<<endl;
    return 0;
}