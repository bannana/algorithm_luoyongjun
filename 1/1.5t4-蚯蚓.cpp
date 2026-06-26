#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
int main(){
    ll n,m,q,u,v,t;
    cin>>n>>m>>q>>u>>v>>t;
    deque<ll> q1,q2,q3;
    for(ll i=0;i<n;i++){
        ll tmp;
        cin>>tmp;
        q1.push_back(tmp);
    }
    bool bk=false;
    sort(q1.begin(),q1.end(),greater<ll>());
    for(ll i=0;i<m;i++){
        ll ma=LLONG_MIN,lo=0;
        if(!q1.empty()&&q1.front()>ma)ma=q1.front(),lo=1;
        if(!q2.empty()&&q2.front()>ma)ma=q2.front(),lo=2;
        if(!q3.empty()&&q3.front()>ma)ma=q3.front(),lo=3;
        if(lo==1)q1.pop_front();
        else if(lo==2)q2.pop_front();
        else q3.pop_front();
        ma+=i*q;
        ll res1=ma*u/v,res2=ma-res1;
        q2.push_back(res1-q-i*q);
        q3.push_back(res2-q-i*q);
        if((i+1)%t==0){
            if(bk)cout<<' ';
            cout<<ma;
            bk=false;
        }
    }
    bk=true;
    cout<<endl;
    for(ll i=0;i<n+m;i++){
        ll ma=LLONG_MIN,lo=0;
        if(!q1.empty()&&q1.front()>ma)ma=q1.front(),lo=1;
        if(!q2.empty()&&q2.front()>ma)ma=q2.front(),lo=2;
        if(!q3.empty()&&q3.front()>ma)ma=q3.front(),lo=3;
        if(lo==1)q1.pop_front();
        else if(lo==2)q2.pop_front();
        else q3.pop_front();
        if((i+1)%t==0){
            if(bk)cout<<' ';
            cout<<ma;
            bk=false;
        }
    }
    cout<<endl;
    return 0;
}