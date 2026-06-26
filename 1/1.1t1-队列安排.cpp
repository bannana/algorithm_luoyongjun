//使用结构体数组模拟链表，节省查找时间，实在是高
//注意初始化中需要一个虚拟0位置作为全链条最左侧或最右侧
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN=1e5+5;
struct node{
    ll l,r;
    ll d;
}m[MAXN];
void solve(){
    ll n;
    cin>>n;
    m[1].d=1;
    m[1].l=0,m[1].r=0;
    m[0].d=0;
    m[0].l=0,m[0].r=1;
    for(ll i=2;i<=n;i++){
        ll k,p;
        cin>>k>>p;
        if(p==0){
            m[i].r=k;
            m[i].l=m[k].l;
            m[m[k].l].r=i;
            m[k].l=i;
        }else{
            m[i].l=k;
            m[i].r=m[k].r;
            m[m[k].r].l=i;
            m[k].r=i;
        }
        m[i].d=1;
    }
    ll nn;
    cin>>nn;
    for(ll i=0;i<nn;i++){
        ll x;
        cin>>x;
        m[x].d=0;
    }
    ll now=m[0].r;
    while(now!=0){
        if(m[now].d){
            if(now!=m[0].r)cout<<" ";
            cout<<now;
        }
        now=m[now].r;
    }
    cout<<endl;
}
int main(){
    solve();
    return 0;
}