//没想到使用队列，建立一个sum累计数组，注意不要i==dq.front否则出现0污染结果
//每增加一个位置，要先检查大小，在运用窗口极小值算出最大值，同ans更新
//同时检测用当前值将dq更新成小于它的队列，保证单增，开始位置最小
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll n,m;
    cin>>n>>m;
    ll a;
    vector<ll> sum(n+3,0);
    for(ll i=1;i<=n;i++){
        cin>>a;
        sum[i]=sum[i-1]+a;
    }
    deque<ll> dq;
    ll ans=-1e18;
    dq.push_back(0);
    for(ll i=1;i<=n;i++){
        while(!dq.empty()&&i-dq.front()>m)dq.pop_front();
        ans=max(ans,sum[i]-sum[dq.front()]);
        while(!dq.empty()&&sum[dq.back()]>=sum[i])dq.pop_back();
        dq.push_back(i);
    }
    cout<<ans<<endl;
    return 0;
}