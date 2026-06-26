#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    ll n;
    cin>>n;
    priority_queue<ll,vector<ll>,greater<>> a;
    for(ll i=0;i<n;i++){
        ll tmp;
        cin>>tmp;
        a.push(tmp);
    }
    ll ans=0;
    while(a.size()>1){
        ll aa=a.top();a.pop();
        ll bb=a.top();a.pop();
        ans+=aa+bb;
        a.push(aa+bb);
    }
    cout<<ans<<endl;
    return 0;
}