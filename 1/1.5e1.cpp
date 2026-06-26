#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
int main(){
    ll n;
    cin>>n;
    priority_queue<ll,vector<ll>,greater<>>pq;
    while(n--){
        ll op;
        cin>>op;
        if(op==1){
            ll x;
            cin>>x;
            pq.push(x);
        }else if(op==2)cout<<pq.top()<<endl;
        else pq.pop();
    }
    return 0;
}