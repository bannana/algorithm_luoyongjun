//本题为反悔贪心，总结一下堆的知识，着重在于考察利用某些性质管理不同堆解决问题
//反悔贪心在于每次都比较一下是硬着头皮上还是选择反悔一次代价最小的
//如果是后者回报高，那就付出代价，把仅有的减免机会让给c组
//注意使用buy数组同步p和c组内已买过的物品，每一轮都要删掉已买的，保证一致性
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
typedef struct{
    ll pri,pre;
    ll ord;
}pll;
struct cmp1{
    bool operator()(const pll &a,const pll &b){
        return a.pri>b.pri;
    }
};
struct cmp2{
    bool operator()(const pll &a,const pll &b){
        return a.pre>b.pre;
    }
};
int main(){
    ll n,k,m;
    cin>>n>>k>>m;
    vector<bool> buy(n,false);
    priority_queue<pll,deque<pll>,cmp1>p;
    priority_queue<pll,deque<pll>,cmp2>c;
    priority_queue<ll,deque<ll>,greater<>>delta;
    for(ll i=0;i<k;i++)delta.push(0);
    for(ll i=0;i<n;i++){
        pll tmp;
        cin>>tmp.pri>>tmp.pre;
        tmp.ord=i;
        p.push(tmp);
        c.push(tmp);
    }
    ll ans=0;
    while(!p.empty()){
        while(!p.empty()&&buy[p.top().ord])p.pop();
        while(!c.empty()&&buy[c.top().ord])c.pop();
        if(p.empty())break;
        if(p.top().pri<=c.top().pre+delta.top()){
            m-=p.top().pri;
            if(m<0)break;
            buy[p.top().ord]=true;
            ans++;
        }else{
            m-=delta.top()+c.top().pre;
            if(m<0)break;
            buy[c.top().ord]=true;
            delta.pop();
            delta.push(c.top().pri-c.top().pre);
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}