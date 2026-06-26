//本题深入理解了两项
//1.针对每个窗口要先清整，再推入，最后判断窗口大小
//2.使用sum数组可以解决此类涉及到求和的问题
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll n;
    cin>>n;
    vector<ll> a(2*n+2);
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        a[n+i]=a[i];
    }
    vector<ll> sum(2*n+2);
    sum[0]=0;
    for(ll i=1;i<=2*n;i++){
        sum[i]=sum[i-1]+a[i];
    }
    deque<ll> dq;
    ll ans=0;
    for(ll i=1;i<2*n;i++){
        while(!dq.empty()&&sum[dq.back()]>=sum[i])dq.pop_back();
        dq.push_back(i);
        if(i>=n){
            while(!dq.empty()&&i-dq.front()>n)dq.pop_front();
            if(sum[dq.front()]-sum[i-n]>=0)ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}