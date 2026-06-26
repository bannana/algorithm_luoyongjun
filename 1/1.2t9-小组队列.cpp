#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    ll n,m;
    cin>>n>>m;
    vector<pair<ll,ll>> a(n);
    deque<ll> se;
    vector<deque<pair<ll,ll>>> num(300);
    for(ll i=0;i<n;i++){
        cin>>a[i].first;
        a[i].second=i;
    }
    ll t;
    cin>>t;
    for(ll i=0;i<t;i++){
        string str;
        cin>>str;
        if(str=="push"){
            ll nn;
            cin>>nn;
            ll na=a[nn].first;
			ll nb=a[nn].second;
            if(num[na].empty()){
                se.push_back(na);
            }
            num[na].push_back({na,nb});
        }else{
            ll fr=se.front();
            cout<<num[fr].front().second<<endl;
            if(num[fr].size()==1){
                se.pop_front();
            }
            num[fr].pop_front();
        }
    }
    return 0;
}