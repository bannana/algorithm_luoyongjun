//滑动窗口队列+二分+DP
//此处二分当模版记住得了
//此处j只有在等到满足left后才++，此处把一个区间掰成2步处理很不错，值得借鉴，同时这也是运用队列的原因
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=1e18;
ll n,d,k;
vector<ll> x,s;
bool check(ll t){
    vector<ll> gain(n+1,-INF);
    deque<ll> dq;
    gain[0]=0;
    ll j=0;
    ll left=max(1LL,d-t),right=d+t;
    for(ll i=1;i<=n;i++){
        while(j<i&&x[i]-x[j]>=left){
            if(gain[j]!=-INF){
                while(!dq.empty()&&gain[dq.back()]<gain[j])dq.pop_back();
                dq.push_back(j);
            }
            j++;
        }
        while(!dq.empty()&&x[i]-x[dq.front()]>right)dq.pop_front();
        if(!dq.empty())gain[i]=gain[dq.front()]+s[i];
        else gain[i]=-INF;
        if(gain[i]>=k)return true;
    }
    return false;
}
int main(){
    cin>>n>>d>>k;
    x.resize(n+1),s.resize(n+1);
    for(ll i=1;i<=n;i++)cin>>x[i]>>s[i];
    ll r=1e9,l=0;
    ll ans=-1;
    while(l<=r){
        ll mid=(r+l)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}