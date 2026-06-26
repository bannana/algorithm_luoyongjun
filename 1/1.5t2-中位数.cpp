#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
int main(){
    ll n;
    cin>>n;
    priority_queue<ll> r;
    priority_queue<ll,vector<ll>,greater<>> l;
    ll tmp;
    cin>>tmp;
    cout<<tmp<<endl;
    r.push(tmp);
    for(ll i=1;i<n;i++){
        cin>>tmp;
        if(tmp>r.top())l.push(tmp);
        else r.push(tmp);
        while(r.size()>l.size()+1){
            l.push(r.top());r.pop();
        }
        while(l.size()>r.size()+1){
            r.push(l.top());l.pop();
        }
        if(i%2==0)cout<<(l.size()>r.size()?l.top():r.top())<<endl;
    }
    return 0;
}