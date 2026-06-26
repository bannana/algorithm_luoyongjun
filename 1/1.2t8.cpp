//跟上一题有异曲同工之妙，把区间掰成两段，先把满足l的入队并排序
//接着消除不满足r的元素，使用dp不断计算每个位置的最大收益
//最后注意并非每个位置都可退出游戏，需要在合法i位置取最大值
//注意窗口主要维护的是j，i只是比较对象
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=-1e18;
int main(){
    ll n,l,r;
    cin>>n>>l>>r;
    vector<ll> a(n+1);
    vector<ll> gain(n+1,INF);
    gain[0]=0;
    deque<ll> qq;
    for(ll i=0;i<=n;i++)cin>>a[i];
    ll j=0;
    ll ans=INF;
    for(ll i=1;i<=n;i++){
        while(i>=j+l){
            if(gain[j]!=INF){
                while(!qq.empty()&&gain[qq.back()]<gain[j])qq.pop_back();
                qq.push_back(j);
            }
            j++;
        }
        while(!qq.empty()&&i-qq.front()>r)qq.pop_front();
        if(!qq.empty()){
            gain[i]=gain[qq.front()]+a[i];
            if(i+r>n)ans=max(ans,gain[i]);
        }
    }
    cout<<ans<<endl;
    return 0;
}