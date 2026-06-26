#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
bool solve(){
    ll n;
    cin>>n;
    string str;
    cin>>str;
    sort(str.begin(),str.end());
    priority_queue<ll,vector<ll>,greater<>> pq;
    ll num=1;
    for(ll i=1;i<=str.size();i++){
        if(str[i-1]!=str[i]){
            pq.push(num);
            num=1;
        }else num++;
    }
    ll ans=1;
    if(pq.size()==1)ans=str.size();
    while(pq.size()>1){
        ll a=pq.top();pq.pop();
        ll b=pq.top();pq.pop();
        ans+=a+b;
        pq.push(a+b);
    }
    if(ans<=n)return true;
    else return false;
}
int main(){
    ll t;
    cin>>t;
    while(t--){
        if(solve())cout<<"yes"<<endl;
        else cout<<"no"<<endl;
    }
    return 0;
}