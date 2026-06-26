//注意使用erase操作后赋值一定要判断迭代器合法性
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
    ll n,m;
    cin>>n>>m;
    list<ll> nd;
    ll nn;
    for(ll i=1;i<=n;i++)nd.push_back(i);
    ll st=nd.size();
    auto it=nd.begin();
    while(nd.size()>0){
        for(ll i=0;i<m-1;i++){
            it++;
            nn=*it;
            if(it==nd.end())it=nd.begin();
        }
        if(nd.size()!=st)cout<<" ";
        cout<<*it;
        it=nd.erase(it);
        if(it==nd.end())it=nd.begin();
    }
    cout<<endl;
}
int main(){
    solve();
    return 0;
}